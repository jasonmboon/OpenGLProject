#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	Vector3 _position;
	GLfloat _rotation;
	GLfloat _rotationValue;
	GLfloat _zMovement;

public:
	Cube(Mesh* mmesh, float x, float y, float z);
	~Cube(void);

	void Update();
	void Draw();
};

