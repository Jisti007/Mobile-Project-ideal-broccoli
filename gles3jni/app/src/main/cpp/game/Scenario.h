#ifndef GLES3JNI_SCENARIO_H
#define GLES3JNI_SCENARIO_H

#include <vector>
#include <queue>
#include <memory>
#include "events/ScenarioEvent.h"
#include "GameMap.h"

class Scenario {
public:
	inline std::vector<std::unique_ptr<GameMap>>& getMaps() { return maps; }

private:
	std::vector<std::unique_ptr<GameMap>> maps;
	std::vector<std::unique_ptr<ScenarioEvent>> eventLog;
	std::queue<std::unique_ptr<ScenarioEvent>> eventQueue;
};

#endif //GLES3JNI_SCENARIO_H
