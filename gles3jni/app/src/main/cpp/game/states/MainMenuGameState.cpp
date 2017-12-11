#include "MainMenuGameState.h"
#include "../ui/UITexture.h"
#include "IdleGameState.h"

MainMenuGameState::MainMenuGameState(Game* game) : GameState(game) {
	createUI();
}

void MainMenuGameState::recreateUI() {
	GameState::recreateUI();
	createUI();
}

void MainMenuGameState::createUI() {
	auto assets = game->getAssets();

	auto fontTexture = assets->getTexture("default_font_texture");
	uiRoot->addNewChild<UITexture>(
		fontTexture,
		glm::vec2{0.0f, 0.0f},
		glm::vec2{fontTexture->getWidth(), fontTexture->getHeight()}
	);

	auto testButton = uiRoot->addNewChild<UITexture>(
		assets->getTexture("pixel"),
		glm::vec2{0.0f, 0.0f},
		glm::vec2{512.0f, 128.0f}
	);
	testButton->setOnPress(std::bind(
		&MainMenuGameState::testButton_onPress, this, std::placeholders::_1
	));
}

void MainMenuGameState::testButton_onPress(void* args) {
	game->changeToNew<IdleGameState>(game);
}
