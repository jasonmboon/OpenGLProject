#include "Texture2D.h"

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D(void)
{
	glDeleteTextures(1, &textureID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;
	textureID = 0;

	// If we reach here, it means the texture has not been loaded yet, so we proceed to load it
	textureID++; // Increment texture ID for new texture

	this->width = width;
	this->height = height;

	inFile.open(path, std::ios::binary);

	if (!inFile.good())
	{
		std::cerr << "Can't open texture file " << path << std::endl;
		return false;
	}

	inFile.seekg(0, std::ios::end);
	fileSize = static_cast<int>(inFile.tellg());
	tempTextureData = new char[fileSize];
	inFile.seekg(0, std::ios::beg);

	inFile.read(tempTextureData, fileSize);
	inFile.close();

	textureList = new TextureNode(textureID, path); // Add new texture to the linked list
	textureID = textureList->textureID; // Update the texture ID to the new one

	std::cout << "Texture file " << path << " loaded successfully. File size: " << fileSize << " bytes. TextureID = " << textureID << std::endl;

	// Generate and bind the texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// set texure wrap mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload the texture data to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);
	//glGenerateMipmap(GL_TEXTURE_2D);

	delete[] tempTextureData;
	return true;
}
