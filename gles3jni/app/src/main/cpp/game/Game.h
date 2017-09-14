#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"

class Game {
public:
    GameMap* map;

    Game(AssetManager *assetManager);
    ~Game();

	void update();
	void draw();

private:
	AssetManager* assetManager;
};


#endif //GLES3JNI_GAME_H
