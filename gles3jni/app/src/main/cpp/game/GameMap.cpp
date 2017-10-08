#include "GameMap.h"

GameMap::GameMap() {

}

GameMap::GameMap(uint16_t width, uint16_t height, AssetManager& assets) {
	initialize(width, height, assets, nullptr);
}

GameMap::~GameMap() {

}

void GameMap::initialize(uint16_t width, uint16_t height, AssetManager& assets, Pipeline* pipeline) {
	this->width = width;
	this->height = height;
	this->pipeline = pipeline;
	hexes.resize(width * height);

	HexType* testHexType = assets.getHexType("default");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			getHex(x, y)->initialize(x, y, testHexType);
		}
	}
}

void GameMap::draw() {
	glUseProgram(pipeline->getProgram());
	Vertex::enableAttributes();
	auto instancePositionLocation = glGetUniformLocation(pipeline->getProgram(), "instancePosition");
	auto cameraPositionLocation = glGetUniformLocation(pipeline->getProgram(), "cameraPosition");
	auto cameraSizeLocation = glGetUniformLocation(pipeline->getProgram(), "cameraSize");
	glUniform2f(cameraPositionLocation, camera.getX(), camera.getY());
	glUniform2f(cameraSizeLocation, camera.getSize().x, camera.getSize().y);

	for (auto& hex : hexes) {
		auto position = getScreenPosition(hex.getGridX(), hex.getGridY());
		if (
			position.x + camera.getX() < -camera.getSize().x
			|| position.x + camera.getX() > camera.getSize().x
			|| position.y + camera.getY() < -camera.getSize().y
			|| position.y + camera.getY() > camera.getSize().y
			) {
			continue;
		}

		auto sprite = hex.getType()->getSprite();
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getHandle());
		auto mesh = sprite->getMesh();
		glBindVertexArray(mesh->getVertexArray());
		glUniform2f(instancePositionLocation, position.x, position.y);
		glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
	}
}

glm::vec2 GameMap::getScreenPosition(int32_t x, int32_t y) {
	glm::vec2 position = {x, y};

	const float gridSize = 128;

	float xOffset = 0.75;
	float yOffset = 0.50;

	if (x % 2) {
		position = {xOffset * x, y - yOffset};
	} else {
		position = {xOffset * x, y};
	}

	position.x *= gridSize;
	position.y *= gridSize;

	return position;
}
