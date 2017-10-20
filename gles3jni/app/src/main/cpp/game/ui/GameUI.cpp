//
// Created by K1697 on 20.10.2017.
//

#include "GameUI.h"

void GameUI::Add(std::shared_ptr<UIObject> object) {
	uiObjects.push_back(object);
}

void GameUI::draw(Pipeline *pipeline) {
	glUseProgram(pipeline->getProgram());
	Vertex::enableAttributes();
	auto instancePositionLocation = glGetUniformLocation(pipeline->getProgram(), "instancePosition");
	auto cameraPositionLocation = glGetUniformLocation(pipeline->getProgram(), "cameraPosition");
	auto cameraSizeLocation = glGetUniformLocation(pipeline->getProgram(), "cameraSize");
	glUniform2f(cameraPositionLocation, 0, 0);
	glUniform2f(cameraSizeLocation, 960, 540);

	for (auto& uiObject : uiObjects) {
		glUniform2f(instancePositionLocation, uiObject->getPosition().x, uiObject->getPosition().y);
		auto sprite = uiObject->getSprite();
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



