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

// Sweeping Triangles - perspective display
void Map::display(){
	int drawcount = 0;
	// set up
	double formerPlane[4] = {0.0}, latterPlane[4] = {0.0}, capPlane[4] = {0.0};
	int startX=mg.getProtagonistX()+PLAYER_WIDTH/2, startY=mg.getProtagonistY();
	double endX[2], endY[2], capTheta, dYdX, interc, prevEndX, prevEndY;
	double lower[2], upper[2];
	bool streakVert=false, streakHor=false;

	for(int i=0; i<3; ++i) glEnable(GL_CLIP_PLANE0+i);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(startX, startY, 0.0);
	mg.recenterCamera();

//	double boxLower[2], boxUpper[2];
	queue<double> qX, qY;  // debug visualization

	double startTheta = 0.0;//M_PI+DISPLAY_SWEEP_DELTA;
	double endTheta = startTheta+2*M_PI;

	for(double theta=startTheta; theta<=endTheta+DISPLAY_SWEEP_DELTA/2; theta+=DISPLAY_SWEEP_DELTA){
		// set latter arc plane
		latterPlane[0] = sin(theta);
		latterPlane[1] = -cos(theta);
		latterPlane[3] = 0.0;

		// set cap plane
		glClipPlane(GL_CLIP_PLANE2, capPlane);

		// calculate next cap plane
		for(int i=0; i<2; ++i){
			endX[i] = startX;
			endY[i] = startY;
			while(!mg.envCollision(endX[i], endY[i], 2, 2) && fabs(endX[i]-startX)<WINDOW_SIZE/2 && fabs(endY[i]-startY)<WINDOW_SIZE/2){
				endX[i] += cos(theta+i*DISPLAY_SWEEP_DELTA);
				endY[i] += sin(theta+i*DISPLAY_SWEEP_DELTA);
			}
/*			endX[i] -= cos(theta+i*DISPLAY_SWEEP_DELTA);
			endY[i] -= sin(theta+i*DISPLAY_SWEEP_DELTA);*/
		}
		if(fabs(endX[0]-endX[1]) >= 1.0){
			dYdX = (endY[1]-endY[0]) / (endX[1]-endX[0]);
			capTheta = atan(dYdX);
			interc = (endY[0]-startY) - (endX[0]-startX)*dYdX;
			capPlane[0] = sin(capTheta);
			capPlane[1] = -cos(capTheta);
			capPlane[3] = -interc * capPlane[1];
			if(interc < 0){
				capPlane[0] *= -1;
				capPlane[1] *= -1;
				capPlane[3] *= -1;
			}
		}
		else{
			capPlane[0] = (theta<M_PI/2 || theta>3*M_PI/2) ? -1.0 : 1.0;
			capPlane[1] = 0.0;
			capPlane[3] = (theta<M_PI/2 || theta>3*M_PI/2) ? endX[0]-startX : startX-endX[0];
		}
		if(fabs(endX[0]-prevEndX) <= 1.0) streakVert=true;
		if(fabs(endY[0]-prevEndY) <= 1.0) streakHor=true;
		if(theta==startTheta){
			prevEndX = endX[0];
			prevEndY = endY[0];
			for(int i=0; i<4; ++i) formerPlane[i] = i<2 ? -latterPlane[i] : latterPlane[i];
		}

		// decide whether to draw yet
		if(theta!=startTheta && ((streakVert && fabs(endX[1]-prevEndX)>1.0) || (streakHor && fabs(endY[1]-prevEndY)>1.0) || (!streakVert && !streakHor) || theta>=2*M_PI)){
			// record corners for debug display
			qX.push(prevEndX);
			qY.push(prevEndY);
			qX.push(endX[0]);
			qY.push(endY[0]);

			// set new starting point
			prevEndX = endX[0];
			prevEndY = endY[0];
			streakHor = false;
			streakVert = false;

			// update room drawing box
			if(startX < lower[0]) lower[0] = startX;
			if(endX[0] < lower[0]) lower[0] = endX[0];
			if(startX > upper[0]) upper[0] = startX;
			if(endX[0] > upper[0]) upper[0] = endX[0];
			if(startY < lower[1]) lower[1] = endY[1];
			if(endY[0] < lower[1]) lower[1] = endY[1];
			if(startY > upper[1]) upper[1] = startY;
			if(endY[0] > upper[1]) upper[1] = endY[0];

/*			for(int i=0; i<2; ++i){
				boxLower[i] = lower[i];
				boxUpper[i] = upper[i];
			}*/

			// draw
			//cout << "draw #" << ++drawcount << endl;
			int numroomsdrawn = 0;
			glClipPlane(GL_CLIP_PLANE0, formerPlane);
			glClipPlane(GL_CLIP_PLANE1, latterPlane);
			glPushMatrix();
			glLoadIdentity();

			// only draw visible rooms
			int total=0, current;
			for(int i=0,n=rooms.size(); i<n /*&& total<9*/; ++i){
				current = rooms[i].mediumIsInRoom(lower[0], lower[1], fabs(upper[0]-lower[0]), fabs(upper[1]-lower[1]));
				if(current > 0){
					rooms[i].display();
					rooms[i].addObjectsToDisplay();
					++numroomsdrawn;
					total += current;
				}
			}
			//cout << "  " << numroomsdrawn << " rooms drawn" << endl;
			glPopMatrix();

			// reset room drawing box
			lower[0] = upper[0] = startX;
			lower[1] = upper[1] = startY;
			if(prevEndX < lower[0]) lower[0] = prevEndX;
			if(endX[0] < lower[0]) lower[0] = endX[0];
			if(prevEndX > upper[0]) upper[0] = prevEndX;
			if(endX[0] > upper[0]) upper[0] = endX[0];
			if(prevEndY < lower[1]) lower[1] = prevEndY;
			if(endY[0] < lower[1]) lower[1] = endY[0];
			if(prevEndY > upper[1]) upper[1] = prevEndY;
			if(endY[0] > upper[1]) upper[1] = endY[0];

			// change former arc plane
			for(int i=0; i<4; ++i) formerPlane[i] = i<2 ? -latterPlane[i] : latterPlane[i];
		}
	}

	for(int i=0; i<3; ++i) glDisable(GL_CLIP_PLANE0+i);

	glLoadIdentity();

	// debug: draw display triangles
/*	glDisable(GL_TEXTURE_2D);
	glColor3f(R_TRANSPARENT/255.0, G_TRANSPARENT/255.0, B_TRANSPARENT/255.0);
	while(!qX.empty()){
		glBegin(GL_LINE_STRIP);
		glVertex2i(startX, startY);
		glVertex2f(qX.front(), qY.front());
		qX.pop(); qY.pop();
		glVertex2f(qX.front(), qY.front());
		glVertex2i(startX, startY);
		qX.pop(); qY.pop();
		glEnd();
	}*/
/*	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP); glVertex2f(boxLower[0], boxLower[1]); glVertex2f(boxLower[0], boxUpper[1]); glVertex2f(boxUpper[0], boxUpper[1]); glVertex2f(boxUpper[0], boxLower[1]); glVertex2f(boxLower[0], boxLower[1]); glEnd();
	glEnable(GL_TEXTURE_2D);*/
}

