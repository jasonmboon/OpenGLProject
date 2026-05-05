#include "Texture2D.h"

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;
 
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

	std::cout << "Texture file " << path << " loaded successfully. File size: " << fileSize << " bytes." << std::endl;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;
}
