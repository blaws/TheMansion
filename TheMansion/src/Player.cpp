/*
 * Player.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

Player::Player(double x, double y, int w, int h, string texture, int xframes, int yframes, double s)
	: Character(x, y, w, h, texture, xframes, yframes, s){
}

Player::~Player() {
}

