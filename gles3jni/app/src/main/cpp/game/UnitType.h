#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Skill.h"
#include "Buff.h"
#include "Resource.h"

class UnitType {
public:
	typedef std::vector<std::unique_ptr<Skill>> SkillList;
	typedef std::vector<std::unique_ptr<Buff>> BuffList;

	UnitType(
		Sprite* sprite, std::string name, int hp, int defense, int movement,
		SkillList& skills, BuffList& buffs, ResourceAmountList upkeep
	);

	const std::vector<Skill*> getValidSkills(MapObject* user, MapObject* target) const;
	int getMaxSkillRange() const;
	int getDamageModifierAgainst(Damage* damage);

	inline Sprite* getSprite() const { return sprite; }
	inline const int getHP() const { return hp; }
	inline const std::string getName() const { return name; };
	inline const int getDefense() const { return defense; }
	inline const int getMovement() const { return movement; }
	inline const SkillList& getSkills() const { return skills; };
	inline const ResourceAmountList& getUpkeep() const { return upkeep; }

private:
	Sprite* sprite;
	std::string name;
	int hp, defense, movement;
	SkillList skills;
	BuffList buffs;
	ResourceAmountList upkeep;
};

#endif //GLES3JNI_UNITTYPE_H
