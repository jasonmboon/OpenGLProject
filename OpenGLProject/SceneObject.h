#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
	protected:
		Mesh* _mesh;
		Texture2D* _texture;

	public:
		SceneObject(Mesh* mesh, Texture2D* texture);
		virtual ~SceneObject(void);

		virtual void Update() = 0;
		virtual void Draw(Vector3 position, Vector3 scale) = 0;
};

