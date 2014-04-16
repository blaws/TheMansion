/*
 * MansionGame.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef MANSIONGAME_H_
#define MANSIONGAME_H_

#include "Include.h"

class MansionGame {
public:
	static MansionGame & getMansionGame();
	virtual ~MansionGame();
	int play(int*, char*[]);

	void initAndOpenWindow(int*, char*[]);
	void display();
	void displayObjects(objectType);
	void addToObjectsToDisplay(Entity * const);
	void respondToKeyDown(unsigned char, int, int);
	void respondToKeyUp(unsigned char, int, int);
	void animate();
	bool envCollision(double, double, int, int);
	void recenterCamera();
	double getProtagonistX();
	double getProtagonistY();
	direction getProtagonistFacingDir();
	void displayProtagonist();

private:
	MansionGame();  // so that only one instance can be created, through getMansionGame()

	Player protagonist;
	Map map;
	vector<Entity *> objectsToDisplay;
};

#endif /* MANSIONGAME_H_ */
