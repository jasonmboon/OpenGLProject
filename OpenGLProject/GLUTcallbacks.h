#pragma once

class ProjectGL;

namespace GLUTCallbacks
{
	void Init(ProjectGL* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);
}