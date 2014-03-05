/*
 * Map.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

Map::Map() {
	srand(time(NULL));
	queue<int> connectionsX;
	queue<int> connectionsY;
	queue<int> connectionsDir;
	//cout<<"starting map build..."<<endl;
	addNextConnectingRoom(true, connectionsX, connectionsY, connectionsDir);
	while(addNextConnectingRoom(false, connectionsX, connectionsY, connectionsDir));
	//cout<<"finished map build"<<endl;
}

Map::~Map() {
}

void Map::display() const{
	for(int i=0,n=rooms.size(); i<n; ++i){
		rooms[i].display();
	}
}

void Map::displayObjects(int type) const{  // type = OBJ_BACKGROUND or OBJ_FOREGROUND
	for(vector<Entity>::const_iterator i=objects.begin(); i!=objects.end(); ++i){
		if(type==OBJ_BACKGROUND && (i->getY() >= mg.getProtagonistY()))
			i->display();
		else if(type==OBJ_FOREGROUND && (i->getY() < mg.getProtagonistY()))
			i->display();
	}
}

int Map::isInMap(double xi, double yi, int wi, int hi){
	int val=0;  // once val reaches 9, the box is fully in one or more rooms
	for(int i=0,n=rooms.size(); i<n; ++i){
		val += rooms[i].isInRoom(xi, yi, wi, hi);
	}
	return val;
}

bool Map::addNextConnectingRoom(bool first, queue<int> & connectionsX, queue<int> & connectionsY, queue<int> & connectionsDir){
	if(!first && connectionsX.empty()) return false;

	// make initial estimates of size and position
	int roomW = FLOOR_TILE_SIZE*(3+rand()%15);
	int roomH = FLOOR_TILE_SIZE*(3+rand()%15);
	int roomX = first ? WINDOW_SIZE/2-roomW/2 : connectionsX.front();
	int roomY = first ? WINDOW_SIZE/2-roomH/2 : connectionsY.front();

	// pick type of room and doorway locations
	int tileX = rand()%2;
	int tileH = (tileX) ? 4 : 6;
	int doorways[4];
	for(int i=0; i<4; ++i) doorways[i] = (i==DIRECTION_UP || i==DIRECTION_DOWN) ? rand()%(roomW/FLOOR_TILE_SIZE-2)+1 : rand()%(roomH/FLOOR_TILE_SIZE-2)+1;

	// adjust position based on where connection with previous room is
	int dir = -1;
	if(!first){
		int offset;
		switch(dir = connectionsDir.front()){
		case DIRECTION_RIGHT:
			offset = rand()%(roomH/FLOOR_TILE_SIZE-2) + 1;
			roomY -= offset*FLOOR_TILE_SIZE;
			doorways[DIRECTION_LEFT] = -1;//offset;
			break;
		case DIRECTION_LEFT:
			roomX -= roomW;
			offset = rand()%(roomH/FLOOR_TILE_SIZE-2) + 1;
			roomY -= offset*FLOOR_TILE_SIZE;
			doorways[DIRECTION_RIGHT] = -1;//offset;
			break;
		case DIRECTION_DOWN:
			roomY -= roomH;
			offset = rand()%(roomW/FLOOR_TILE_SIZE-2) + 1;
			roomX -= offset*FLOOR_TILE_SIZE;
			doorways[DIRECTION_UP] = -1;//offset;
			break;
		case DIRECTION_UP:
			offset = rand()%(roomW/FLOOR_TILE_SIZE-2) + 1;
			roomX -= offset*FLOOR_TILE_SIZE;
			doorways[DIRECTION_DOWN] = -1;//offset;
			break;
		}

		connectionsX.pop();
		connectionsY.pop();
		connectionsDir.pop();
	}

	static int numRooms=0;
	// make room unless it overlaps a prior room
	if(!isInMap(roomX, roomY, roomW, roomH)){
		rooms.push_back(Room(roomX, roomY, roomW, roomH, "floor.bmp", tileX, 0, 1, tileH, doorways));
		++numRooms;

		// add some actual doorways
		if(doorways[DIRECTION_UP]>0 && rand()%2==0){
			Entity tmp(roomX+doorways[DIRECTION_UP]*FLOOR_TILE_SIZE, roomY+roomH-FLOOR_TILE_SIZE, DOORWAY_WIDTH, DOORWAY_HEIGHT, string("door.bmp"), 1, 2, false);
			objects.push_back(tmp);
		}
		if(doorways[DIRECTION_DOWN]>0 && rand()%2==0){
			Entity tmp(roomX+doorways[DIRECTION_DOWN]*FLOOR_TILE_SIZE, roomY, DOORWAY_WIDTH, DOORWAY_HEIGHT, string("door.bmp"), 1, 2, false);
			objects.push_back(tmp);
		}

		// prepare for next rooms (save location of doorways)
		for(int i=0; i<4; ++i){
			if(doorways[i] >= 0 && (((i==DIRECTION_RIGHT || i==DIRECTION_LEFT) && doorways[i]<roomH/FLOOR_TILE_SIZE) || ((i==DIRECTION_UP || i==DIRECTION_DOWN) && doorways[i]<roomW/FLOOR_TILE_SIZE))){
				connectionsX.push(i==DIRECTION_RIGHT ? roomX+roomW : (i==DIRECTION_LEFT ? roomX : roomX+FLOOR_TILE_SIZE*doorways[i]));
				connectionsY.push(i==DIRECTION_UP ? roomY+roomH : (i==DIRECTION_DOWN ? roomY : roomY+FLOOR_TILE_SIZE*doorways[i]));
				connectionsDir.push(i);
			}
		}
	}

	if(numRooms>20 || connectionsX.empty()){
		cout<<numRooms<<endl;
		return false;
	}
	else return true;
}
