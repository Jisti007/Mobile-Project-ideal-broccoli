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
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class GLES3JNIView extends GLSurfaceView {
	private static final String TAG = "GLES3JNI";
	private static final boolean DEBUG = true;
	private float previousX;
	private float previousY;

	public GLES3JNIView(Context context, Activity activity) {
		super(context);
		// Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
		// supporting OpenGL ES 2.0 or later backwards-compatible versions.
		setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		setEGLContextClientVersion(3);
		setRenderer(new Renderer(activity));
	}

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

	private static class Renderer implements GLSurfaceView.Renderer {
		private Activity activity;

		Renderer(Activity activity) {
			this.activity = activity;
		}

		public void onDrawFrame(GL10 gl) {
			GLES3JNILib.step();
		}

		public void onSurfaceChanged(GL10 gl, int width, int height) {
			GLES3JNILib.resize(width, height);
		}

		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			GLES3JNILib.init(activity);
		}
	}
}
