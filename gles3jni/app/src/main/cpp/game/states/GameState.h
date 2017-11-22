#ifndef GLES3JNI_GAMESTATE_H
#define GLES3JNI_GAMESTATE_H

class Game;

#include "../ui/UIObject.h"
#include "../Game.h"

class GameState {
public:
	GameState(Game* game);
	virtual ~GameState();

	virtual void recreateUI();
	virtual void update(float deltaTime) = 0;
	virtual void draw(Pipeline* pipeline, float deltaTime);
	virtual void move(float dx, float dy) = 0;
	virtual bool press(float x, float y) { return uiRoot->press({x, y}); }
	virtual void zoom(float scaleFactor) = 0;

protected:
	Game* game;
	std::unique_ptr<UIObject> uiRoot;

private:
	void createUI();
};

#endif //GLES3JNI_GAMESTATE_H
