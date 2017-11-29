//
// Created by K1697 on 29.11.2017.
//

#ifndef GLES3JNI_RECOLOREDUISPRITE_H
#define GLES3JNI_RECOLOREDUISPRITE_H
#include "UISprite.h"

class RecoloredUISprite : public UISprite {
public:
	RecoloredUISprite(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors);
	RecoloredUISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size, std::vector<glm::vec3> destinationColors);
	RecoloredUISprite(Sprite* sprite, glm::vec2 position, float scale,  std::vector<glm::vec3> destinationColors);
	RecoloredUISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size, float scale,  std::vector<glm::vec3> destinationColors);
	virtual ~RecoloredUISprite();

	virtual void onDraw(Pipeline* pipeline);

private:
	std::vector<glm::vec3> destinationColors;
};


#endif //GLES3JNI_RECOLOREDUISPRITE_H
