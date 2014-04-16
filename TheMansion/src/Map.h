/*
 * Map.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef MAP_H_
#define MAP_H_

#include "Include.h"

class Map {
public:
	Map();
	virtual ~Map();
	void display();
	int isInMap(double, double, int, int);
	bool thoroughIsInMap(double, double, int, int);
	bool objectCollision(double, double, double, double);
	void interact(Entity &, double, double, double, double);

private:
	std::vector<Room> rooms;

	bool addNextConnectingRoom(bool, queue<int> &, queue<int> &, queue<int> &);
};

#endif /* MAP_H_ */
