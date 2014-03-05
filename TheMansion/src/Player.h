/*
 * Player.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Include.h"

class Player: public Character {
public:
	Player(double=WINDOW_SIZE/2, double=WINDOW_SIZE/2, int=PLAYER_WIDTH, int=PLAYER_HEIGHT, string=string("player.bmp"), int=PLAYER_XFRAMES, int=PLAYER_YFRAMES, double=CHARACTER_SPEED);
	virtual ~Player();
};

#endif /* PLAYER_H_ */
