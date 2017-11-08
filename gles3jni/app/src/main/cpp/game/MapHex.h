#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

class GameMap;
class MapRegion;
class Unit;

#include "HexType.h"
#include "Unit.h"
#include "GameMap.h"
#include "MapRegion.h"
#include "pathing/Comparable.h"
#include "pathing/Node.h"

class MapHex : public MapObject, public Node {
public:
	//MapHex();
	MapHex(uint16_t gridX, uint16_t gridY, glm::vec2 position, HexType* type);
	virtual ~MapHex();

	virtual float getHeuristic(Node* destination);

	void initializeNeighbors(GameMap* map);
	void setRegion(MapRegion* region);

	virtual Sprite* getSprite() {return type->getSprite(); }
	inline const std::vector<MapHex*>& getNeighbors() const { return neighbors; }
	inline const MapRegion* getRegion() const { return region; }
	inline const HexType* getType() const { return type; }
	inline Unit* getUnit() { return unit; }
	inline void setUnit(Unit* unit) { this->unit = unit; }

private:
	std::vector<MapHex*> neighbors;
	MapRegion* region;
	HexType* type;
	Unit* unit;

	void addNeighbor(GameMap* map, int x, int y);
};

#endif //GLES3JNI_MAPHEX_H
