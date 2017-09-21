#include <jni.h>
#include <stdlib.h>
#include <memory>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <unistd.h>

#include "gles3jni.h"
#include "game/Game.h"

Game game;

extern "C" {
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_init(JNIEnv *env, jobject obj, jobject activity, jobject assetManager);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj);
};

void extractAssets(JNIEnv *env, jobject activity, jobject javaAssetManager);

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
	return GL_TRUE;
}
#endif

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_init(
	JNIEnv *env, jobject obj, jobject activity, jobject javaAssetManager
) {
	extractAssets(env, activity, javaAssetManager);
	game.initialize();
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height) {

}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj) {
	game.update();
	game.draw();
}

void extractAssets(JNIEnv *env, jobject activity, jobject javaAssetManager) {
	JavaVM *vm;
	env->GetJavaVM(&vm);
	vm->AttachCurrentThread(&env, NULL);

	jclass activityClass = env->GetObjectClass(activity);
	jmethodID getCacheDir = env->GetMethodID(activityClass, "getCacheDir", "()Ljava/io/File;");
	jobject file = env->CallObjectMethod(activity, getCacheDir);
	jclass fileClass = env->FindClass("java/io/File");
	jmethodID getAbsolutePath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
	jstring jpath = (jstring)env->CallObjectMethod(file, getAbsolutePath);
	const char* appDirectory = env->GetStringUTFChars(jpath, NULL);
	//LOGI("appDirectory: %s", appDirectory);
	chdir(appDirectory);
	env->ReleaseStringUTFChars(jpath, appDirectory);

	AAssetManager *assetManager = AAssetManager_fromJava(env, javaAssetManager);
	AAssetDir *assetDir = AAssetManager_openDir(assetManager, "");
	const char *filename;
	while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
		AAsset *asset = AAssetManager_open(assetManager, filename, AASSET_MODE_STREAMING);
		char buffer[BUFSIZ];
		int size = 0;
		const int count = 1;
		FILE *out = fopen(filename, "w");
		while ((size = AAsset_read(asset, buffer, BUFSIZ)) > 0) {
			fwrite(buffer, size, count, out);
		}
		fclose(out);
		AAsset_close(asset);
	}
	AAssetDir_close(assetDir);
}
