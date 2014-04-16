/*
 * MansionGame.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

// "trampolines" to convert member functions to GLUT-friendly form
void display_TRAMP(){ mg.display(); }
void respondToKeyDown_TRAMP(unsigned char key, int x, int y){
	mg.respondToKeyDown(key, x, y);
}
void respondToKeyUp_TRAMP(unsigned char key, int x, int y){
	mg.respondToKeyUp(key, x, y);
}
void animate_TRAMP(int t){
	mg.animate();
}

MansionGame & MansionGame::getMansionGame(){
	static MansionGame mainMG;
	return mainMG;
}

MansionGame::MansionGame() {  // private; accessed through getMansionGame()
}

MansionGame::~MansionGame() {
}

int MansionGame::play(int* argc, char* argv[]){
	if(!glutInitialized){
		glutInitialized = true;
		initAndOpenWindow(argc, argv);
	}
	glutMainLoop();
	return 0;
}

void MansionGame::initAndOpenWindow(int* argc, char* argv[]){
	// start GLUT
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutInitWindowPosition(1280-WINDOW_SIZE, 0);
	glutCreateWindow(argv[0]);

	// set camera view
	recenterCamera();

	// set functions
	glutDisplayFunc(display_TRAMP);
	glutKeyboardFunc(respondToKeyDown_TRAMP);
	glutKeyboardUpFunc(respondToKeyUp_TRAMP);
	glutTimerFunc(ANIMATION_PERIOD, animate_TRAMP, 0);
}

void MansionGame::display(){
	glClear(GL_COLOR_BUFFER_BIT);

	objectsToDisplay.clear();
	map.display();
	displayObjects(OBJ_BACKGROUND);
	protagonist.display();
	displayObjects(OBJ_FOREGROUND);

	glutSwapBuffers();
}

void MansionGame::displayObjects(objectType type){
	for(vector<Entity *>::iterator i=objectsToDisplay.begin(); i!=objectsToDisplay.end(); ++i){
		if(type==OBJ_BACKGROUND && ((*i)->getY() >= mg.getProtagonistY()))
			(*i)->display();
		else if(type==OBJ_FOREGROUND && ((*i)->getY() < mg.getProtagonistY()))
			(*i)->display();
	}
}

void MansionGame::addToObjectsToDisplay(Entity * const obj){
	objectsToDisplay.push_back(obj);
}

void MansionGame::displayProtagonist(){
	protagonist.display();
}

void MansionGame::respondToKeyDown(unsigned char key, int x, int y){
	switch(key){
	case 'w':
		protagonist.startMoveDir(DIRECTION_UP);
		break;
	case 's':
		protagonist.startMoveDir(DIRECTION_DOWN);
		break;
	case 'a':
		protagonist.startMoveDir(DIRECTION_LEFT);
		break;
	case 'd':
		protagonist.startMoveDir(DIRECTION_RIGHT);
		break;
	case 'q':
	case 'Q':
	case 27:  // ESC key
		exit(0);
	case ' ':
		map.interact(protagonist, protagonist.getX(), protagonist.getY(), protagonist.getW(), protagonist.getThickness());
	}
}

void MansionGame::respondToKeyUp(unsigned char key, int x, int y){
	switch(key){
	case 'w':
		protagonist.stopMoveDir(DIRECTION_UP);
		break;
	case 's':
		protagonist.stopMoveDir(DIRECTION_DOWN);
		break;
	case 'a':
		protagonist.stopMoveDir(DIRECTION_LEFT);
		break;
	case 'd':
		protagonist.stopMoveDir(DIRECTION_RIGHT);
		break;
	}
}

void MansionGame::animate(){
	protagonist.move();
	recenterCamera();
	//glutPostRedisplay();
	glutTimerFunc(ANIMATION_PERIOD, animate_TRAMP, 0);
}

bool MansionGame::envCollision(double xi, double yi, int wi, int ti){
	return map.isInMap(xi, yi, wi, ti)<4 || map.objectCollision(xi, yi, wi, ti);
}

void MansionGame::recenterCamera(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(protagonist.getX()-WINDOW_SIZE/2, protagonist.getX()+WINDOW_SIZE/2, protagonist.getY()-WINDOW_SIZE/2, protagonist.getY()+WINDOW_SIZE/2);
	glMatrixMode(GL_MODELVIEW);
}

double MansionGame::getProtagonistX(){
	return protagonist.getX();
}

double MansionGame::getProtagonistY(){
	return protagonist.getY();
}

direction MansionGame::getProtagonistFacingDir(){
	return protagonist.getFacingDir();
}
