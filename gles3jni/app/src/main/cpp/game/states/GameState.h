#ifndef GLES3JNI_GAMESTATE_H
#define GLES3JNI_GAMESTATE_H

#include "../ui/UIObject.h"

class GameState {
public:
	GameState();
	virtual ~GameState();

	virtual void update() = 0;
	virtual void draw(Pipeline* pipeline);
	virtual void move(float dx, float dy) = 0;
	virtual bool press(float x, float y) { return uiRoot->press({x, y}); }

protected:
	std::unique_ptr<UIObject> uiRoot;
};

#endif //GLES3JNI_GAMESTATE_H
