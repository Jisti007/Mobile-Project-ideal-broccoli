#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

class GameMap;
class MapRegion;
class Unit;

#include "HexType.h"
#include "Unit.h"
#include "Building.h"
#include "GameMap.h"
#include "MapRegion.h"
#include "pathing/Comparable.h"
#include "pathing/Node.h"

class MapHex : public MapObject, public Node {
public:
	MapHex(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map);
	virtual ~MapHex();

	virtual float getHeuristic(Node* destination);

	std::vector<MapHex*> getHexesWithin(int radius);
	void initializeNeighbors();
	void setRegion(MapRegion* region);
	void clearDecorations();
	void createDecorations();

	virtual Sprite* getSprite() { return type->getSprite(); }
	inline const std::vector<MapHex*>& getNeighbors() const { return neighbors; }
	inline const MapRegion* getRegion() const { return region; }
	inline const HexType* getType() const { return type; }
	inline Unit* getUnit() { return unit; }
	inline void setUnit(Unit* unit) { this->unit = unit; }
	inline Building* getBuilding() { return building; }
	inline void setBuilding(Building* building) { this->building = building; }

private:
	std::vector<MapHex*> neighbors;
	std::vector<Actor*> decorations;
	GameMap* map;
	MapRegion* region;
	HexType* type;
	Unit* unit = nullptr;
	Building* building = nullptr;

	void addNeighbor(GameMap* map, int x, int y);
};

#endif //GLES3JNI_MAPHEX_H
