#pragma once
#include "GLUTCallbacks.h"
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Structures.h"
#include "SceneObject.h"
#include "Cube.h"

#define REFRESHRATE 16

class ProjectGL
{
private:
	//Private member variables and functions
	float rotation;

	Camera* camera;

	static Vertex indexedVertices[];
	static Colour indexedColours[];
	static GLushort indices[];

	Cube* cube;

public:
	//Constructor and Destructor
	ProjectGL(int argc, char* argv[]);
	~ProjectGL(void);

	void Update();
	void Display();

	void Keyboard(unsigned char key, int x, int y);
	void DrawGrid(float gridSize, int numLines);
	void DrawCube();
	//void DrawCubeArray();
	void DrawIndexedCube();
	void DrawIndexedCubeAlt();
};
