/*
 * Character.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

Character::Character(double x, double y, int w, int h, string texture, int xframes, int yframes, double s)
	: Entity(x, y, w, h, texture, xframes, yframes) {
	speed = s;
	movingRight = movingLeft = movingUp = movingDown = false;
}

Character::~Character() {
}

void Character::startMoveDir(int dir){
	switch(dir){
	case DIRECTION_RIGHT: movingRight=true; break;
	case DIRECTION_LEFT: movingLeft=true; break;
	case DIRECTION_UP: movingUp=true; break;
	case DIRECTION_DOWN: movingDown=true; break;
	}
}

void Character::stopMoveDir(int dir){
	switch(dir){
	case DIRECTION_RIGHT: movingRight=false; break;
	case DIRECTION_LEFT: movingLeft=false; break;
	case DIRECTION_UP: movingUp=false; break;
	case DIRECTION_DOWN: movingDown=false; break;
	}
}

void Character::move(){
	if(movingRight){
		x+=speed;
		while(mg.envCollision(x, y, w, 2)) x-=1.0;
	}
	else if(movingLeft){
		x-=speed;
		while(mg.envCollision(x, y, w, 2)) x+=1.0;
	}
	if(movingUp){
		y+=speed;
		while(mg.envCollision(x, y, w, 2)) y-=1.0;
	}
	else if(movingDown){
		y-=speed;
		while(mg.envCollision(x, y, w, 2)) y+=1.0;
	}

	// set frames
	if(movingRight) setFrameX(DIRECTION_RIGHT);
	else if(movingLeft) setFrameX(DIRECTION_LEFT);
	else if(movingUp) setFrameX(DIRECTION_UP);
	else if(movingDown) setFrameX(DIRECTION_DOWN);
	if(movingRight || movingLeft || movingUp || movingDown) nextFrameY();
}
