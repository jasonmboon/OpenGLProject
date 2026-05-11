#pragma once
#include <Windows.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include "GL/freeglut.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Vertices
struct point3d
{
	float x, y, z;
};

// Colours
struct Colour
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

// Faces
struct polygon3d
{
	int a;
	int b;
	int c;
};

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye;
	Vector3 centre;
	Vector3 up;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
};

struct lighting {
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};

// linked list to store texture ID and path to texture file
struct TextureNode
{
	GLuint textureID;
	char* filePath;
	TextureNode* next;
	TextureNode(GLuint id, char* path) : textureID(id), filePath(path), next(nullptr) {}
};



