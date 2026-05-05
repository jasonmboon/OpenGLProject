#pragma once
#include "Structures.h"

class Texture2D
{
private:
	GLuint textureID;
	int width, height;

public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetTextureID() const { return textureID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	//void Bind() const;
};

