/*
 * Character.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Include.h"
using namespace std;

class Character: public Entity {
public:
	Character(double=0.0, double=0.0, int=0, int=0, int=0, string="", int=1, int=1, double=1.0, direction=DIRECTION_RIGHT);
	virtual ~Character();
	void startMoveDir(int);
	void stopMoveDir(int);
	void move();
	direction getFacingDir() const;

private:
	double speed;
	bool movingUp, movingDown, movingLeft, movingRight;
	direction facingDir;
};

#endif /* CHARACTER_H_ */
