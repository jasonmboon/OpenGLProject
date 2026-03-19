#pragma once
#include <Windows.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include "GL/freeglut.h"

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
	Vertex* vertices;
	Colour* colours;
	GLushort* indices;
	int VertexCount, ColourCount, IndexCount;
};