#ifndef GLES3JNI_SKILL_H
#define GLES3JNI_SKILL_H

#include "Sprite.h"
#include "MapObject.h"
#include "scenes/Scene.h"
#include "DamageType.h"

typedef MapObject SkillUser;
typedef MapObject SkillTarget;



class Effect {
public:
	virtual void apply(SkillUser* user, SkillTarget* target) = 0;
	/// Helps the AI evaluate the value of an action that will have this effect.
	/// The higher the returned number, the better for the AI.
	virtual float evaluate(SkillUser* user, SkillTarget* target, float cost) = 0;
};

class Damage : public Effect {
public:
	Damage(DamageType* type, int amount);

	virtual void apply(SkillUser* user, SkillTarget* target);
	virtual float evaluate(SkillUser* user, SkillTarget* target, float cost);

	inline const DamageType* getType() const { return type; }
	inline const int getAmount() const { return amount; }

private:
	DamageType* type;
	int amount;

	int calculateDamage(SkillUser* user, SkillTarget* target);
};

class HPModification : public Effect {
public:
	HPModification(int amount);

	virtual void apply(SkillUser* user, SkillTarget* target);
	virtual float evaluate(SkillUser* user, SkillTarget* target, float cost);

private:
	int amount;
};

class SkillAnimation {
public:
	enum Role {
		user,
		target
	};

	virtual void queue(SkillUser* user, SkillTarget* target) = 0;
};

class SourceDestination : public SkillAnimation {
public:
	SourceDestination(SkillAnimation::Role source, SkillAnimation::Role destination);

	Actor* getSourceActor(SkillUser* user, SkillTarget* target);
	Actor* getDestinationActor(SkillUser* user, SkillTarget* target);

protected:
	SkillAnimation::Role source;
	SkillAnimation::Role destination;
};

class Nudge : public SourceDestination {
public:
	Nudge(SkillAnimation::Role source, SkillAnimation::Role destination, float distance);

	virtual void queue(SkillUser* user, SkillTarget* target);

private:
	float distance;
};

class Projectile : public SourceDestination {
public:
	Projectile(
		Sprite* sprite, SkillAnimation::Role source,
		SkillAnimation::Role destination, float speed
	);

	virtual void queue(SkillUser* user, SkillTarget* target);

private:
	Sprite* sprite;
	float speed;
};

enum TargetType {
	enemy,
	friendly,
	unit,
	hex
};

class Skill {
public:
	typedef std::vector<std::unique_ptr<Effect>> EffectList;
	typedef std::vector<std::unique_ptr<SkillAnimation>> AnimationList;

	Skill(
		Sprite* sprite, std::string name, std::string description, TargetType targetType, int range, float cost,
		EffectList& effects, AnimationList& animations
	);

	void use(SkillUser* user, SkillTarget* target);
	/// Helps the AI evaluate the value of using this skill.
	/// The higher the returned number, the better for the AI.
	float evaluate(SkillUser* user, SkillTarget* target, float extraCost);
	/// Returns true if the rules allow the user to use this skill against the target.
	bool validate(SkillUser* user, SkillTarget* target, float extraCost);
	/// Returns true if the rules allow the user to use this skill against the target.
	bool validate(SkillUser* user, SkillTarget* target, float extraCost, int range);

	inline Sprite* getSprite() const { return sprite; }
	inline const std::string getName() const { return name; }
	inline const std::string getDescription() const { return description; }
	inline const TargetType getTargetType() const { return targetType; }
	inline const int getRange() const { return range; }
	inline const float getCost() const { return cost; }
	inline const EffectList& getEffects() const { return effects; }

private:
	Sprite* sprite;
	std::string name;
	std::string description;
	TargetType targetType;
	int range;
	float cost;
	EffectList effects;
	AnimationList animations;
};

#endif //GLES3JNI_SKILL_H
