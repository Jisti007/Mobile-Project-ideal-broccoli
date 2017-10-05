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
	void onTouch(float x, float y);

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;

	float previousX, previousY;
};

#endif //GLES3JNI_GAME_H
