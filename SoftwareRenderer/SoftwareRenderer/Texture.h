#pragma once

#ifndef TEXTURE
#define TEXTURE



class Texture {
public:
	unsigned int id;
	string type;
	string path;

	Texture();
	Texture(string path,string type) {

	}

};


#endif
