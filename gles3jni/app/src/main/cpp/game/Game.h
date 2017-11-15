#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"
#include "states/GameState.h"
#include <chrono>

class Game {
	typedef std::chrono::high_resolution_clock Clock;
	typedef Clock::time_point TimePoint;

public:
	Game();
	~Game();

	void initialize();
	void update();
	void draw();

	inline Pipeline& getPipeline() { return pipeline; }
	inline AssetManager& getAssets() { return assetManager; }
	inline GameState* getState() { return state.get(); }

private:
	Pipeline pipeline;
	AssetManager assetManager;
	GameMap map;
	std::unique_ptr<GameState> state;
	TimePoint previousTime;
};

#endif //GLES3JNI_GAME_H
