#ifndef GLES3JNI_SCENE_H
#define GLES3JNI_SCENE_H

#include <list>
#include "Actor.h"
#include "../Pipeline.h"
#include "Animation.h"

class Scene {
public:
	/// Runs the animation(s) at the front of the queue.
	/// Returns false if the animation queue is empty.
	bool animate(float deltaTime);
	void draw(Pipeline* pipeline, float deltaTime);
	void sort();
	void clear();
	void addActor(std::unique_ptr<Actor>& actor);

	inline void queueAnimation(std::unique_ptr<Animation>& animation) {
		animationQueue.push_back(std::move(animation));
	}

private:
	std::list<std::unique_ptr<Actor>> actors;
	std::list<std::unique_ptr<Animation>> animationQueue;
};

#endif //GLES3JNI_SCENE_H
