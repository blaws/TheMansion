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

	map.display();
	//map.displayObjects(OBJ_BACKGROUND);
	protagonist.display();
	//map.displayObjects(OBJ_FOREGROUND);

	glutSwapBuffers();
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

bool MansionGame::envCollision(double xi, double yi, int wi, int hi){
	return (map.isInMap(xi, yi, wi, hi) < 4);
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

int MansionGame::getProtagonistFacingDir(){
	return protagonist.getFacingDir();
}
