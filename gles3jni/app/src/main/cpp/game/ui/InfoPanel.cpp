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
		Transform2D{
			Translation{0 - infoPanelSprite->getWidth() / 3, 0},
			Scale{2.4f, 2.4}
		}
	);

	auto unitName = unitType->getName();
	auto maxHP = unitType->getHP();
	auto currentHP = unit->getHP();
	auto defense = unitType->getDefense();
	auto movement = unitType->getMovement();

	std::stringstream nameString;
	nameString << unitName;

	nameLabel = addNewChild<Label>(
		nameString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f},
		glm::vec2{100,20}
	);

	std::stringstream hpString;
	hpString << "HP: " << currentHP << "/" << maxHP;

	hpLabel = addNewChild<Label>(
		hpString.str().c_str(),
		font,
		glm::vec2{0, 0 + 100},
		glm::vec2{100,20}
	);

	std::stringstream defenseString;
	defenseString << "Defense: " << defense;

	defenseLabel = addNewChild<Label>(
		defenseString.str().c_str(),
		font,
		glm::vec2{0, hpLabel->getBottom() - hpLabel->getSize().y},
		glm::vec2{100,20}
	);

	std::stringstream movementString;
	movementString << "Movement: " << movement;

	movementLabel = addNewChild<Label>(
		movementString.str().c_str(),
		font,
		glm::vec2{0, defenseLabel->getBottom() - defenseLabel->getSize().y},
		glm::vec2{100,20}
	);

	std::stringstream skillString;
	int skillOffset = 30;

	for (auto& skill : unitType->getSkills()){

		auto skillSprite = skill->getSprite();
		auto skillIcon = addNewChild<UISprite>(
			skillSprite,
			Transform2D{
				Translation{0, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
				Scale{0.75f, 0.75f}
			}
		);

		//TODO: Make this a bit smoother
		/*auto name = skill->getName();
		auto description = skill->getDescription();
		auto cost = skill->getCost();
		auto range = skill->getRange();
		auto effects = skill->getEffects();
		auto target = skill->getTargetType();*/

		newStringLabel(skill->getName(), -30 + skillOffset);
		newStringLabel(skill->getDescription(), -10 + skillOffset);
		newStringLabel("Cost: ", skill->getCost(), 10 + skillOffset);
		newStringLabel("Range: ", skill->getRange(), 30 + skillOffset);

		/*skillString << skillName;
		auto skillLabel = addNewChild<Label>(
			skillString.str().c_str(),
			font,
			glm::vec2{skillIcon->getPosition().x + skillIcon->getSize().x / 2.0f, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
			glm::vec2{100,20}
		);*/

		skillOffset += skillIcon->getSize().y;

		skillString.str(std::string());
	}

	auto exitButtonSprite = assetManager->getSprite("no_button");
	auto exitButton = addNewChild<Button>(
		exitButtonSprite,
		glm::vec2{
			getRight() - exitButtonSprite->getWidth() / 2,
			getTop() + exitButtonSprite->getHeight() / 2
		},
		glm::vec2{0,0}
	);
	//exitButton->setOnPress(std::bind(&Game::popState, game));

}

void InfoPanel::updateInfo(Building* building) {
	getChildren().clear();

	auto infoPanelSprite = assetManager->getSprite("ui_info");
	auto buildingType = building->getType();

	auto buildingUISprite = buildingType->getSprite();
	auto buildingIcon = addNewChild<UISprite>(
		buildingUISprite,
		Transform2D{
			Translation{0 - infoPanelSprite->getWidth() / 3, 0},
			Scale{2.4f, 2.4f}
		}
	);

	auto buildingName = buildingType->getName();
	auto buildingDescription = buildingType->getDescription();

	std::stringstream nameString;
	nameString << buildingName;

	nameLabel = addNewChild<Label>(
		nameString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f},
		glm::vec2{100,20}
	);

	std::stringstream descriptionString;
	descriptionString << buildingDescription;

	/*descriptionLabel = addNewChild<Label>(
		descriptionString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f - nameLabel->getSize().y},
		glm::vec2{100,20}
	);*/

	/*
	std::stringstream skillString;
	int skillOffset = 30;

	for (auto& skill : unitType->getSkills()){

		auto skillSprite = skill->getSprite();
		auto skillIcon = addNewChild<UISprite>(
			skillSprite,
			glm::vec2{0,movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
			0.75f
		);

		//TODO: Make this a bit smoother

		newStringLabel(skill->getName(), -30 + skillOffset);
		newStringLabel(skill->getDescription(), -10 + skillOffset);
		newStringLabel("Cost: ", skill->getCost(), 10 + skillOffset);
		newStringLabel("Range: ", skill->getRange(), 30 + skillOffset);

		skillOffset += skillIcon->getSize().y;

		skillString.str(std::string());
	}*/

	auto exitButtonSprite = assetManager->getSprite("no_button");
	auto exitButton = addNewChild<Button>(
		exitButtonSprite,
		glm::vec2{getRight() -  exitButtonSprite->getWidth() / 2, getTop() + exitButtonSprite->getHeight() / 2},
		glm::vec2{0,0}
	);
	//exitButton->setOnPress(std::bind(&Game::popState, game));

}

void InfoPanel::newStringLabel(std::string textString, int skillOffset) {
	std::stringstream skillString;
	skillString << textString;
	auto skillLabel = addNewChild<Label>(
		skillString.str().c_str(),
		font,
		glm::vec2{assetManager->getSprite("attack")->getWidth() / 2.0f, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
		glm::vec2{100,20}
	);
}

void InfoPanel::newStringLabel(std::string textString, int value, int skillOffset) {
	std::stringstream skillString;
	skillString << textString << value;
	auto skillLabel = addNewChild<Label>(
		skillString.str().c_str(),
		font,
		glm::vec2{assetManager->getSprite("attack")->getWidth() / 2.0f, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
		glm::vec2{100,20}
	);
}

void InfoPanel::newStringLabel(std::string textString, float value, int skillOffset) {
	std::stringstream skillString;
	skillString << textString << value;
	auto skillLabel = addNewChild<Label>(
		skillString.str().c_str(),
		font,
		glm::vec2{assetManager->getSprite("attack")->getWidth() / 2.0f, movementLabel->getBottom() - movementLabel->getSize().y - skillOffset},
		glm::vec2{100,20}
	);
}
