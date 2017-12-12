#include "InfoPanel.h"

InfoPanel::InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager, Game* game)
	: UISprite(sprite, position) {
	this->font = font;
	this->assetManager = assetManager;
	this->game = game;
}

void InfoPanel::updateInfo(Unit* unit) {
	getChildren().clear();

	auto infoPanelSprite = assetManager->getSprite("ui_info");
	auto unitType = unit->getType();

	auto unitUISprite = unitType->getSprite();
	auto unitIcon = addNewChild<UISprite>(
		unitUISprite,
		Transform2D{
			Translation{0 - infoPanelSprite->getWidth() / 3 + unitUISprite->getSize().x / 3.0f, 0},
			Scale{2.4f, 2.4}
		}
	);

	auto unitName = unitType->getName();
	auto maxHP = unitType->getHP();
	auto currentHP = unit->getHP();
	auto defense = unitType->getDefense();
	auto movement = unitType->getMovement();

	std::stringstream infoString;
	infoString << unitName
		<< "\nHP: " << currentHP << "/" << maxHP
		<< "\nDefense: " << defense
		<< "\nMovement points: " << movement << "\0";

	infoLabel = addNewChild<Label>(
		infoString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f},
		glm::vec2{infoPanelSprite->getWidth() / 2.0f,infoPanelSprite->getHeight() / 5.0f}
	);

	int skillOffset = 0;

	for (auto& skill : unitType->getSkills()){

		auto skillSprite = skill->getSprite();
		auto skillIcon = addNewChild<UISprite>(
			skillSprite,
			Transform2D{
				Translation{0, infoLabel->getBottom() - infoLabel->getSize().y - skillSprite->getSize().y / 3.0f - skillOffset},
				Scale{0.75f, 0.75f}
			}
		);

		std::stringstream skillString;
		skillString << skill->getName() << "\n"
					<< skill->getDescription() << "\n"
					<< "Cost: " << skill->getCost() << "\n"
					<< "Range: " << skill->getRange();

		skillLabel = addNewChild<Label>(
			skillString.str().c_str(),
			font,
			glm::vec2{assetManager->getSprite("attack")->getWidth() / 2.0f, infoLabel->getBottom() - infoLabel->getSize().y - skillOffset},
			glm::vec2{infoPanelSprite->getWidth() / 2.0f,300}
		);

		skillOffset += skillLabel->getSize().y / 2.0f;

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
			Translation{0 - infoPanelSprite->getWidth() / 3 + buildingUISprite->getSize().x / 3.0f, 0},
			Scale{2.4f, 2.4}
		}
	);

	auto buildingName = buildingType->getName();
	auto buildingDescription = buildingType->getDescription();

	std::stringstream infoString;
	infoString << buildingName << "\n"
				<< buildingDescription;

	infoLabel = addNewChild<Label>(
		infoString.str().c_str(),
		font,
		glm::vec2{0,infoPanelSprite->getHeight() / 3.0f},
		glm::vec2{infoPanelSprite->getWidth() / 2.0f,300}
	);

	auto exitButtonSprite = assetManager->getSprite("no_button");
	auto exitButton = addNewChild<Button>(
		exitButtonSprite,
		glm::vec2{getRight() -  exitButtonSprite->getWidth() / 2, getTop() + exitButtonSprite->getHeight() / 2},
		glm::vec2{0,0}
	);
	//exitButton->setOnPress(std::bind(&Game::popState, game));

	recruitmentList.clear();
	recruitmentList.reserve(building->getType()->getRecruitments().size());
	int recruitOffset = 0;
	for (auto& recruit : building->getType()->getRecruitments()) {
		recruitmentList.emplace_back(building, recruit);

		auto recruitSprite = recruit.getUnitType()->getSprite();
		auto recruitButton = addNewChild<Button>(
			recruitSprite, glm::vec2{
				0 + recruitOffset, infoLabel->getBottom()
			}
		);
		recruitButton->setOnPress(std::bind(
			&InfoPanel::recruitButton_onPress, this, std::placeholders::_1)
		);
		recruitButton->setOnPressArgs(&recruitmentList.back());

		recruitOffset += recruitSprite->getWidth();
	}
}

void InfoPanel::recruitButton_onPress(void* recruitArg) {
	auto recruit = static_cast<BuildingRecruitment*>(recruitArg);
	auto scenario = game->getCampaign()->getScenario();
	auto faction = scenario->getActiveFaction();
	auto resourceCosts = recruit->recruitment.getResourceCosts();
	if (!faction->hasResources(resourceCosts)) {
		return;
	}
	for (auto& resourceCost : resourceCosts) {
		faction->subtractResource(resourceCost);
	}
	//faction->modifyResources(resourceCosts);

	scenario->getActiveMap()->createUnit(
		recruit->building->getGridPosition(), recruit->recruitment.getUnitType(), faction
	);
	game->changeToNew<IdleGameState>(game);
}
