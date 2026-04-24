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

//Vertex ProjectGL::indexedVertices[] = { 1, 1, 1, -1, 1, 1, // v0,v1,
//										-1,-1, 1, 1,-1, 1, // v2,v3
//										1,-1,-1, 1, 1,-1, // v4,v5
//										-1, 1,-1, -1,-1,-1 }; // v6,v7
//
////
////Colour ProjectGL::indexedColours[] = { 1, 1, 1, 1, 1, 0, // v0,v1,
////										1, 0, 0, 1, 0, 1, // v2,v3
////										0, 0, 1, 0, 1, 1, // v4,v5
////										0, 1, 0, 0, 0, 0 }; //v6,v7
//
//Colour ProjectGL::indexedColours[] = { 1, 1, 1, 0, 0, 0, // v0,v1,
//										1, 1 ,1, 0, 0, 0, // v2,v3
//										1, 1, 1, 0, 0, 0, // v4,v5
//										1, 1, 1, 0, 0, 0 }; //v6,v7
//
//
//GLushort ProjectGL::indices[] = { 0, 1, 2, 2, 3, 0, // front
//									0, 3, 4, 4, 5, 0, // right
//									0, 5, 6, 6, 1, 0, // top
//									1, 6, 7, 7, 2, 1, // left
//									7, 4, 3, 3, 2, 7, // bottom
//									4, 7, 6, 6, 5, 4 }; // back
std::ofstream outFile;

ProjectGL::ProjectGL(int argc, char* argv[])
{
	glEnable(GL_CULL_FACE); // Enable back-face culling
	glCullFace(GL_BACK); // Specify that back faces should be culled
	//PolygonCount = 0;
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	// Camera
	camera = new Camera();
	camera->eye = { 0.0f, 0.0f, 1.0f };
	camera->centre = { 0.0f, 0.0f, 0.0f };
	camera->up = { 0.0f, 1.0f, 0.0f };	
	
	cube = new Cube(nullptr, 0.0f, 0.0f, 0.0f);
	
	// Change from true -> OBJ file, false -> text file depending on what you want to display
	SetIsObjectFile(false);
	
	if (GetIsObjectFile())
	{
		SetFilePath((char*)"./Other Files/teapota.obj"); 
		Cube::LoadObjectFile(GetFilePath());
	}
	else
	{
		SetFilePath((char*)"pyramid.txt");
		Cube::Load(GetFilePath());
	}

	setPolygonCount(cube->GetPolyCount());
	
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
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw grid with grid size of 0.1 and 10 lines in each direction
	DrawGrid(0.1f, 10);

	glPushMatrix();

	glRotatef(rotation, 0.0f, 1.0f, 1.0f);

	if (GetIsObjectFile())
	{
		//DrawIndexedCubeFile1();
		DrawObjFile();
	}
	else
	{
		DrawIndexedCubeFile();
	}

	//glutWireTeapot(0.1);
	//cube->Draw();

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

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}

	glutPostRedisplay();
}

void ProjectGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
			{
		rotation -= 5.0f;
	}
	else if (key == 'a')
	{
		rotation += 5.0f;
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

void ProjectGL::DrawIndexedCubeAlt()
{
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	//glColorPointer(3, GL_FLOAT, 0, indexedColours);

	//glPushMatrix();
	//glScalef(0.5f, 0.5f, 0.5f);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	//glPopMatrix();

	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
}

void ProjectGL::DrawIndexedCubeFile()
{
	int indexedIndicesCount = cube->GetPolyCount();	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, cube->GetVertices());
	glColorPointer(3, GL_FLOAT, 0, cube->GetColours());

	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);

	glDrawElements(GL_TRIANGLES, indexedIndicesCount, GL_UNSIGNED_SHORT, cube->GetIndices());
	glPopMatrix();


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// Draw OpenGl .obj faile using vertex arrays
void ProjectGL::DrawObjFile()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	int polyCount = cube->GetPolyCount();
	glVertexPointer(3, GL_FLOAT, 0, cube->GetVertices());

	//glColorPointer(3, GL_FLOAT, 0, cube->GetColours());

	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glDrawElements(GL_TRIANGLES, cube->GetPolyCount()*3, GL_UNSIGNED_SHORT, cube->GetIndices());
	
	glPopMatrix();

	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// Draw OpenGL .obj file from the values obtained in the vetices and indices
// These can be obtained using the cube::getVertices() and cube::getIndices() functions which return the vertices and indices respectively
void ProjectGL::DrawIndexedCubeFile1()
{
	int indexedIndicesCount = cube->GetPolyCount()*3;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube->GetVertices());
	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glDrawElements(GL_TRIANGLES, indexedIndicesCount, GL_UNSIGNED_SHORT, cube->GetIndices());
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}