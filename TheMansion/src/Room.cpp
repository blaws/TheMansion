/*
 * Room.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

Room::Room(double xi, double yi, int width, int height, string file, int tileXstart, int tileYstart, int tileW, int tileH, int* doorways)
	: Entity(xi, yi, width, height, file, 1, 1){
	// tile main space, carving out entries
	bool walkable;
	for(int i=0; i<height/FLOOR_TILE_SIZE; ++i){
		tiles.push_back(vector<Entity>());
		for(int j=0; j<width/FLOOR_TILE_SIZE; ++j){
			if(doorways &&
			   ((doorways[DIRECTION_UP]>0 && i==height/FLOOR_TILE_SIZE-1 && j!=doorways[DIRECTION_UP]) ||
			    (doorways[DIRECTION_DOWN]>0 && i==0 && j!=doorways[DIRECTION_DOWN]) ||
			    (doorways[DIRECTION_LEFT]>0 && j==0 && i!=doorways[DIRECTION_LEFT]) ||
			    (doorways[DIRECTION_RIGHT]>0 && j==width/FLOOR_TILE_SIZE-1 && i!=doorways[DIRECTION_RIGHT])))
				walkable=false;
			else walkable=true;
			tiles.back().push_back(Entity(x+j*FLOOR_TILE_SIZE, y+i*FLOOR_TILE_SIZE, FLOOR_TILE_SIZE, FLOOR_TILE_SIZE, file, MAX_TILE_X, MAX_TILE_Y, walkable));

			// set semi-random tile texture, or fully transparent texture for non-areas
			tiles.back().back().setFrameX(walkable ? tileXstart+rand()%tileW : MAX_TILE_X-1);
			tiles.back().back().setFrameY(walkable ? tileYstart+rand()%tileH : MAX_TILE_Y-1);
		}
	}
}

Room::~Room() {
}

void Room::display() const{
	//if(!isInRoom(mg.getProtagonistX(), mg.getProtagonistY(), PLAYER_WIDTH, 1)) return;
	for(int i=0,n=tiles.size(); i<n; ++i){
		for(int j=0,m=tiles[i].size(); j<m; ++j){
			tiles[i][j].display();
		}
	}
}

int Room::isInRoom(double xi, double yi, int wi, int hi){  // wi and hi must be >=2
	//cout<<"isInRoom?"<<endl;
	if(wi<=0 || hi<=0) return -1;
	int val=0;  // val=0 means not in room, 0<val<9 means partially in room, val=9 means fully in room
	// check six (or four) points of the given box
	for(double i=xi; i<=xi+wi; i+=wi/2){
		for(double j=yi; j<=yi+hi; j+=hi/2){
			if(i>=x && i<x+w && j>=y && j<y+h && tiles[abs((int)(j-y))/FLOOR_TILE_SIZE][abs((int)(i-x))/FLOOR_TILE_SIZE].isTraversable()){
				++val;
			}
		}
	}
	//cout<<"  "<<val<<endl;
	return val;
}
