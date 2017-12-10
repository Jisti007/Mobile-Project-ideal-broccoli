#ifndef GLES3JNI_TRANSFORM2D_H
#define GLES3JNI_TRANSFORM2D_H

#include "../glm/glm.hpp"

typedef glm::vec2 Translation;
typedef glm::vec2 Scale;

struct Transform2D {
	Translation translation;
	Scale scale;
};

#endif //GLES3JNI_TRANSFORM2D_H
