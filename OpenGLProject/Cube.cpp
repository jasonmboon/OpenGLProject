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

	return true;
}

bool Cube::LoadObjectFile(char* path)
{
	numIndices = 0;
	numColours = 0;
	numVertices = 0;

	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Error opening file: " << path << std::endl;
		return false;
	}
	std::string line;
	while (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		if (prefix == "v")
		{
			numVertices++;
		}
		else if (prefix == "f")
		{
			numIndices += 3; // Assuming triangular faces
		}
	}

	inFile.clear(); // Clear EOF flag
	inFile.seekg(0); // Return to the beginning of the file

	// Allocate memory for vertices and indices
	indexedVertices = new Vertex[numVertices];
	indices = new GLushort[numIndices];
	indexedColours = new Colour[numIndices/3]; // No colour information in OBJ files

	int currentVertexPos = 0;
	int currentIndexPos = 0;

	// Read the file again to populate vertices
	if (indexedVertices != nullptr)
	{
		std::cout << "Memory allocated successfully for vertices." << std::endl;

		while (std::getline(inFile, line))
		{
			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if (currentVertexPos >= numVertices)
			{
				std::cerr << "Error: Current vertex exceeds allocated memory." << std::endl;
				break; // Prevent reading beyond allocated memory
			}
			
			if (currentVertexPos <= numVertices-3 && prefix == "v") {
				iss >> indexedVertices[currentVertexPos - 1].x >> indexedVertices[currentVertexPos - 1].y >> indexedVertices[currentVertexPos - 1].z;
				currentVertexPos++;
			}
		}
		std::cout << "Imported Vertices correctly" << std::endl;
	}

	inFile.clear(); // Clear EOF flag
	inFile.seekg(0); // Return to the beginning of the file

	// Read the file again to populate indices
	if (indices != nullptr)
	{
		std::cout << "Memory allocated successfully for indices." << std::endl;

		while (std::getline(inFile, line))
		{
			GLushort v1, v2, v3;
			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if (currentIndexPos >= numIndices)
			{
				std::cerr << "Error: Current index position exceeds allocated memory." << std::endl;
				break; // Prevent reading beyond allocated memory
			}

			if (currentIndexPos < numIndices && prefix == "f")
			{
				iss >> v1 >> v2 >> v3;
				indices[currentIndexPos + 2] = v1 - 1; // OBJ files are 1-indexed
				indices[currentIndexPos + 1] = v2 - 1;
				indices[currentIndexPos] = v3 - 1;
				currentIndexPos += 3;
			}
		}
		std::cout << "Imported Indices correctly" << std::endl;
	}
	return true;
}
