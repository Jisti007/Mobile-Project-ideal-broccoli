#ifndef GLES3JNI_ATTACK_H
#define GLES3JNI_ATTACK_H

#include "../Unit.h"

class Attack : public ScenarioEvent {
public:
	Attack(Unit* attacker, Unit* defender, int damage);
	virtual ~Attack();

	virtual void beginAnimation();
	virtual bool animate(float deltaTime);
	virtual void endAnimation();
	virtual bool execute();
	virtual bool cancel();

private:
	Unit* attacker;
	Unit* defender;
	int damage;
};

#endif //GLES3JNI_ATTACK_H
