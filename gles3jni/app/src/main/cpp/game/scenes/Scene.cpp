#include <algorithm>
#include "Scene.h"

bool Scene::animate(float deltaTime) {
	/*
	if (animationQueue.empty()) {
		return false;
	}
	*/
	auto i = animationQueue.begin();
	while (i != animationQueue.end()) {
		auto animation = i->get();
		if (animation->animate(deltaTime)) {
			animationQueue.erase(i++);
		} else if (animation->isBlocking()) {
			return true;
		} else {
			i++;
		}
	}

	return !animationQueue.empty();
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

void Scene::removeActor(Actor* actor) {
	for (auto i = actors.begin(); i != actors.end(); i++) {
		if ((*i).get() == actor) {
			actors.erase(i);
			break;
		}
	}
}
