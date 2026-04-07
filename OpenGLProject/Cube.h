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

	// Getters for static members
	Vertex* GetVertices() { return indexedVertices; }
	Colour* GetColours() { return indexedColours; }
	GLushort* GetIndices() { return indices; }
	int GetPolyCount() { return numIndices; }
	int GetVertexCount() { return numVertices; }

	void Update();
	void Draw();
	static bool Load(char* path);
	static bool LoadObjectFile(char* path);
};

