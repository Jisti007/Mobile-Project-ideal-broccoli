#ifndef GLES3JNI_SCENARIOEVENT_H
#define GLES3JNI_SCENARIOEVENT_H

class ScenarioEvent {
public:
	virtual bool animate(float deltaTime) = 0;
	virtual void execute() = 0;
	virtual void cancel() = 0;
};

#endif //GLES3JNI_SCENARIOEVENT_H
