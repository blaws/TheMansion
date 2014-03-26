/*
 * Room.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "Include.h"

class Room: public Entity {
public:
	Room(double=0.0, double=0.0, int=0, int=0, string="floor.bmp", int=0, int=0, int=1, int=1, int[]=NULL);
	virtual ~Room();
	void display() const;
	int isInRoom(double, double, double, double) const;
	bool thoroughIsInRoom(double, double, double, double) const;

private:
	vector<vector<Entity> > tiles;
};

#endif /* ROOM_H_ */
