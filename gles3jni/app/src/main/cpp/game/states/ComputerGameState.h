#ifndef GLES3JNI_COMPUTERGAMESTATE_H
#define GLES3JNI_COMPUTERGAMESTATE_H

#include "AnimationGameState.h"

struct SkillUsage {
	Skill* skill;
	Unit* user;
	MapObject* target;
	Path path;
	float evaluation;
};

class ComputerGameState : public AnimationGameState {
public:
	ComputerGameState(Game* game);

	virtual void update(float deltaTime);

protected:
	virtual void onAnimationFinished();

private:
	Unit* pickUnit();
	SkillUsage getBestSkill(Unit* unit, Path& path, int maxRange, SkillUsage currentBest);
	SkillUsage getBestSkill(Unit* unit, Path& path, MapObject* target, Skill* skill, SkillUsage currentBest);
};

#endif //GLES3JNI_COMPUTERGAMESTATE_H
