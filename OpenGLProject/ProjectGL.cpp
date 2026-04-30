#pragma once
#include "ProjectGL.h"

// Color definitions
#define RED 1.0f, 0.0f, 0.0f, 1.0f
#define GREEN 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE 0.0f, 0.0f, 1.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f, 1.0f
#define CYAN 0.0f, 1.0f, 1.0f, 1.0f
#define MAGENTA 1.0f, 0.0f, 1.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f, 1.0f
#define GRAY 0.5f, 0.5f, 0.5f, 1.0f
#define ORANGE 1.0f, 0.5f, 0.0f, 1.0f

std::ofstream outFile;

ProjectGL::ProjectGL(int argc, char* argv[])
{
	glEnable(GL_CULL_FACE); // Enable back-face culling
	glCullFace(GL_BACK); // Specify that back faces should be culled
	//PolygonCount = 0;
	//rotation = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	// Depth testing
	
	glEnable(GL_DEPTH_TEST);


	// Camera
	camera = new Camera();
	camera->eye = { 0.0f, 0.0f, 1.0f };
	camera->centre = { 0.0f, 0.0f, 0.0f };
	camera->up = { 0.0f, 1.0f, 0.0f };	
	
	cube = new Cube(nullptr, 0.0f, 0.0f, 0.0f, 1.5f, 1.5f, 1.5f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45.0, 1.0, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	// end camera
	
	glEnable(GL_CULL_FACE); // Enable back-face culling
	glCullFace(GL_BACK); // Specify that back faces should be culled

	glutMainLoop();
}

ProjectGL::~ProjectGL(void)
{

}

void ProjectGL::Display()
{
	int m_CenterX = 0;
	int m_CenterY = 0;
	const int m_Coords = 2;
	const int m_Sides = 4;
	float m_Vertices[m_Sides][m_Coords] = {
		-0.5f, 0.0f, // Bottom Left
		-0.5f, 0.5f, // Top left
		 0.5f, 0.5f, // Top Right
		 0.5f, 0.0f, // Bottom Right
	};

	// Clear screen buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw grid with grid size of 0.1 and 10 lines in each direction
	DrawGrid(0.1f, 10);

	glPushMatrix();

	//glRotatef(rotation, 0.0f, 1.0f, 1.0f);

	// Draw the cube at the origin with a scale of 1.5 in all directions
	cube->Draw(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f));

	glPopMatrix();

	// Flush the buffer to the screen
	glFlush();
	glutSwapBuffers();
}

void ProjectGL::Update()
{
	glLoadIdentity();
	// Camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->centre.x, camera->centre.y, camera->centre.z,
		camera->up.x, camera->up.y, camera->up.z);

	if (cube->GetRotation() >= 360.0f)
	{
		cube->SetRotation(0.0f);
	}

	glutPostRedisplay();
}

void ProjectGL::Keyboard(unsigned char key, int x, int y)
{
	float curreRoration = cube->GetRotation();
	if (key == 'd')
			{
		cube->SetRotation(curreRoration -= 5.0f);
	}
	else if (key == 'a')
	{
		cube->SetRotation(curreRoration += 5.0f);
	}
	else if (key == 'w')
	{
		camera->eye.z -= 0.01f;
	}
	else if (key == 's')
	{
		camera->eye.z += 0.01f;
	}
}

void ProjectGL::DrawGrid(float gridSize, int numLines)
{

	glColor4f(GRAY);
	glTranslatef(0.0f, 0.0f, -3.0f); // Move the grid back so it's visible in the perspective view
	glBegin(GL_LINES);
	for (int i = -numLines; i <= numLines; i++)
	{
		glVertex2f(i * gridSize, -numLines * gridSize);
		glVertex2f(i * gridSize, numLines * gridSize);
		glVertex2f(-numLines * gridSize, i * gridSize);
		glVertex2f(numLines * gridSize, i * gridSize);
	}
	glEnd();
}


