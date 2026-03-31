#pragma once
#include "Cube.h"

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
GLushort* Cube::indices = nullptr;

Cube::Cube(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{

}

Cube::~Cube(void)
{
}

void Cube::Draw()
{

}

void Cube::Update()
{
	_rotation += 0.1f;
}

bool Cube::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Error opening file: " << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		inFile >> indexedVertices[i].x >> indexedVertices[i].y >> indexedVertices[i].z;
	}

	inFile >> numColours;
	indexedColours = new Colour[numColours];
	for (int i = 0; i < numColours; i++)
	{
		inFile >> indexedColours[i].r >> indexedColours[i].g >> indexedColours[i].b;
	}

	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i];
	}

	// print out the loaded data for verification
	//std::cout << "Loaded " << numVertices << " vertices:" << std::endl;
	//for (int i = 0; i < numVertices; i++)
	//{
	//	std::cout << "Vertex " << i << ": (" << indexedVertices[i].x << ", " << indexedVertices[i].y << ", " << indexedVertices[i].z << ")" << std::endl;
	//}
	//std::cout << "Loaded " << numColours << " colours:" << std::endl;
	//for (int i = 0; i < numColours; i++)
	//{
	//	std::cout << "Colour " << i << ": (" << indexedColours[i].r << ", " << indexedColours[i].g << ", " << indexedColours[i].b << ")" << std::endl;
	//}
	//std::cout << "Loaded " << numIndices << " indices:" << std::endl;
	//for (int i = 0; i < numIndices; i++)
	//{
	//	std::cout << "Index " << i << ": " << indices[i] << std::endl;
	//}

	return true;
}
