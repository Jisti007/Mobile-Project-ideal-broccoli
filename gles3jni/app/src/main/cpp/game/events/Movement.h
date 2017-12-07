#ifndef GLES3JNI_MOVEMENT_H
#define GLES3JNI_MOVEMENT_H

#include "../MapHex.h"
#include "ScenarioEvent.h"

class Movement : public ScenarioEvent {
public:
	Movement(Unit* unit, Path path);
	virtual ~Movement();

	virtual bool execute();
	virtual bool cancel();

private:
	Unit* unit;
	Path path;
	//std::list<Link*> animationPath;
};

#endif //GLES3JNI_MOVEMENT_H
