package xyz.asdasd.gles3jni;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class LoadingActivity extends Activity {
	private String dataDirectory;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_loading);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		Thread extractionThread = new Thread() {
			@Override
			public void run() {
				dataDirectory = getFilesDir() + "/";
				extractFileOrDir("modules");
				Intent intent = new Intent(
					LoadingActivity.this, GLES3JNIActivity.class
				);
				startActivity(intent);
				finish();
			}
		};
		extractionThread.start();
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
			e.printStackTrace();
			//Log.e("main", "I/O Exception", e);
		}
	}

	private void extractFile(String filename) {
		try (
			InputStream in = getAssets().open(filename);
			OutputStream out = new FileOutputStream(dataDirectory + filename)
		) {
			byte[] buffer = new byte[32 * 1024];
			int numberOfBytesRead;
			while ((numberOfBytesRead = in.read(buffer)) != -1) {
				out.write(buffer, 0, numberOfBytesRead);
			}
			out.flush();
		} catch (Exception e) {
			e.printStackTrace();
			//Log.e("main", e.getMessage());
		}
	}
}
