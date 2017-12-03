#include "HexType.h"

Decoration::Decoration(Sprite* sprite) {
	this->sprite = sprite;
}

HexType::HexType(
	Sprite* sprite, float movementCost,
	WeightedList<Decoration> decorations,
	int minDecorations, int maxDecorations, float decorationDistance
) {
	this->sprite = sprite;
	this->movementCost = movementCost;
	this->decorations = decorations;
	this->minDecorations = minDecorations;
	this->maxDecorations = maxDecorations;
	this->decorationDistance = decorationDistance;
}

std::vector<Sprite*> HexType::getRandomDecorations() const {
	int count = minDecorations;
	int range = maxDecorations - minDecorations;
	if (range > 0) {
		count += rand() % range;
	}
	std::vector<Sprite*> randomDecorations((size_t)count);
	for (int i = 0; i < count; i++) {
		randomDecorations[i] = decorations.getRandom().getSprite();
	}
	return randomDecorations;
}
