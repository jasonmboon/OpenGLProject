#pragma once
#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture) : _mesh(mesh), _texture(texture)
{
	//_mesh = new Mesh();
	_mesh = mesh;
	_texture = texture;
}

SceneObject::~SceneObject(void)
{

}