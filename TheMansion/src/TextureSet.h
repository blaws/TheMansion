/*
 * TextureSet.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#ifndef TEXTURESET_H_
#define TEXTURESET_H_

#include "Include.h"
using namespace std;

class TextureSet {
public:
	static TextureSet & mainTextureSet();
	virtual ~TextureSet();
	GLuint getTexture(string);

private:
	TextureSet();  // so that only one TextureSet can be created, via mainTextureSet
	vector<string> textureNames;
	vector<GLuint> textureIDs;
};

#endif /* TEXTURESET_H_ */
