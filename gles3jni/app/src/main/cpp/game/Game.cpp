#include "Game.h"
#include "ui/Button.h"

using namespace std;

Game::Game() {

}

Game::~Game() {

}

void Game::initialize() {
	pipeline.initialize();
	assetManager.unloadAll();
	assetManager.loadModule("modules/default");
	map.initialize(160, 160, &assetManager, &pipeline);
	std::shared_ptr<Button> button =
		std::make_shared<Button>(assetManager.getSprite("test_button"), glm::vec2{-650,440}, glm::vec2{200,200});
	button->setOnPress(bind(&GameMap::generate, &map));
	ui.Add(button);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	map.draw();
	ui.draw(&pipeline);
}

void Game::onMove(float dx, float dy) {
	map.getCamera()->moveBy({dx, dy});
}

void Game::onResize(int width, int height) {
	map.getCamera()->setSize({width, height});
}

void Game::onPress(float x, float y) {
	ui.press({x, y});
}
