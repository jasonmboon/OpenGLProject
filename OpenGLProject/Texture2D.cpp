#include "Texture2D.h"

Texture2D::~Texture2D(void)
{
	glDeleteTextures(1, &textureID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;
	GLuint textureID = 0;

	// check if the texture has already been loaded by checking through linked list of texture IDs and file paths, if it has been loaded, return the existing texture ID instead of loading it again

	/// TODO: This is currently not working, need to fix the linked list implementation and ensure that the texture data is properly loaded into OpenGL even if the texture has been loaded before, this is just for testing purposes
	//while (textureList != nullptr)
	//{
	//	if (strcmp(textureList->filePath, path) == 0)
	//	{
	//		textureID = textureList->textureID;
	//		std::cout << "Texture file " << path << " already loaded. Using existing texture ID: " << textureID << std::endl;

	//		// load the texture data from the file again to ensure the texture is properly loaded into OpenGL, even if it has been loaded before
	//		glBindTexture(GL_TEXTURE_2D, textureID);	
	//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);

	//		return true;
	//	}
	//	textureID = textureList->textureID;
	//	textureList = textureList->next;
	//}

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

	std::cout << "Texture file " << path << " loaded successfully. File size: " << fileSize << " bytes." << std::endl;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;

}
