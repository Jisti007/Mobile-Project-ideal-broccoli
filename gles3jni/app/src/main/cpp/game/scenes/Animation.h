#ifndef GLES3JNI_ANIMATION_H
#define GLES3JNI_ANIMATION_H

class Animation {
public:
	virtual bool animate(float deltaTime) = 0;
};

#endif //GLES3JNI_ANIMATION_H
