#ifndef GLES3JNI_MAINMENUGAMESTATE_H
#define GLES3JNI_MAINMENUGAMESTATE_H

#include "GameState.h"

class MainMenuGameState : public GameState {
public:
	MainMenuGameState(Game* game);

	virtual void recreateUI();

private:
	void createUI();
	void testButton_onPress(void* args);
};

#endif //GLES3JNI_MAINMENUGAMESTATE_H
