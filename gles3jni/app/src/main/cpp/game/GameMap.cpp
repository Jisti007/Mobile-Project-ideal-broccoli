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

	HexType* grass = assets.getHexType("grass");
	HexType* sand = assets.getHexType("sand");
	HexType* water = assets.getHexType("water");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 70) {
				getHex(x, y)->initialize(x, y, grass);
			}
			else if (rn > 50) {
				getHex(x, y)->initialize(x, y, sand);
			}
			else {
				getHex(x, y)->initialize(x, y, water);
			}
		}
	}

    UnitType* test_unit = assets.getUnitType("test");

	units.emplace_back(0, 0, test_unit);
	for (uint16_t y = 0; y < width; y++) {
        for (uint16_t x = 0; x < height; x++) {
            auto rn = rand() % 100;
            if (rn > 95) {
	            units.emplace_back(x, y, test_unit);
            //    getUnit(x, y)->initialize(x, y, test);
            }
        }
    }

	BuildingType* test_building = assets.getBuildingType("test");

	buildings.emplace_back(0, 0, test_building);
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				buildings.emplace_back(x, y, test_building);
				//    getUnit(x, y)->initialize(x, y, test);
			}
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

		glUniform2f(instancePositionLocation, position.x, position.y);
		auto sprite = hex.getType()->getSprite();
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getHandle());
		auto mesh = sprite->getMesh();
		glBindVertexArray(mesh->getVertexArray());
		glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
	}


	for (auto& building : buildings) {
		auto position = getScreenPosition(building.getX(), building.getY());
		if (
				position.x + camera.getX() < -camera.getSize().x
				|| position.x + camera.getX() > camera.getSize().x
				|| position.y + camera.getY() < -camera.getSize().y
				|| position.y + camera.getY() > camera.getSize().y
				) {
			continue;
		}

		glUniform2f(instancePositionLocation, position.x, position.y);
		auto sprite = building.getType()->getSprite();
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getHandle());
		auto mesh = sprite->getMesh();
		glBindVertexArray(mesh->getVertexArray());
		glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
	}

    for (auto& unit : units) {
        auto position = getScreenPosition(unit.getX(), unit.getY());
        if (
                position.x + camera.getX() < -camera.getSize().x
                || position.x + camera.getX() > camera.getSize().x
                || position.y + camera.getY() < -camera.getSize().y
                || position.y + camera.getY() > camera.getSize().y
                ) {
            continue;
        }

        glUniform2f(instancePositionLocation, position.x, position.y);
        auto sprite = unit.getType()->getSprite();
        glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getHandle());
        auto mesh = sprite->getMesh();
        glBindVertexArray(mesh->getVertexArray());
        glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
    }


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
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
