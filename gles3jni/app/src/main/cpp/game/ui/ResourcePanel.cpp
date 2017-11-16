//
// Created by K1697 on 16.11.2017.
//

#include "ResourcePanel.h"
#include "../states/MapGameState.h"
#include <algorithm>
#include <sstream>

ResourcePanel::ResourcePanel(Sprite* sprite, glm::vec2 position, Font* font, Scenario* scenario) : UISprite(sprite, position) {
	this->font = font;
/*	resourceLabel = new Label(
		u8"609", font,
		glm::vec2{getLeft() + 50, getTop() - getSprite()->getHeight() / 2.0f},
		glm::vec2{400,200}
	);

	std::unique_ptr<UIObject> resourceLabelPointer(resourceLabel);
	addChild(resourceLabelPointer);

	auto playerResources = scenario->getPlayerFaction()->getResources();
	std::vector<Resource*> resourceList;

	for (auto const& playerResource : playerResources)
	{
		resourceList.push_back(playerResource.first);

	}

	std::sort(resourceList.begin(), resourceList.end(), ResourceSorter());

	int resourceOffset = 50;
	for (auto const& playerResource : resourceList) {
		auto resourceUISprite = playerResource->getSprite();

		auto resourceIcon = new UISprite(
			resourceUISprite, glm::vec2{getLeft() + resourceOffset, getTop() - getSprite()->getHeight() / 2.0f}, 0.4f);
		std::unique_ptr<UIObject> resourceIconPointer(resourceIcon);
		addChild(resourceIconPointer);

		resourceOffset += resourceUISprite->getWidth()*resourceIcon->getScale();

		auto resourceAmount = playerResources[playerResource];
		std::stringstream resourceString;
		resourceString << resourceAmount;

		auto resourceAmountLabel = new Label(
			resourceString.str().c_str(), font,
			glm::vec2{getLeft() + resourceOffset, getTop() - getSprite()->getHeight() / 2.0f},
			glm::vec2{0,0});
		std::unique_ptr<UIObject> resourceAmountLabelPointer(resourceAmountLabel);
		addChild(resourceAmountLabelPointer);

		resourceOffset += 100;
	}*/

}

ResourcePanel::~ResourcePanel() {

}

void ResourcePanel::updateResources(Scenario* scenario) {
	getChildren().clear();
	auto playerResources = scenario->getPlayerFaction()->getResources();
	std::vector<Resource*> resourceList;

	for (auto const& playerResource : playerResources)
	{
		resourceList.push_back(playerResource.first);

	}

	std::sort(resourceList.begin(), resourceList.end(), ResourceSorter());

	int resourceOffset = 50;
	for (auto const& playerResource : resourceList) {
		auto resourceUISprite = playerResource->getSprite();

		auto resourceIcon = new UISprite(
			resourceUISprite, glm::vec2{getLeft() + resourceOffset, getTop() - getSprite()->getHeight() / 2.0f}, 0.4f);
		std::unique_ptr<UIObject> resourceIconPointer(resourceIcon);
		addChild(resourceIconPointer);

		resourceOffset += resourceUISprite->getWidth()*resourceIcon->getScale();

		auto resourceAmount = playerResources[playerResource];
		std::stringstream resourceString;
		resourceString << resourceAmount;

		auto resourceAmountLabel = new Label(
			resourceString.str().c_str(), font,
			glm::vec2{getLeft() + resourceOffset, getTop() - getSprite()->getHeight() / 2.0f},
			glm::vec2{0,0});
		std::unique_ptr<UIObject> resourceAmountLabelPointer(resourceAmountLabel);
		addChild(resourceAmountLabelPointer);

		resourceOffset += 100;
	}
}
