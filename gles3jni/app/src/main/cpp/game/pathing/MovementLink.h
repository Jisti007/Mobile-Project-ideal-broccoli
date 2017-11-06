#ifndef GLES3JNI_MOVEMENTLINK_H
#define GLES3JNI_MOVEMENTLINK_H

#include "Link.h"
#include "../MapHex.h"

class MovementLink : public Link {
public:
	MovementLink(MapHex* source, MapHex* destination);

	virtual float getCost(Agent* agent, float pathCost);
};

#endif //GLES3JNI_MOVEMENTLINK_H
