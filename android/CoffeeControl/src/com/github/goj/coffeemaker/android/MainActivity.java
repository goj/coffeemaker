package com.github.goj.coffeemaker.android;

import static com.github.goj.coffeemaker.android.Secret.SECRET;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

    private static final String OFF = "off";
	private static final String STATUS = "status";
	private static final String ON = "on";
	private static final String STATE_KEY = "COFFEEMAKER_STATE";
	private Button onButton;
	private Button offButton;
	private Button statusButton;
	private TextView statusView;
	private String currentStatus;

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
		statusView = (TextView) findViewById(R.id.statusView);
        onButton = (Button) findViewById(R.id.onButton);
        offButton = (Button) findViewById(R.id.offButton);
        statusButton = (Button) findViewById(R.id.statusButton);
        
        onButton.setOnClickListener(doRequestListener(ON));
        statusButton.setOnClickListener(doRequestListener(STATUS));
        offButton.setOnClickListener(doRequestListener(OFF));
        
        PreferenceManager.setDefaultValues(this, R.xml.preferences, false);
        if (savedInstanceState != null) {
        	restoreDataFromBundle(savedInstanceState);
        } else {
        	new DoRequestTask().execute(STATUS);
        }
    }
	
	private void restoreDataFromBundle(Bundle savedInstanceState) {
		String savedStatus = savedInstanceState.getString(STATE_KEY);
		if (savedStatus != null)
			setCurrentStatus(savedStatus);
	}

	@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
	
	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		if (item.getItemId() == R.id.menu_settings) {
			Intent intent = new Intent(this, PreferencesActivity.class);
			startActivity(intent);
			return true;
		} else {
			return super.onMenuItemSelected(featureId, item);
		}
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		outState.putString(STATE_KEY, currentStatus);
		super.onSaveInstanceState(outState);
	}
	
    private OnClickListener doRequestListener(final String what) {
    	return new OnClickListener() {
    		public void onClick(View v) {
    			new DoRequestTask().execute(what);
    		}
    	};
	}

    private void setButtonsClickability(boolean clickable) {
    	onButton.setClickable(clickable);
    	statusButton.setClickable(clickable);
    	offButton.setClickable(clickable);
    }

    private void setCurrentStatus(String status) {
    	currentStatus = status;
    	statusView.setText(currentStatus);
    }
    
    private class DoRequestTask extends AsyncTask<String, Void, String> {

    	@Override
    	protected void onPreExecute() {
    		setButtonsClickability(false);
    	}

    	@Override
    	protected String doInBackground(String... params) {
    		if (params.length != 1) {
    			return "ERROR: bad number of params";
    		}
    		DefaultHttpClient client = new DefaultHttpClient();
    		HttpUriRequest post = new HttpGet(actionURL(params[0]));
    		post.setHeader("Secret", SECRET);
    		try {
    			HttpResponse response = client.execute(post);
    			HttpEntity entity = response.getEntity();
    			String responseContent = EntityUtils.toString(entity);
    			return responseContent;
    		} catch (Exception e) {
    			return "HTTP ERROR: " + e.getMessage();
    		}
    	}

    	@Override
    	protected void onPostExecute(String result) {
    		setCurrentStatus(result);
    		setButtonsClickability(true);
    	}

	}

	private String actionURL(String action) {
		SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
		String template = preferences.getString("url_template", null);
		return template.replace("%s", action);
	}

}
