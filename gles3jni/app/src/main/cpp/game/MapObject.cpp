#include <cstdlib>
#include "MapObject.h"

MapObject::MapObject(uint16_t gridX, uint16_t gridY) {
	this->gridX = gridX;
	this->gridY = gridY;
}

MapObject::~MapObject() {

}

int MapObject::getDistance(MapObject* other) {
	Point3D cube = getCubePosition();
	Point3D otherCube = other->getCubePosition();
	return (
		abs(cube.x - otherCube.x)
		+ abs(cube.y - otherCube.y)
		+ abs(cube.z - otherCube.z)
	) / 2;
}

Point3D MapObject::getCubePosition() {
	int x = getGridX();
	int z = getGridY() - (getGridX() + (getGridX() & 1)) / 2;
	int y = -x - z;
	return Point3D{x, y, z};
}
