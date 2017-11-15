#include <jni.h>
#include <stdlib.h>
#include <unistd.h>

#include "game/Game.h"

Game game;
int screenWidth;
int screenHeight;

extern "C" {
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_initialize(JNIEnv *env, jobject obj, jobject activity);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_onMove(JNIEnv *env, jobject obj, jfloat dx, jfloat dy);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_onPress(JNIEnv *env, jobject obj, jfloat x, jfloat y);
};

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
	return GL_TRUE;
}
#endif

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_initialize(JNIEnv *env, jobject obj, jobject activity) {
	JavaVM *vm;
	env->GetJavaVM(&vm);
	vm->AttachCurrentThread(&env, NULL);

	jclass activityClass = env->GetObjectClass(activity);
	jmethodID getCacheDir = env->GetMethodID(activityClass, "getFilesDir", "()Ljava/io/File;");
	jobject file = env->CallObjectMethod(activity, getCacheDir);
	jclass fileClass = env->FindClass("java/io/File");
	jmethodID getAbsolutePath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
	jstring jpath = (jstring)env->CallObjectMethod(file, getAbsolutePath);
	const char* appDirectory = env->GetStringUTFChars(jpath, NULL);
	//LOGI("appDirectory: %s", appDirectory);
	chdir(appDirectory);
	env->ReleaseStringUTFChars(jpath, appDirectory);

	game.initialize();
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height) {
	screenWidth = width;
	screenHeight = height;
	//game.getPipeline().setViewportSize(width, height);
	game.resize(width, height);
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj) {
	game.update();
	game.draw();
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_onMove(JNIEnv *env, jobject obj, jfloat dx, jfloat dy) {
	game.getState()->move(dx, dy);
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_onPress(JNIEnv *env, jobject obj, jfloat x, jfloat y) {
	x -= screenWidth/2;
	y = screenHeight/2 - y;
	game.getState()->press(x, y);
}
