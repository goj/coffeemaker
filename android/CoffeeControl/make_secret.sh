#!/bin/sh

cat <<EOF > gen/com/github/goj/coffeemaker/android/Secret.java
package com.github.goj.coffeemaker.android;

public class Secret {
	public static final String SECRET = "`cat ../../SECRET`";
}
EOF
