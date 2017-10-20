#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"
#include "ui/GameUI.h"

class Game {
public:
    Game();
    ~Game();

	void initialize();
	void update();
	void draw();
	void onMove(float dx, float dy);
	void onResize(int width, int height);

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;
	GameUI ui;
};

#endif //GLES3JNI_GAME_H
