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
	for (auto& actor : actors) {
		actor->draw(pipeline);
	}
}

void Scene::sort() {
	actors.sort(ActorPointerSorter());
}

void Scene::clear() {
	animationQueue.clear();
	actors.clear();
}

void Scene::addActor(std::unique_ptr<Actor>& actor) {
	actors.push_back(std::move(actor));
}
