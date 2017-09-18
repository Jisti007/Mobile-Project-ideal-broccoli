#include "AndroidAssetManager.h"
#include <cstdio>

AndroidAssetManager::AndroidAssetManager(AAssetManager* handle) {
	this->handle = handle;
}

AndroidAssetManager::~AndroidAssetManager() {

}

void AndroidAssetManager::extractAssets() {
	AAssetDir *assetDir = AAssetManager_openDir(handle, "");
	const char *filename;
	while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
		AAsset *asset = AAssetManager_open(handle, filename, AASSET_MODE_STREAMING);
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
