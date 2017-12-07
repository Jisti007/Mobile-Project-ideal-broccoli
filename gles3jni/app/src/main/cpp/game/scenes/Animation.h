#ifndef GLES3JNI_ANIMATION_H
#define GLES3JNI_ANIMATION_H

#include <memory>

class Animation {
public:
	Animation(bool blocking = true);

	template <class T, typename... Args>
	T* chainNew(Args&& ... args);

	/// Returns true if the animation and all chained animations have finished.
	bool animate(float deltaTime);

	inline Animation* getNext() { return next.get(); }
	inline bool isBlocking() { return blocking; }

protected:
	/// Returns true if the animation has finished.
	virtual bool onAnimate(float deltaTime) = 0;

private:
	std::unique_ptr<Animation> next;
	bool blocking;
	bool finished = false;
};

template<class T, typename... Args>
T* Animation::chainNew(Args&& ... args) {
	auto next = new T(std::forward<Args>(args)...);
	std::unique_ptr<Animation> nextPtr(next);
	this->next = std::move(nextPtr);
	return next;
}

#endif //GLES3JNI_ANIMATION_H
