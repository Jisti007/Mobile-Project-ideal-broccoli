#ifndef GLES3JNI_SCENARIO_H
#define GLES3JNI_SCENARIO_H

class Campaign;

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

	inline GameMap* getActiveMap() { return maps[0].get(); }
	inline GameMap* getMap(size_t index) { return maps[index].get(); }
	inline size_t getMapCount() { return maps.size(); }

private:
	Campaign* campaign;

	/// All the maps that belong to the scenario.
	std::vector<std::unique_ptr<GameMap>> maps;
	/// List of events that have been executed.
	std::vector<std::unique_ptr<ScenarioEvent>> eventLog;
	/// Queue of events not yet animated.
	std::queue<std::unique_ptr<ScenarioEvent>> animationQueue;
};

#endif //GLES3JNI_SCENARIO_H
