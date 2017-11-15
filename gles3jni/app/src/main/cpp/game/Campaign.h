#ifndef GLES3JNI_CAMPAIGN_H
#define GLES3JNI_CAMPAIGN_H

class Game;
class Scenario;

#include <memory>
#include "Scenario.h"
#include "Game.h"

class Campaign {
public:
	Campaign(Game* game);
	~Campaign();

	inline Game* getGame() { return game; }
	inline Scenario* getScenario() { return scenario.get(); }

private:
	Game* game;
	std::unique_ptr<Scenario> scenario;
};

#endif //GLES3JNI_CAMPAIGN_H
