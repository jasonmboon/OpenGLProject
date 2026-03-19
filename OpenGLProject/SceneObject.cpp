#pragma once
#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh) : _mesh(mesh)
{
	_mesh = mesh;
}

SceneObject::~SceneObject(void)
{

}