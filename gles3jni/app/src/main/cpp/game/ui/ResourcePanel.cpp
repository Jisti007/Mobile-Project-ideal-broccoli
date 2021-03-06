#include "ResourcePanel.h"
#include "../states/MapGameState.h"
#include <algorithm>
#include <sstream>

ResourcePanel::ResourcePanel(Sprite* sprite, glm::vec2 position, Font* font)
	: UISprite(sprite, position) {
	this->font = font;
}

ResourcePanel::~ResourcePanel() {

}

void ResourcePanel::updateResources(Scenario* scenario) {
	getChildren().clear();
	auto playerResources = scenario->getActiveFaction()->getResources();
	std::vector<Resource*> resourceList;

	for (auto const& playerResource : playerResources) {
		resourceList.push_back(playerResource.first);
	}

	std::sort(resourceList.begin(), resourceList.end(), ResourceSorter());

	int resourceOffset = 50;
	for (auto const& playerResource : resourceList) {
		auto resourceUISprite = playerResource->getSprite();
		auto resourceIcon = new UISprite(
			resourceUISprite,
			Transform2D{
				Translation{getLeft() + resourceOffset, getTop() - getSprite()->getHeight() / 2.0f},
				Scale{0.4f, 0.4f}
			}
		);
		std::unique_ptr<UIObject> resourceIconPointer(resourceIcon);
		addChild(resourceIconPointer);

		resourceOffset += resourceUISprite->getWidth() * resourceIcon->getScale().x;

		auto resourceAmount = playerResources[playerResource];
		std::stringstream resourceString;
		resourceString << resourceAmount;

		auto resourceAmountLabel = new Label(
			resourceString.str().c_str(),
			font,
			glm::vec2{resourceIcon->getRight() - 60, getTop() - resourceIcon->getSprite()->getHeight() / 2.5f},
			glm::vec2{resourceUISprite->getWidth() * 2.0f / 1.2f,resourceUISprite->getHeight() * 2.0f}
		);
		std::unique_ptr<UIObject> resourceAmountLabelPointer(resourceAmountLabel);
		addChild(resourceAmountLabelPointer);

		resourceOffset += 100;
	}
}
