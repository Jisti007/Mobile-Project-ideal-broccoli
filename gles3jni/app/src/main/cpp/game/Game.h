#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"
#include "states/GameState.h"
#include <chrono>

class Game {
public:
	Game();
	~Game();

	void initialize();
	void update();
	void draw();
	void resize(int width, int height);

	inline GameState* getState() { return state.get(); }

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;
	std::unique_ptr<GameState> state;
	std::chrono::high_resolution_clock::time_point previousTime;
};

#endif //GLES3JNI_GAME_H
