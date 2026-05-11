#pragma once
#include "Cube.h"
#include "MeshLoader.h"
#include "Texture2D.h"

Mesh* m_Mesh = nullptr;
int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
Vector3* Cube::indexedNormals = nullptr;
TexCoord* Cube::indexedTextures = nullptr;
GLushort* Cube::indices = nullptr;

Cube::Cube(Mesh* mesh, Texture2D* texture, float _posX, float _posY, float _posZ, float _scaleX, float _scaleY, float _scaleZ) : SceneObject(mesh, nullptr)
{
	rotation = 0.1f;

	// Change from true -> OBJ file, false -> text file depending on what you want to display
	SetIsObjectFile(false);

	if (GetIsObjectFile())
	{
		// Need to update the obj reader to read in normals and texture coordinates as well, plus materials
		SetFilePath((char*)"./Other Files/teapot.obj");
		Cube::LoadObjectFile(GetFilePath());
	}
	else
	{
		// Testing new cube with texture
		SetFilePath((char*)"cube.txt");
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
		bool texturesLoaded = true;
		int indexedIndicesCount = GetPolyCount();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glBindTexture(GL_TEXTURE_2D, _texture->GetTextureID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// Textures
		glEnable(GL_TEXTURE_2D);
		Texture2D* texture = new Texture2D();
		texturesLoaded = texture->Load((char*)"./Other Files/stars.raw", 512, 512);

		if (!texturesLoaded)
		{
			std::cerr << "Failed to load texture." << std::endl;
			return;
		}

		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

		glVertexPointer(3, GL_FLOAT, 0, GetVertices());
		glColorPointer(3, GL_FLOAT, 0, GetColours());
		//glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glTexCoordPointer(2, GL_FLOAT, 0, indexedTextures);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation, 0.0f, 1.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, indexedIndicesCount, GL_UNSIGNED_SHORT, GetIndices());
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

	/// TODO: Delete the contents here and call the Mesh loader functions instead, this is just for testing purposes

	Mesh* mesh = MeshLoader::Load(path);

	if (mesh)
	{
		// Use the loaded mesh data
		// For example:
		indexedVertices = mesh->Vertices;
		indexedNormals = mesh->Normals;
		indexedTextures =mesh->TexCoords;
		indices = mesh->Indices;
	}
	else
	{
		std::cerr << "Failed to load mesh from: " << path << std::endl;
		return false;
	}

	//std::ifstream inFile;
	//inFile.open(path);
	//if (!inFile.good())
	//{
	//	std::cerr << "Error opening file: " << path << std::endl;
	//	return false;
	//}

	//inFile >> numVertices;
	//indexedVertices = new Vertex[numVertices];
	//for (int i = 0; i < numVertices; i++)
	//{
	//	inFile >> indexedVertices[i].x >> indexedVertices[i].y >> indexedVertices[i].z;
	//}

	//inFile >> numColours;
	//indexedColours = new Colour[numColours]; // Needs to be Textures
	//for (int i = 0; i < numColours; i++)
	//{
	//	inFile >> indexedColours[i].r >> indexedColours[i].g >> indexedColours[i].b;
	//}

	//inFile >> numIndices;
	//indices = new GLushort[numIndices];
	//for (int i = 0; i < numIndices; i++)
	//{
	//	inFile >> indices[i];
	//}

	return true;
}

bool Cube::LoadEnhanced(char* path)
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

int LoadTextureTGA(const char* textureFileName)
{
	GLuint ID = 0;
	char* tempHeaderData = new char[18]; //18 Bytes is TGA Header Size
	char* tempTextureData;
	int fileSize;
	char type, pixelDepth, mode;

	std::ifstream inFile;

	inFile.open(textureFileName, std::ios::binary);
	if (!inFile.good())
	{
		std::cerr << "Can't open texture file " << textureFileName << std::endl;
		return -1;
	}

	//18 Bytes is the size of a TGA Header
	inFile.seekg(0, std::ios::beg); //Seek back to beginning of file
	inFile.read(tempHeaderData, 18); //Read in all the data in one go

	inFile.seekg(0, std::ios::end); //Seek to end of file
	fileSize = (int)inFile.tellg() - 18; //Get current position in file - The End, this gives us total file size
	tempTextureData = new char[fileSize]; //Create an new aray to store data
	inFile.seekg(18, std::ios::beg); //Seek back to beginning of file + 18
	inFile.read(tempTextureData, fileSize); //Read in all the data in one go
	inFile.close(); //Close the file

	type = tempHeaderData[2]; //Get TGA Type out of Header - Must be RGB for this to work
	int _width = ((unsigned char)tempHeaderData[13] << 8u) + (unsigned char)tempHeaderData[12]; // Find the width (Combines two bytes into a short)
	int _height = ((unsigned char)tempHeaderData[15] << 8u) + (unsigned char)tempHeaderData[14]; //Find the height
	pixelDepth = tempHeaderData[16]; // Find the pixel depth (24/32bpp)

	bool flipped = false;
	if ((int)((tempHeaderData[11] << 8) + tempHeaderData[10]) == 0)
		flipped = true;

	//We only support RGB type
	if (type == 2)
	{
		std::cout << textureFileName << " loaded." << std::endl;

		glGenTextures(1, &ID); //Get next Texture ID
		glBindTexture(GL_TEXTURE_2D, ID); //Bind the texture to the ID

		mode = pixelDepth / 8;

		//Note that TGA files are stored as BGR(A) - So we need to specify the format as GL_BGR(A)_EXT
		if (mode == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempTextureData);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);

	}

	delete[] tempHeaderData; //We don't need the header memory anymore
	delete[] tempTextureData; //Clear up the data - We don't need this any more

	return ID;
}
