package com.github.goj.coffeemaker.android;

import android.os.Bundle;
import android.preference.PreferenceActivity;

public class PreferencesActivity extends PreferenceActivity {
	
	@Override
	@SuppressWarnings("deprecation") // my GF's phone still runs Android 2.1 :-/
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		addPreferencesFromResource(R.xml.preferences);
	}

}
