#ifndef GLES3JNI_SCENE_H
#define GLES3JNI_SCENE_H

#include <unordered_map>
#include <memory>
#include "Sprite.h"
#include "Actor.h"

class Actor;

class Scene {
public:
	Scene();
	~Scene();

	static void initializePipeline();
	Actor* addActor(Sprite* sprite, glm::vec2 position);
	Actor* addActor(Texture* texture, Mesh* mesh, glm::vec2 position);
	void removeActor(Actor* actor);

	void draw();

private:
	std::unordered_map<
		Texture*, std::unordered_map<
			Mesh*, std::vector<
				Actor*
			>
		>
	> actors;
	std::vector<Actor*> removedActors;

	void destroyActors();
};

#endif //GLES3JNI_SCENE_H
