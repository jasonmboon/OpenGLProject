#pragma once
#include "Structures.h"

class SceneObject
{
	protected:
		Mesh* _mesh;

	public:
		SceneObject(Mesh* mesh);
		virtual ~SceneObject(void);

		virtual void Update() = 0;
		virtual void Draw() = 0;
};

