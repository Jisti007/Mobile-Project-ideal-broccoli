/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package xyz.asdasd.gles3jni;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.WindowManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class GLES3JNIActivity extends Activity {
	GLES3JNIView view;
	private String dataDirectory;
	private float previousX;
	private float previousY;

	@Override
	public boolean onTouchEvent(MotionEvent e) {
		switch (e.getAction()) {
			case MotionEvent.ACTION_MOVE:
				float dx = e.getX() - previousX;
				float dy = e.getY() - previousY;
				GLES3JNILib.onMove(dx, -dy);
				break;
		}

		previousX = e.getX();
		previousY = e.getY();

		return true;
	}

	@Override
	protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		// Extract files from the .apk into the cache
		// so we can access them in C++ in a cross-platform way.
		dataDirectory = getCacheDir() + "/";
		extractFileOrDir("modules");

		view = new GLES3JNIView(getApplication(), this);
		setContentView(view);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	}

	@Override
	protected void onPause() {
		super.onPause();
		view.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		view.onResume();
	}

	private void extractFileOrDir(String path) {
		try {
			String[] assets = getAssets().list(path);
			if (assets.length == 0) {
				extractFile(path);
			} else {
				File dir = new File(dataDirectory + path);
				if (!dir.exists() && !dir.mkdir()) {
					Log.e("main", "failed to create directory: " + path);
					return;
				}

				for (String asset : assets) {
					String nextFileOrDir = path;
					if (!nextFileOrDir.equals("")) {
						nextFileOrDir += "/";
					}
					nextFileOrDir += asset;
					extractFileOrDir(nextFileOrDir);
				}
			}
		} catch (IOException e) {
			Log.e("main", "I/O Exception", e);
		}
	}

	private void extractFile(String filename) {
		try (
			InputStream in = getAssets().open(filename);
			OutputStream out = new FileOutputStream(dataDirectory + filename)
		) {
			byte[] buffer = new byte[32 * 1024];
			int read;
			while ((read = in.read(buffer)) != -1) {
				out.write(buffer, 0, read);
			}
			out.flush();
		} catch (Exception e) {
			Log.e("main", e.getMessage());
		}
	}
}
