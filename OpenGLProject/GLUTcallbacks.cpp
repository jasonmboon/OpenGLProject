#include "GLUTCallbacks.h"
#include "ProjectGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		ProjectGL* projectGL = nullptr;
	}

	void Init(ProjectGL* gl)
	{
		projectGL = gl;
	}

	void Display()
	{
		if (projectGL != nullptr)
		{
			projectGL->Display();
		}

	}

	void Timer(int preferredRefresh)
	{
		if (projectGL != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			projectGL->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, Timer, preferredRefresh);
		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		if (projectGL != nullptr)
		{
			projectGL->Keyboard(key, x, y);
		}
	}

}