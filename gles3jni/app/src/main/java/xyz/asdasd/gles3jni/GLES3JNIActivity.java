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
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.WindowManager;

public class GLES3JNIActivity extends Activity {
	private GLES3JNIView view;
	private GestureDetector gestureDetector;
	private ScaleGestureDetector scaleGestureDetector;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		gestureDetector = new GestureDetector(this, new GestureListener());
		scaleGestureDetector = new ScaleGestureDetector(this, new ScaleListener());

		view = new GLES3JNIView(getApplication(), this);
		setContentView(view);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		/*
		outState.putString("version", versionName);
		outState.putBoolean("assetsExtracted", true);
		*/
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

	@Override
	public boolean onTouchEvent(MotionEvent e) {
		scaleGestureDetector.onTouchEvent(e);
		if (scaleGestureDetector.isInProgress()) {
			return true;
		}

		gestureDetector.onTouchEvent(e);

		return true;
	}

	private class GestureListener extends GestureDetector.SimpleOnGestureListener {
		@Override
		public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
			GLES3JNILib.onMove(distanceX, -distanceY);
			return true;
		}

		@Override
		public boolean onSingleTapUp(MotionEvent e) {
			float x = e.getX();
			float y = e.getY();
			GLES3JNILib.onPress(x, y);
			return true;
		}
	}

	private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener {
		@Override
		public boolean onScale(ScaleGestureDetector detector) {
			float scaleFactor = scaleGestureDetector.getScaleFactor();
			if (scaleFactor != 1.0f) {
				GLES3JNILib.zoom(scaleFactor);
				return true;
			}
			return false;
		}
	}
}
