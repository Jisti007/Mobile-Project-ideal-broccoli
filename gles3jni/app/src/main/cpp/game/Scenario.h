#ifndef GLES3JNI_SCENARIO_H
#define GLES3JNI_SCENARIO_H

#include <vector>
#include <queue>
#include <memory>
#include "events/ScenarioEvent.h"
#include "GameMap.h"

class Scenario {
public:
	Scenario();
	~Scenario();

	/// Returns the list of maps belonging to the scenario.
	inline std::vector<std::unique_ptr<GameMap>>& getMaps() { return maps; }
	inline std::vector<std::unique_ptr<ScenarioEvent>>& getEventLog() { return eventLog; }
	inline std::queue<std::unique_ptr<ScenarioEvent>>& getAnimationQueue() { return animationQueue; }

private:
	/// All the maps that belong to the scenario.
	std::vector<std::unique_ptr<GameMap>> maps;
	/// List of events that have been executed.
	std::vector<std::unique_ptr<ScenarioEvent>> eventLog;
	/// Queue of events not yet animated.
	std::queue<std::unique_ptr<ScenarioEvent>> animationQueue;
};

#endif //GLES3JNI_SCENARIO_H
