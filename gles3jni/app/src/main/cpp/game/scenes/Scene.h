#ifndef GLES3JNI_SCENE_H
#define GLES3JNI_SCENE_H

#include <list>
#include "Actor.h"
#include "../Pipeline.h"
#include "Animation.h"

class Scene {
public:
	template <class T, typename... Args>
	T* addNew(Args&& ... args);
	template <class T, typename... Args>
	T* queueNew(Args&& ... args);

	/// Runs the animation(s) at the front of the queue.
	/// Returns false if the animation queue is empty.
	bool animate(float deltaTime);
	void draw(Pipeline* pipeline, float deltaTime);
	void clear();
	void addActor(std::unique_ptr<Actor>& actor);
	void removeActor(Actor* actor);

	inline void queueAnimation(std::unique_ptr<Animation>& animation) {
		animationQueue.push_back(std::move(animation));
	}

private:
	std::list<std::unique_ptr<Actor>> actors;
	std::list<std::unique_ptr<Animation>> animationQueue;
};

template<class T, typename... Args>
T* Scene::addNew(Args&& ... args) {
	auto actor = new T(std::forward<Args>(args)...);
	std::unique_ptr<Actor> actorPtr(actor);
	addActor(actorPtr);
	return actor;
}

template<class T, typename... Args>
T* Scene::queueNew(Args&& ... args) {
	auto animation = new T(std::forward<Args>(args)...);
	std::unique_ptr<Animation> animationPtr(animation);
	queueAnimation(animationPtr);
	return animation;
}

#endif //GLES3JNI_SCENE_H
