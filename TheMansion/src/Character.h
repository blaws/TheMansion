/*
 * Character.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "include.h"
using namespace std;

class Character: public Entity {
public:
	Character(double=0.0, double=0.0, int=0, int=0, string="", int=1, int=1, double=1.0);
	virtual ~Character();
	void startMoveDir(int);
	void stopMoveDir(int);
	void move();

private:
	double speed;
	bool movingUp, movingDown, movingLeft, movingRight;
};

#endif /* CHARACTER_H_ */
