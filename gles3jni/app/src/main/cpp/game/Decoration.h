//
// Created by K1697 on 23.10.2017.
//

#ifndef GLES3JNI_DECORATION_H
#define GLES3JNI_DECORATION_H


#include "Sprite.h"
#include "DecorationType.h"

class Decoration {

public:
	Decoration(DecorationType *type);

	inline const DecorationType* getType() const { return type; }
	Sprite* getSprite() { return sprite; }

private:
	Sprite* sprite;
	DecorationType* type;
};


#endif //GLES3JNI_DECORATION_H
