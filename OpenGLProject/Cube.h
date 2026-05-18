#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	float _rotation;
	static Vertex* indexedVertices;
	static Colour* indexedColours;
	static TexCoord* indexedTextures;
	static Vector3* indexedNormals;
	static GLushort* indices;
	static int numVertices, numNormals, numColours, numIndices;
	Vector3 _position;
	Vector3 _scale;
	bool isObjectFile = false;
	char* filePath;
	int polygonCount;
	float rotation;

public:
	Cube(Mesh* mesh, Texture2D* texture, float _posX, float _posY, float _posZ, float _scaleX, float _scaleY, float _scaleZ);
	~Cube(void);

	// Getters for static members
	Vertex* GetVertices() { return indexedVertices; }
	Vector3* GetNormals() { return indexedNormals; }
	GLushort* GetIndices() { return indices; }
	TexCoord* GetTexCoords() { return indexedTextures; }
	int GetPolyCount() { return numIndices; }
	int GetVertexCount() { return numVertices; }

	// Getters and settings for file path, isObjectFile and polygon count
	void SetFilePath(char* _filePath) {
		filePath = _filePath;
	}
	char* GetFilePath() {
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

	float GetRotation() {
		return rotation;
	}
	void SetRotation(float _rotation) {
		rotation = _rotation;
	}

	// Override virtual functions from SceneObject
	void Update();
	void Draw(Vector3 position, Vector3 scale);
	static bool Load(char* path);
	static bool LoadEnhanced(char* path);
	static bool LoadObjectFile(char* path);
	static GLint LoadTextureTGA(char* path);
};

