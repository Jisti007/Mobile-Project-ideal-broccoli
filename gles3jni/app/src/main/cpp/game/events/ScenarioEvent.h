#ifndef GLES3JNI_SCENARIOEVENT_H
#define GLES3JNI_SCENARIOEVENT_H

class ScenarioEvent {
public:
	/*
	virtual void beginAnimation() = 0;
	/// Returns true when animation is finished.
	virtual bool animate(float deltaTime) = 0;
	virtual void endAnimation() = 0;
	*/
	virtual bool execute() = 0;
	virtual bool cancel() = 0;
};

#endif //GLES3JNI_SCENARIOEVENT_H
