#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

class GameMap;
class MapHex;

#include "UnitType.h"
#include "MapObject.h"
#include "Faction.h"
#include "GameMap.h"
#include "pathing/Agent.h"
#include "scenes/Actor.h"
#include "pathing/Path.h"

class Unit : public MapObject, public Agent {
public:
	Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction, GameMap* map);
	virtual ~Unit();

	virtual Sprite* getSprite() {return type->getSprite(); }

	bool move(Path& path);
	bool moveTo(MapHex* destination);
	void die();
	void setHP(int hp);
	void onBeginTurn();
	MapHex* getHex();
	bool isFriendlyTowards(Unit* other);

	inline GameMap* getMap() { return map; }
	//inline MapHex* getHex() { return map->tryGetHex(getGridPosition()); }
	inline const UnitType* getType() const { return type; }
	inline const Faction* getFaction() const { return faction; }
	inline int getHP() { return hp; }
	inline void modifyHP(int deltaHP) { setHP(hp + deltaHP); }
	inline float getMovement() { return movementRemaining; }
	inline void modifyMovement(float deltaMovement) { movementRemaining += deltaMovement; }
	inline bool isHostileTowards(Unit* other) { return !isFriendlyTowards(other); }

private:
    UnitType* type;
	Faction* faction;
	GameMap* map;
	int hp;
	float movementRemaining;
	bool movable = true;
};

#endif //GLES3JNI_UNIT_H
