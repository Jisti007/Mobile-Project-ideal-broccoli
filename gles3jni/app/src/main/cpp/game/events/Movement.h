#ifndef GLES3JNI_MOVEMENT_H
#define GLES3JNI_MOVEMENT_H

#include "../MapHex.h"
#include "ScenarioEvent.h"

class Movement : public ScenarioEvent {
public:
	Movement(Unit* unit, MapHex* destination);
	virtual ~Movement();

	virtual bool animate(float deltaTime);
	virtual void execute();
	virtual void cancel();

private:
	Unit* unit;
	MapHex* source;
	MapHex* destination;
};

#endif //GLES3JNI_MOVEMENT_H
