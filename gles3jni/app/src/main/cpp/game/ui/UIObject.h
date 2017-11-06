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
	void setOnPress(std::function<void()> onPress);
	bool press(glm::vec2 position);
	/// Convenience method for moving unique pointer to the ui object's children.
	void addChild(std::unique_ptr<UIObject>& newChild);

	inline std::vector<std::unique_ptr<UIObject>>& getChildren() { return children; }
	inline glm::vec2 getPosition() { return position; }
	inline glm::vec2 getSize() { return size; }
	inline Rectangle getRectangle() {
		return Rectangle(glm::vec2(position.x - size.x / 2, position.y - size.y /2), size);
	}

private:
	std::vector<std::unique_ptr<UIObject>> children;
	glm::vec2 position;
	glm::vec2 size;
	std::function<void()> onPress;
};

#endif //GLES3JNI_UIOBJECT_H
