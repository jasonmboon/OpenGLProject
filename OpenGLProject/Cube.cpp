#pragma once
#include "Cube.h"

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
