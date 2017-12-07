#ifndef GLES3JNI_UIOBJECT_H
#define GLES3JNI_UIOBJECT_H

#include "../Sprite.h"
#include "../Rectangle.h"
#include "../Pipeline.h"



class UIObject {
	//typedef std::unique_ptr<UIObject> ChildPtr;

public:
	UIObject(glm::vec2 position = {0,0}, glm::vec2 size = {0,0});

	virtual void onDraw(Pipeline* pipeline) {}

	void draw(Pipeline* pipeline);
	void setOnPress(std::function<void(void*)> onPress);
	bool press(glm::vec2 position);
	/// Convenience method for moving unique pointer to the UI object's children.
	void addChild(std::unique_ptr<UIObject>& newChild);
	/// Convenience method for constructing and adding a new child for the UI object.
	template <class T, typename... Args>
	T* addNewChild(Args&& ... args);

	inline std::vector<std::unique_ptr<UIObject>>& getChildren() { return children; }
	inline glm::vec2 getPosition() { return position; }
	inline glm::vec2 getSize() { return size; }
	inline Rectangle getRectangle() {
		return Rectangle(glm::vec2(getLeft(), getBottom()), size);
	}
	inline float getLeft() { return position.x - size.x / 2.0f; }
	inline float getRight() { return position.x + size.x / 2.0f; }
	inline float getTop() { return position.y + size.y / 2.0f; }
	inline float getBottom() { return position.y - size.y / 2.0f; }
	inline void setOnPressArgs(void* args) { this->onPressArgs = args; }

private:
	std::vector<std::unique_ptr<UIObject>> children;
	glm::vec2 position;
	glm::vec2 size;
	std::function<void(void*)> onPress;
	void* onPressArgs;
};

template<class T, typename... Args>
T* UIObject::addNewChild(Args&& ... args) {
	auto child = new T(std::forward<Args>(args)...);
	std::unique_ptr<UIObject> childPtr(child);
	addChild(childPtr);
	return child;
}

#endif //GLES3JNI_UIOBJECT_H
