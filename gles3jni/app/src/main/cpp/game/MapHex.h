#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

class GameMap;
class MapRegion;

#include "HexType.h"
#include "Unit.h"
#include "GameMap.h"
#include "MapRegion.h"

class MapHex : public MapObject {
public:
	MapHex();
	MapHex(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map);
	~MapHex();

	void initialize(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map);

	virtual Sprite* getSprite() {return type->getSprite(); }
	inline const std::vector<MapHex*>& getNeighbors() const { return neighbors; }
	inline const MapRegion* getRegion() const { return region; }
	inline void setRegion(MapRegion* region) { this->region = region; }
	inline const HexType* getType() const { return type; }

private:
	std::vector<MapHex*> neighbors;
	MapRegion* region;
	HexType* type;
	Unit* unit;

	void addNeighbor(GameMap* map, int x, int y);
};

#endif //GLES3JNI_MAPHEX_H
