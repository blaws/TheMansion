/*
 * Entity.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Include.h"
using namespace std;

class Entity {
	//friend class MansionGame;
public:
	Entity(double=0.0, double=0.0, int=0, int=0, int=0, string="", int=1, int=1, bool=true);
	virtual ~Entity();
	void setFrameX(uint);
	void setFrameY(uint);
	void nextFrameY();
	virtual void display() const;
	bool isTraversable() const;
	double getX() const;
	double getY() const;
	double getW() const;
	double getH() const;
	double getThickness() const;
	virtual void interact(Entity &);

protected:
	double x,y;  // of type double for smoother animation
	int w,h,thickness;

private:
	GLuint texture;
	uint numFramesX, numFramesY;
	uint frameX, frameY;
	bool traversable;
};

#endif /* ENTITY_H_ */
