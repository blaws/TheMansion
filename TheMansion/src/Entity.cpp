/*
 * Entity.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "include.h"

Entity::Entity(double xi, double yi, int width, int height, string file, int xframes, int yframes, bool trav){
	x = xi;
	y = yi;
	w = width;
	h = height;
	numFramesX = xframes;
	numFramesY = yframes;
	texture = TextureSet::mainTextureSet().getTexture(file);
	traversable = trav;
	frameX = frameY = 0;
}

Entity::~Entity() {
}

void Entity::setFrameX(uint fx){
	frameX = fx % numFramesX;
}

void Entity::setFrameY(uint fy){
	frameY = fy % numFramesY;
}

void Entity::nextFrameY(){
	frameY = (frameY+1) % numFramesY;
}

void Entity::display() const{
	//cout<<x<<","<<y<<" "<<w<<","<<h<<": "<<texture<<endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(frameX/(double)numFramesX, frameY/(double)numFramesY); glVertex2i(x, y);
	glTexCoord2f((frameX+1.0)/numFramesX, frameY/(double)numFramesY); glVertex2i(x+w, y);
	glTexCoord2f((frameX+1.0)/numFramesX, (frameY+1.0)/numFramesY); glVertex2i(x+w, y+h);
	glTexCoord2f(frameX/(double)numFramesX, (frameY+1.0)/numFramesY); glVertex2i(x, y+h);
	glEnd();
}

bool Entity::isTraversable() const{
	return traversable;
}

double Entity::getX() const{
	return x;
}

double Entity::getY() const{
	return y;
}
