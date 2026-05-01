#pragma once
#include "Cube.h"

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
GLushort* Cube::indices = nullptr;

Cube::Cube(Mesh* mesh, float _posX, float _posY, float _posZ, float _scaleX, float _scaleY, float _scaleZ) : SceneObject(mesh)
{
	rotation = 0.1f;

	// Change from true -> OBJ file, false -> text file depending on what you want to display
	SetIsObjectFile(true);

	if (GetIsObjectFile())
	{
		SetFilePath((char*)"./Other Files/teapot.obj");
		Cube::LoadObjectFile(GetFilePath());
	}
	else
	{
		SetFilePath((char*)"pyramid.txt");
		Cube::Load(GetFilePath());
	}

	setPolygonCount(GetPolyCount());
	_position = Vector3(_posX, _posY, _posZ);
	_scale = Vector3(_scaleX, _scaleY, _scaleZ);
}

Cube::~Cube(void)
{
}

void Cube::Draw(Vector3 position, Vector3 scale)
{
	if (GetIsObjectFile())
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		int polyCount = GetPolyCount();
		glVertexPointer(3, GL_FLOAT, 0, GetVertices());

		//glColorPointer(3, GL_FLOAT, 0, cube->GetColours());

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation, 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, GetPolyCount() * 3, GL_UNSIGNED_SHORT, GetIndices());

		glPopMatrix();

		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else
	{
		int indexedIndicesCount = GetPolyCount();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);


		glVertexPointer(3, GL_FLOAT, 0, GetVertices());
		glColorPointer(3, GL_FLOAT, 0, GetColours());

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation, 0.0f, 1.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, indexedIndicesCount, GL_UNSIGNED_SHORT, GetIndices());
		glPopMatrix();


		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
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
	int numIndicesTotal = 0;

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
			numIndices++; // Assuming triangular faces
		}
	}

	numIndicesTotal = numIndices * 3; // Store original count for later use

	inFile.clear(); // Clear EOF flag
	inFile.seekg(0); // Return to the beginning of the file

	// Allocate memory for vertices and indices
	indexedVertices = new Vertex[numVertices];
	indices = new GLushort[numIndices * 3];
	indexedColours = new Colour[numColours]; // No colour information in OBJ files

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

			if (currentVertexPos > numVertices)
			{
				std::cerr << "Error: Current vertex exceeds allocated memory." << std::endl;
				break; // Prevent reading beyond allocated memory
			}
			
			if (currentVertexPos < numVertices && prefix == "v") {
				iss >> indexedVertices[currentVertexPos].x >> indexedVertices[currentVertexPos].y >> indexedVertices[currentVertexPos].z;
				currentVertexPos++;
			}
		}
		std::cout << "Imported Vertices correctly" << std::endl;
	}

	inFile.clear(); // Clear EOF flag
	inFile.seekg(0); // Return to the beginning of the file
	currentIndexPos = 0; 	// Reset index position for reading indices
	
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

			// Check array bounds before writing to indices
			if (currentIndexPos >= numIndicesTotal)
			{
				std::cerr << "Error: Current index position exceeds allocated memory." << std::endl;
				std::cout << "Current index position: " << currentIndexPos << ", Number of indices: " << numIndicesTotal << std::endl;
				break; // Prevent reading beyond allocated memory
			}

			// OBJ files are 1-indexed, so we subtract 1 to convert to 0-indexed
			// Assuming faces are defined as "f v1 v2 v3" and we only care about vertex indices
			if (currentIndexPos <= numIndicesTotal && prefix == "f")
			{
				iss >> v1 >> v2 >> v3;

				// OBJ files are 1-indexed
				indices[currentIndexPos + 2] = v1 - 1; 
				indices[currentIndexPos + 1] = v2 - 1;
				indices[currentIndexPos] = v3 - 1;
				currentIndexPos += 3;
			}
		}
		std::cout << "Imported Indices correctly" << std::endl;
	}
	return true;
}
