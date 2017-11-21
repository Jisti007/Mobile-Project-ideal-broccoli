#include <algorithm>
#include "Scene.h"

bool Scene::animate(float deltaTime) {
	if (animationQueue.empty()) {
		return false;
	}

	auto animation = animationQueue.front().get();
	if (animation->animate(deltaTime)) {
		animationQueue.pop_front();
	}
	return true;
}

void Scene::draw(Pipeline* pipeline, float deltaTime) {
	std::vector<Actor*> visibleActors;
	for (auto& actor : actors) {
		auto position = actor->getPosition();
		auto sprite = actor->getSprite();
		Rectangle spriteBounds(position - sprite->getSize() / 2.0f, sprite->getSize());
		if (pipeline->isVisible(spriteBounds)) {
			visibleActors.push_back(actor.get());
		}
	}

	std::sort(visibleActors.begin(), visibleActors.end(), ActorSorter());
	for (auto& actor : visibleActors) {
		actor->draw(pipeline);
	}
}

void Scene::clear() {
	animationQueue.clear();
	actors.clear();
}

void Scene::addActor(std::unique_ptr<Actor>& actor) {
	actors.push_back(std::move(actor));
}