int Map::isInMap(double xi, double yi, int wi, int hi){
	int val=0;  // once val reaches 4, the box is fully in one or more rooms
	for(int i=0,n=rooms.size(); i<n; ++i){
		val += rooms[i].isInRoom(xi, yi, wi, hi);
		if(val >= 4) return 4;
	}
	return val;
}

bool Map::thoroughIsInMap(double xi, double yi, int wi, int hi){
	for(int i=0,n=rooms.size(); i<n; ++i){
		if(rooms[i].thoroughIsInRoom(xi, yi, wi, hi)) return true;
	}
	return false;
}

bool Map::addNextConnectingRoom(bool first, queue<int> & connectionsX, queue<int> & connectionsY, queue<int> & connectionsDir){
	if(!first && connectionsX.empty()) return false;

	// make initial estimates of size and position
	int roomW = FLOOR_TILE_SIZE*(3+rand()%15);
	int roomH = FLOOR_TILE_SIZE*(3+rand()%15);
	int roomX = first ? -roomW/2 : connectionsX.front();
	int roomY = first ? -roomH/2 : connectionsY.front();

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
	if(!thoroughIsInMap(roomX, roomY, roomW, roomH)){
		rooms.push_back(Room(roomX, roomY, roomW, roomH, "floor.bmp", tileX, 0, 1, tileH, doorways));
		++numRooms;

		// add some actual doorways
		if(doorways[DIRECTION_UP]>0 && rand()%2==0){
			Entity tmp(roomX+doorways[DIRECTION_UP]*FLOOR_TILE_SIZE, roomY+roomH-FLOOR_TILE_SIZE, DOORWAY_WIDTH, DOORWAY_HEIGHT, 5, string("door.bmp"), 1, 2, false);
			rooms.back().addObject(tmp);
		}
		if(doorways[DIRECTION_DOWN]>0 && rand()%2==0){
			Entity tmp(roomX+doorways[DIRECTION_DOWN]*FLOOR_TILE_SIZE, roomY, DOORWAY_WIDTH, DOORWAY_HEIGHT, 5, string("door.bmp"), 1, 2, false);
			rooms.back().addObject(tmp);
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
		//cout<<numRooms<<endl;
		return false;
	}
	else return true;
}

bool Map::objectCollision(double x, double y, double w, double h){
	for(int i=0,n=rooms.size(); i<n; ++i){
		if(rooms[i].isInRoom(x, y, w, h)){
			for(int j=0,m=rooms[i].getNumObjects(); j<m; ++j){
				Entity obj = rooms[i].getObject(j);
				if(overlap(x, y, w, h, obj.getX(), obj.getY(), obj.getW(), obj.getThickness()) && !obj.isTraversable()){
					return true;
				}
			}
		}
	}
	return false;
}

void Map::interact(Entity & sender, double x, double y, double w, double t){
	for(int i=0,n=rooms.size(); i<n; ++i){
		if(rooms[i].isInRoom(x, y, w, t)) rooms[i].interact(sender, x, y, w, t);
	}
}
