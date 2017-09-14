#ifndef GLES3JNI_ANDROIDASSETMANAGER_H
#define GLES3JNI_ANDROIDASSETMANAGER_H

#include "AssetManager.h"
#include <android/asset_manager.h>

class AndroidAssetManager : public AssetManager {
public:
	AndroidAssetManager(AAssetManager* handle);
	~AndroidAssetManager();

	void extractAssets();

private:
	AAssetManager* handle;
};

#endif //GLES3JNI_ANDROIDASSETMANAGER_H
