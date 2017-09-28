#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"

class Game {
public:
    Game();
    ~Game();

	void initialize();
	void update();
	void draw();

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;
};


#endif //GLES3JNI_GAME_H
