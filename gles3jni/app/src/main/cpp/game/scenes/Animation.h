#ifndef GLES3JNI_ANIMATION_H
#define GLES3JNI_ANIMATION_H

class Animation {
public:
	Animation(bool blocking = true);

	virtual bool animate(float deltaTime) = 0;

	bool isBlocking() { return blocking; }

private:
	bool blocking;
};

#endif //GLES3JNI_ANIMATION_H
