#include "InfoPanel.h"

InfoPanel::InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager, Game* game)
	: UISprite(sprite, position) {
	this->font = font;
	this->assetManager = assetManager;
	this->game = game;
}

InfoPanel::~InfoPanel() {

}

void InfoPanel::updateInfo(Unit* unit) {
	getChildren().clear();

	auto infoPanelSprite = assetManager->getSprite("ui_info");
	auto unitType = unit->getType();

	auto unitUISprite = unitType->getSprite();
	auto unitIcon = addNewChild<UISprite>(
		unitUISprite,
		glm::vec2{0 - infoPanelSprite->getWidth() / 3, 0},
		2.4f
	);

	auto unitName = unitType->getName();
	auto maxHP = unitType->getHP();
	auto currentHP = unit->getHP();
	auto defense = unitType->getDefense();
	auto movement = unitType->getMovement();

	std::stringstream nameString;
	nameString << unitName;

	auto nameLabel = addNewChild<Label>(
		nameString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f},
		glm::vec2{100,20}
	);

	std::stringstream hpString;
	hpString << "HP: " << currentHP << "/" << maxHP;

	auto hpLabel = addNewChild<Label>(
		hpString.str().c_str(),
		font,
		glm::vec2{0, 0 + 100},
		glm::vec2{100,20}
	);

	std::stringstream defenseString;
	defenseString << "Defense: " << defense;

	auto defenseLabel = addNewChild<Label>(
		defenseString.str().c_str(),
		font,
		glm::vec2{0, hpLabel->getBottom() - hpLabel->getSize().y},
		glm::vec2{100,20}
	);

	std::stringstream movementString;
	movementString << "Movement: " << movement;

	auto movementLabel = addNewChild<Label>(
		movementString.str().c_str(),
		font,
		glm::vec2{0, defenseLabel->getBottom() - defenseLabel->getSize().y},
		glm::vec2{100,20}
	);




	std::stringstream skillString;
	int skillOffset = 50;

	for (auto& skill : unitType->getSkills()){
		auto skillName = skill->getName();
		auto skillSprite = skill->getSprite();
		auto description = skill->getDescription();
		auto cost = skill->getCost();
		auto range = skill->getRange();
		//auto effects = skill->getEffects();
		auto target = skill->getTargetType();

		auto skillIcon = addNewChild<UISprite>(
			skillSprite,
			glm::vec2{0,movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
			0.75f
		);

		skillString << skillName;
		auto skillLabel = addNewChild<Label>(
			skillString.str().c_str(),
			font,
			glm::vec2{skillIcon->getPosition().x + skillIcon->getSize().x / 2.0f, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
			glm::vec2{100,20}
		);

		skillOffset += skillIcon->getSize().y + skillLabel->getSize().y;

		skillString.str(std::string());
	}

	auto exitButtonSprite = assetManager->getSprite("no_button");
	auto exitButton = addNewChild<Button>(
		exitButtonSprite,
		glm::vec2{getRight() -  exitButtonSprite->getWidth() / 2, getTop() + exitButtonSprite->getHeight() / 2},
		glm::vec2{0,0}
	);
	//exitButton->setOnPress(std::bind(&Game::popState, game));


}
