#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

class GameMap;

#include "UnitType.h"
#include "MapObject.h"
#include "Faction.h"
#include "GameMap.h"
#include "pathing/Agent.h"

class Unit : public MapObject, public Agent {
public:
	Unit(uint16_t gridX, uint16_t gridY, glm::vec2 position, UnitType *type, Faction* faction, GameMap* map);
	virtual ~Unit();

	virtual Sprite* getSprite() {return type->getSprite(); }

	bool moveTo(MapHex* destination);

	inline const UnitType* getType() const { return type; }
	inline const Faction* getFaction() const { return faction; }
	inline int getHP() { return hp; }
	inline void setHP(int hp) { this->hp = hp; }
	inline void modifyHP(int deltaHP) { this->hp += deltaHP; }

private:
    UnitType* type;
	Faction* faction;
	GameMap* map;
	int hp;
};

#endif //GLES3JNI_UNIT_H
