#ifndef GLES3JNI_GAMESTATE_H
#define GLES3JNI_GAMESTATE_H

class Game;

#include "../ui/UIObject.h"
#include "../Game.h"

class GameState {
public:
	GameState(Game* game);
	virtual ~GameState();

	virtual void update(float deltaTime) = 0;
	virtual void draw(Pipeline* pipeline);
	virtual void move(float dx, float dy) = 0;
	virtual bool press(float x, float y) { return uiRoot->press({x, y}); }

protected:
	Game* game;
	Camera camera;
	std::unique_ptr<UIObject> uiRoot;
};

#endif //GLES3JNI_GAMESTATE_H
