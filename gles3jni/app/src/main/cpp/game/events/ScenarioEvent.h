#ifndef GLES3JNI_SCENARIOEVENT_H
#define GLES3JNI_SCENARIOEVENT_H

class ScenarioEvent {
public:
	virtual bool execute() = 0;
	virtual bool cancel() = 0;
};

#endif //GLES3JNI_SCENARIOEVENT_H
