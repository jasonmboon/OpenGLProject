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

lighting whiteLighting = {
	{0.2f, 0.2f, 0.2f, 1.0f}, // Ambient light
	{0.7f, 0.7f, 0.7f, 1.0f}, // Diffuse light
	{0.5f, 0.5f, 0.5f, 1.0f}  // Specular light
};

material redShinyMaterial = {
	{0.8f, 0.05f, 0.05f, 1.0f}, // Ambient reflectance
	{0.8f, 0.05f, 0.05f, 1.0f}, // Diffuse reflectance
	{1.0f, 1.0f, 1.0f, 1.0f}, // Specular reflectance
	100.0f                      // Shininess
};

float light0_pos[] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
	glEnable(GL_NORMALIZE); // Enable automatic normalization of normals for correct lighting
	// Depth testing
	
	glEnable(GL_DEPTH_TEST);

	// Camera
	camera = new Camera();
	camera->eye = { 0.0f, 0.0f, 3.0f };
	camera->centre = { 0.0f, 0.0f, 0.0f };
	camera->up = { 0.0f, 1.0f, 0.0f };	
	
	cube = new Cube(nullptr, 0.0f, 0.0f, 0.0f, 1.1f, 1.1f, 1.1f);
	cube2 = new Cube(nullptr, 0.3f, 0.3f, 0.3f, 1.3f, 1.3f, 1.3f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45.0, 1.0, 0.1, 1000.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);
	// end camera

	setLight(&whiteLighting);
	
	glEnable(GL_CULL_FACE); // Enable back-face culling
	glCullFace(GL_BACK); // Specify that back faces should be culled

	glutMainLoop();
}

ProjectGL::~ProjectGL(void)
{

}

void ProjectGL::Display()
{
	// Clear screen buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw grid with grid size of 0.1 and 10 lines in each direction
	//DrawGrid(0.1f, 10);
	setMaterial(&redShinyMaterial);
	
	glPushMatrix();

	// Draw the image at the origin first, with a given scale second
	cube->Draw(Vector3(0.0f, -0.2f, 0.0f), Vector3(0.05f, 0.05f, 0.05f));

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
	float currentRotation = cube->GetRotation();
	if (key == 'd')
	{
		cube->SetRotation(currentRotation -= 5.0f);
	}
	else if (key == 'a')
	{
		cube->SetRotation(currentRotation += 5.0f);
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

void ProjectGL::setLight(lighting* light)
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, light->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light->specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
}

void ProjectGL::setMaterial(material* mat)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat->shininess);
}
