#ifndef GLES3JNI_SCENARIO_H
#define GLES3JNI_SCENARIO_H

class Campaign;
class GameMap;

#include <vector>
#include <queue>
#include <memory>
#include "events/ScenarioEvent.h"
#include "GameMap.h"
#include "Campaign.h"

class Scenario {
public:
	Scenario(Campaign* campaign);
	~Scenario();

	void executeEvent(std::unique_ptr<ScenarioEvent>& event);
	void endTurn();

	inline Campaign* getCampaign() { return campaign; }
	inline GameMap* getActiveMap() { return maps[0].get(); }
	inline GameMap* getMap(size_t index) { return maps[index].get(); }
	inline size_t getMapCount() { return maps.size(); }
	inline Faction* getPlayerFaction() { return &factions[0]; }
	inline Faction* getActiveFaction() { return &factions[activeFactionIndex]; }
	inline Faction* getFaction(size_t index) { return &factions[index]; }
	inline size_t getFactionCount() { return factions.size(); }
	inline ScenarioEvent* peekAnimation() { return animationQueue.front(); }
	inline void popAnimation() { animationQueue.pop(); }
	inline size_t getAnimationCount() { return animationQueue.size(); }

private:
	Campaign* campaign;
	int turn = 1;
	size_t activeFactionIndex = 0;

	/// List of factions in the scenario. The player faction is 0 by default.
	std::vector<Faction> factions;
	/// All the maps that belong to the scenario.
	std::vector<std::unique_ptr<GameMap>> maps;
	/// List of events that have been executed.
	std::vector<std::unique_ptr<ScenarioEvent>> eventLog;
	/// Queue of events not yet animated.
	std::queue<ScenarioEvent*> animationQueue;
};

#endif //GLES3JNI_SCENARIO_H
