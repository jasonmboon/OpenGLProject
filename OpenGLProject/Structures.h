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

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, ColourCount, IndexCount, TexCoordCount;
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

struct TexCoord
{
	GLfloat u, v;
};

