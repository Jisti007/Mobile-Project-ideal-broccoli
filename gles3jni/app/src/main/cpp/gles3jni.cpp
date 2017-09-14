#include <jni.h>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <unistd.h>

#include "gles3jni.h"
#include "game/Game.h"
#include "game/AndroidAssetManager.h"

static std::unique_ptr<Game> game = NULL;
static std::unique_ptr<AndroidAssetManager> androidAssetManager = NULL;
//static Renderer *g_renderer = NULL;

extern "C" {
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_init(JNIEnv *env, jobject obj, jobject activity, jobject assetManager);
JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj);
};

#if !defined(DYNAMIC_ES3)

static GLboolean gl3stubInit() {
	return GL_TRUE;
}
#endif

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_init(
	JNIEnv *env, jobject obj, jobject activity, jobject javaAssetManager
) {
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
	androidAssetManager = std::unique_ptr<AndroidAssetManager>(
		new AndroidAssetManager(assetManager)
	);
	androidAssetManager->extractAssets();

	game = std::unique_ptr<Game>(new Game(androidAssetManager.get()));

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	/*
	if (g_renderer) {
		delete g_renderer;
		g_renderer = NULL;
	}

	printGlString("Version", GL_VERSION);
	printGlString("Vendor", GL_VENDOR);
	printGlString("Renderer", GL_RENDERER);
	printGlString("Extensions", GL_EXTENSIONS);

	const char *versionStr = (const char *) glGetString(GL_VERSION);
	if (strstr(versionStr, "OpenGL ES 3.") && gl3stubInit()) {
		g_renderer = createES3Renderer();
	} else if (strstr(versionStr, "OpenGL ES 2.")) {
		g_renderer = createES2Renderer();
	} else {
		ALOGE("Unsupported OpenGL ES version");
	}
	*/
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_resize(JNIEnv *env, jobject obj, jint width, jint height) {
	/*
	if (g_renderer) {
		g_renderer->resize(width, height);
	}
	*/
}

JNIEXPORT void JNICALL
Java_xyz_asdasd_gles3jni_GLES3JNILib_step(JNIEnv *env, jobject obj) {
	game->update();
	game->draw();
	/*
	if (g_renderer) {
		g_renderer->render();
	}
	*/
}
