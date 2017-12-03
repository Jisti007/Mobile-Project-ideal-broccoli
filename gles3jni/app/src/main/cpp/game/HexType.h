#ifndef GLES3JNI_HEXTYPE_H
#define GLES3JNI_HEXTYPE_H

#include "Texture.h"
#include "Mesh.h"
#include "Sprite.h"
#include "WeightedList.h"

class Decoration {
public:
	Decoration(Sprite* sprite);

	inline Sprite* getSprite() { return sprite; }

private:
	Sprite* sprite;
};

class HexType {
public:
	HexType(
		Sprite* sprite, float movementCost,
		WeightedList<Decoration> decorations,
		int minDecorations, int maxDecorations, float decorationDistance
	);

	std::vector<Sprite*> getRandomDecorations() const;

	inline Sprite* getSprite() const { return sprite; }
	inline const float getMovementCost() const { return movementCost; }
	inline const float getDecorationDistance() const { return decorationDistance; }

private:
	Sprite* sprite;
	float movementCost;
	WeightedList<Decoration> decorations;
	int minDecorations;
	int maxDecorations;
	float decorationDistance;
};

#endif //GLES3JNI_HEXTYPE_H
