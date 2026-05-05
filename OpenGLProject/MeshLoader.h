#pragma once

#include "Structures.h"
#include "Texture2D.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	TexturedMesh* LoadTextured(char* path);
};