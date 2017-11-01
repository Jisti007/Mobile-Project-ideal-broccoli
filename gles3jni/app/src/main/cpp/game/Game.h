#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"
#include "states/GameState.h"

class Game {
public:
	Game();
	~Game();

	void initialize();
	void update();
	void draw();
	void onMove(float dx, float dy);
	void onResize(int width, int height);
	void onPress(float x, float y);

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;
	std::unique_ptr<GameState> state;
};

#endif //GLES3JNI_GAME_H
