#ifndef GLES3JNI_CAMPAIGN_H
#define GLES3JNI_CAMPAIGN_H

#include <memory>
#include "Scenario.h"

class Campaign {
public:
	Campaign();
	~Campaign();

	inline Scenario* getScenario() { return scenario.get(); }

private:
	std::unique_ptr<Scenario> scenario;
};

#endif //GLES3JNI_CAMPAIGN_H
