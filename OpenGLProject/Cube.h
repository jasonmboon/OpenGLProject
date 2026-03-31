#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	float _rotation;
	static Vertex* indexedVertices;
	static Colour* indexedColours;
	static GLushort* indices;

	static int numVertices, numColours, numIndices;

public:
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube(void);

	void Update();
	void Draw();
	static bool Load(char* path);
};

