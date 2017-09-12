#include "Game.h"

Game::Game() {
    map = new GameMap();
}

Game::~Game() {
    delete map;
}
