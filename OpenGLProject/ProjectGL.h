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

	//Vertex* Cube::indexedVertices;
	//Colour* Cube::indexedColours;
	//GLushort* Cube::indices;
	char* filePath;
	bool isObjectFile = false;
	int polygonCount;	

	Cube* cube;
	
public:
	//Constructor and Destructor
	ProjectGL(int argc, char* argv[]);
	~ProjectGL(void);

	void SetFilePath(char* _filePath) {
		filePath = _filePath;
	}

	/// <summary>
	/// Getters and settings for file path, isObjectFile and polygon count
	/// </summary>
	/// <returns></returns>
	char* GetFilePath(){
		return filePath;
	}

	void SetIsObjectFile(bool _isObjectFile) {
		isObjectFile = _isObjectFile;
	}

	bool GetIsObjectFile() {
		return isObjectFile;
	}

	void setPolygonCount(int _polygonCount) {
		polygonCount = _polygonCount;
	}

	int GetPolygonCount() {
		return polygonCount;
	}

	void Update();
	void Display();

	void Keyboard(unsigned char key, int x, int y);
	void DrawGrid(float gridSize, int numLines);
	void DrawCube();
	//void DrawCubeArray();
	void DrawIndexedCube();
	void DrawIndexedCubeAlt();
	void DrawIndexedCubeFile();
	void DrawObjFile();
};
