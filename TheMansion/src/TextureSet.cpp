/*
 * TextureSet.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blaws
 */

#include "Include.h"

TextureSet & TextureSet::mainTextureSet(){
	static TextureSet mainSet;
	return mainSet;
}

TextureSet::TextureSet() {  // private; TextureSet should be accessed through mainTextureSet()
}

TextureSet::~TextureSet() {
}

GLuint TextureSet::getTexture(string texture){
	if(texture=="" || texture==" "){
		cout<<"ignoring bad texture request: \""<<texture<<"\""<<endl;
		return 0;
	}

	// make sure that GLUT is initialized to prevent seg fault
	if(!glutInitialized){
		int tempArgc = 1;
		char* tempArgv[1] = {"MansionGame"};
		mg.initAndOpenWindow(&tempArgc, tempArgv);
		glutInitialized = true;
	}

	// check for existing texture matching requested name
	for(int i=0,n=textureNames.size(); i<n; ++i){
		if(textureNames[i] == texture){
			//cout<<"found texture: "<<texture<<endl;
			return textureIDs[i];
		}
	}

	// create new texture from file corresponding to name
	// open file
	ifstream file(string("src/textures/")+texture);
	if(!file.is_open()){
		cout << "File error: " << texture << ":" << strerror(errno) << endl;
		return 0;
	}

	// get size of image from header
	int width,height;
	short bitsperpixel;
	file.ignore(18);  // beginning of .bmp header
	file.read((char*)&width, 4);
	file.read((char*)&height, 4);
	file.ignore(2);
	file.read((char*)&bitsperpixel, 2);
	file.ignore(24);  // rest of .bmp header

	unsigned char* colorArray = new unsigned char[width*abs(height)*4];
	int begin, incr;
	if(height > 0){
		begin = 0;
		incr = 1;
	}
	else{
		begin = height-1;
		incr = -1;
	}

	// read image into array
	for(int i=begin; i>=0 && i<abs(height); i+=incr){
		int j;
		for(j=0; j<width; ++j){
			file.read((char*)&colorArray[(i*width+j)*4], bitsperpixel/8);
			// check if this pixel should be transparent
			if(colorArray[(i*width+j)*4] == (unsigned char)B_TRANSPARENT
					&& colorArray[(i*width+j)*4+1] == (unsigned char)G_TRANSPARENT
					&& colorArray[(i*width+j)*4+2] == (unsigned char)R_TRANSPARENT)
				colorArray[(i*width+j)*4+3] = (unsigned char)0;
			else colorArray[(i*width+j)*4+3] = (unsigned char)255;
		}
		while((j++)%4) file.ignore(1);  // discard padding at end of each line
	}
	file.close();

	// create texture object from array
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	textureIDs.push_back(GLuint(0));
	glGenTextures(1, &textureIDs.back());
	glBindTexture(GL_TEXTURE_2D, textureIDs.back());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, colorArray);

	textureNames.push_back(texture);
	//cout<<"created texture: "<<texture<<endl;
	return textureIDs.back();
}
