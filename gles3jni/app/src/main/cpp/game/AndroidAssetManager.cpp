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
		int nb_read = 0;
		FILE *out = fopen(filename, "w");
		while ((nb_read = AAsset_read(asset, buffer, BUFSIZ)) > 0) {
			fwrite(buffer, nb_read, 1, out);
		}
		fclose(out);
		AAsset_close(asset);
	}
	AAssetDir_close(assetDir);
}
