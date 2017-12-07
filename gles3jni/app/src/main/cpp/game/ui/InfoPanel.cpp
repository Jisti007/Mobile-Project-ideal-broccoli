#include <sstream>
#include "InfoPanel.h"

InfoPanel::InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager)
	: UISprite(sprite, position) {
	this->font = font;
	this->assetManager = assetManager;
}

InfoPanel::~InfoPanel() {

}

void InfoPanel::updateInfo(Unit* unit) {
	getChildren().clear();

	//unit sprite
	auto unitType = unit->getType();

	auto infoUISprite = unitType->getSprite();
	auto unitIcon = new UISprite(
		infoUISprite,
		glm::vec2{getLeft(), getSize().x / 1.5f},
		1.0f
	);
	std::unique_ptr<UIObject> unitIconPointer(unitIcon);
	addChild(unitIconPointer);

	//unit status
	auto maxHP = unitType->getHP();
	auto currentHP = unit->getHP();
	auto defense = unitType->getDefense();
	auto movement = unitType->getMovement();
	//auto skill = unitType->getSkills();

	std::stringstream hpString;
	hpString << "HP: " << currentHP << "/" << maxHP;

	std::stringstream defenseString;
	hpString << "Defense: " << defense;

	std::stringstream movementString;
	hpString << "Movement: " << movement;

	auto hpLabel = new Label(
		hpString.str().c_str(),
		font,
		glm::vec2{getSize().x / 2.0f, getSize().y / 1.5f},
		glm::vec2{0,0}
	);
	std::unique_ptr<UIObject> hpLabelPointer(hpLabel);
	addChild(hpLabelPointer);

	auto defenseLabel = new Label(
		defenseString.str().c_str(),
		font,
		glm::vec2{getSize().x / 2.0f, getSize().y - hpLabel->getSize().y / 1.5f},
		glm::vec2{0,0}
	);
	std::unique_ptr<UIObject> defenseLabelPointer(defenseLabel);
	addChild(defenseLabelPointer);

	auto movementLabel = new Label(
		movementString.str().c_str(),
		font,
		glm::vec2{getSize().x / 2.0f, getSize().y - defenseLabel->getSize().y / 1.5f},
		glm::vec2{0,0}
	);
	std::unique_ptr<UIObject> movementLabelPointer(movementLabel);
	addChild(movementLabelPointer);

	//exit button

	auto exitButtonSprite = assetManager->getSprite("no_button");
	auto exitButton = addNewChild<Button>(
		exitButtonSprite,
		glm::vec2{getSize().x / 2.0f, getSize().y - defenseLabel->getSize().y / 1.5f},
		glm::vec2{0,0}
	);

}
