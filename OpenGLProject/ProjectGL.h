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
	Camera* camera;
	Cube* cube;
	Cube* cube2;
	
public:
	//Constructor and Destructor
	ProjectGL(int argc, char* argv[]);
	~ProjectGL(void);

	void Update();
	void Display();

	void Keyboard(unsigned char key, int x, int y);
	void DrawGrid(float gridSize, int numLines);
	void DrawCube();
	void setLight(lighting* light);
	void setMaterial(material* mat);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
};
