#ifndef GLES3JNI_GAME_H
#define GLES3JNI_GAME_H

class GameState;
class Campaing;

#include "GameMap.h"
#include "AssetManager.h"
#include "Pipeline.h"
#include "states/GameState.h"
#include "Campaign.h"
#include <chrono>

class Game {
	typedef std::chrono::high_resolution_clock Clock;
	typedef Clock::time_point TimePoint;

public:
	Game();
	~Game();

	void initialize();
	void step();
	void resize(int width, int height);

	inline Pipeline* getPipeline() { return &pipeline; }
	inline AssetManager* getAssets() { return &assetManager; }
	inline GameState* getState() { return state.get(); }
	inline Campaign* getCampaign() { return campaign.get(); }

private:
	Pipeline pipeline;
	AssetManager assetManager;
	std::unique_ptr<Campaign> campaign;
	std::unique_ptr<GameState> state;
	TimePoint previousTime;
};

#endif //GLES3JNI_GAME_H
