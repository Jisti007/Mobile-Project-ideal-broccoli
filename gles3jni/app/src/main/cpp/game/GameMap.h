#ifndef GLES3JNI_GAMEMAP_H
#define GLES3JNI_GAMEMAP_H


#include <vector>
#include <string>
#include "MapHex.h"

class GameMap {

public:
    GameMap();

    void createMap();
    void Init();

private:
    std::vector<MapHex> hexes;
};

#endif //GLES3JNI_GAMEMAP_H
