#include "UITexture.h"
#include <vector>

UITexture::UITexture(Texture* texture, glm::vec2 position, glm::vec2 size) :
	UIObject(position, size),
	sprite(
		"none", texture, 0, 0,
		static_cast<int>(size.x), static_cast<int>(size.y),
		0, 0, std::vector<glm::vec3>()
	)
{

}

void UITexture::onDraw(Pipeline* pipeline) {
	pipeline->draw(&sprite, getPosition());
}
