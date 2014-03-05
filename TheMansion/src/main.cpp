/*
 * main.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

MansionGame mg = MansionGame::getMansionGame();
bool glutInitialized = false;

int main(int argc, char* argv[]){
	return mg.play(&argc, argv);
}
