/*
 * Map.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef MAP_H_
#define MAP_H_

#include "Include.h"
using namespace std;

class Map {
public:
	Map();
	virtual ~Map();
	void display() const;
	void displayObjects(int) const;
	int isInMap(double, double, int, int);

private:
	vector<Room> rooms;
	vector<Entity> objects;

	bool addNextConnectingRoom(bool, queue<int> &, queue<int> &, queue<int> &);
};

#endif /* MAP_H_ */
