#ifndef GLES3JNI_ACTOR_H
#define GLES3JNI_ACTOR_H

#include "Mesh.h"
#include "Texture.h"
#include "Scene.h"

class Scene;

class Actor {
public:
	Actor(Scene* scene, Texture* texture, Mesh* mesh, glm::vec2 position);
	~Actor();

	void remove();
	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() const { return mesh; }
	inline glm::vec2 getPosition() const { return position; }
	inline float getX() const { return position.x; }
	inline float getY() const { return position.y; }
	inline void setPosition(glm::vec2 position) { this->position = position; }

private:
	Scene* scene;
	Texture* texture;
	Mesh* mesh;
	glm::vec2 position;
};

#endif //GLES3JNI_ACTOR_H
