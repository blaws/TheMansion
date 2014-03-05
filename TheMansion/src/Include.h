/*
 * include.h
 *
 *  Created on: Feb 13, 2014
 *      Author: blaws
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

#define WINDOW_SIZE 750
#define ANIMATION_PERIOD 50  // milliseconds

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32
#define PLAYER_XFRAMES 4
#define PLAYER_YFRAMES 3
#define CHARACTER_SPEED 5.0

#define DOORWAY_WIDTH 40
#define DOORWAY_HEIGHT 50

#define FLOOR_TILE_SIZE 40
#define MAX_TILE_X 13
#define MAX_TILE_Y 6

#define R_TRANSPARENT 255
#define G_TRANSPARENT 0
#define B_TRANSPARENT 255

enum{
	DIRECTION_RIGHT = 0,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_UP
};

enum{
	OBJ_FOREGROUND,
	OBJ_BACKGROUND
};

typedef struct floortile{
	floortile(int a, int b){ x=a; y=b; }
	unsigned int x;
	unsigned int y;
} floortile;

#include <GLUT/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cmath>

#include "Entity.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Room.h"
#include "Map.h"
#include "TextureSet.h"
#include "MansionGame.h"

extern MansionGame mg;
extern bool glutInitialized;

#endif /* INCLUDE_H_ */
