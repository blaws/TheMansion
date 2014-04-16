/*
 * Character.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

Character::Character(double x, double y, int w, int h, int t, string texture, int xframes, int yframes, double s, direction dir)
	: Entity(x, y, w, h, t, texture, xframes, yframes) {
	speed = s;
	movingRight = movingLeft = movingUp = movingDown = false;
	facingDir = dir;
}

Character::~Character() {
}

void Character::startMoveDir(int dir){
	switch(dir){
	case DIRECTION_RIGHT:
		movingRight=true;
		facingDir = DIRECTION_RIGHT;
		break;
	case DIRECTION_LEFT:
		movingLeft=true;
		if(!movingRight) facingDir = DIRECTION_LEFT;
		break;
	case DIRECTION_UP:
		movingUp=true;
		if(!movingRight && !movingLeft) facingDir = DIRECTION_UP;
		break;
	case DIRECTION_DOWN:
		movingDown=true;
		if(!movingRight && !movingLeft && !movingUp) facingDir = DIRECTION_DOWN;
		break;
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
	if(movingRight || movingLeft || movingUp || movingDown){
		nextFrameY();
		glutPostRedisplay();

		//cout << "x = " << x << "; y = " << y << endl;
	}
}

direction Character::getFacingDir() const{
	return facingDir;
}
