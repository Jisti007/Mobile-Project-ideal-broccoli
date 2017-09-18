#ifndef GLES3JNI_ASSETMANAGER_H
#define GLES3JNI_ASSETMANAGER_H

#include <vector>
#include "Texture.h"

class AssetManager {
public:
	AssetManager();
	virtual ~AssetManager();

	virtual Texture* loadTexture(const char* filePath);

private:
	std::vector<Texture*> textures;
};

#endif //GLES3JNI_ASSETMANAGER_H
