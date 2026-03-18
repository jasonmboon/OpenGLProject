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


ProjectGL::ProjectGL(int argc, char* argv[])
{
	glEnable(GL_CULL_FACE); // Enable back-face culling
	glCullFace(GL_BACK); // Specify that back faces should be culled
	PolygonCount = 0;
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
	//DrawGrid(0.1f, 10);

	//DrawRegularPolygon(0.3f, -0.3f, 0.3f, 7);

	glPushMatrix();
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	glutWireTeapot(0.1);
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


	//rotation += 0.5f;

	if (rotation >= 360.0f)
	{
		rotation = 0.0f;
	}

	glutPostRedisplay();
}

void ProjectGL::DrawPolygon()
{
	glBegin(GL_POLYGON);
	{
		float scale = 0.5f;
		//glScalef(scale, scale, scale);
		glColor4f(RED);
		glVertex2f(-0.5, 0.0);
		glColor4f(BLUE);
		glVertex2f(0.5, 0.0);
		glColor4f(YELLOW);
		glVertex2f(0.789, 0.307);
		glColor4f(WHITE);
		glVertex2f(-0.211, 0.307);
		glEnd();
	}
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
}







/// <summary>
/// Previous Draw functions ahead - Testing 2D and Basic 3D technicques. These functions are not used in the final program, but they were used for testing and learning purposes. 
/// They can be used as a reference for how to draw basic shapes and polygons in OpenGL, and how to read polygon data from a file and store it in arrays.
/// </summary>

/// <param name="m_Vertices"></param>
/// <param name="m_Sides"></param>
void ProjectGL::DrawPolygon2D(float m_Vertices[][2], int m_Sides)
{
	float m_CenterX = -0.5;
	float m_CenterY = 0.5;
	glPushMatrix();
	//glTranslatef(m_CenterX, m_CenterY, 0);
	//glRotatef(rotation, 0, 0, -1.0f); // Rotate around the Z-axis
	//glTranslatef(-m_CenterX, -m_CenterY, 0);
	glBegin(GL_POLYGON);
	{
		float scale = 0.5f;
		//glScalef(scale, scale, scale);

		for (int i = 0; i < m_Sides; i++)
		{
			glColor4f(BLUE);
			glVertex2f(m_Vertices[i][0], m_Vertices[i][1]);
		}

		glEnd();
	}
	glPopMatrix();
}

// Draw filled circle with center at (cx, cy) and radius r
void ProjectGL::DrawFilledCircle(float m_CenterX, float m_CenterY, float m_Radius, int m_Segments)
{
	int m_ColorStep = 0;

	glPushMatrix();

	// Translate to centre of polygon before rotating
	glTranslatef(m_CenterX, m_CenterY, 0);
	glRotatef(rotation, 0, 0, -1.0f); // Rotate around the Z-axis
	glTranslatef(-m_CenterX, -m_CenterY, 0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_Segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(m_Segments); // get the current angle
		float x = m_Radius * cosf(theta); // calculate the x component
		float y = m_Radius * sinf(theta); // calculate the y component
		glColor4f(BLUE);
		glVertex2d(m_CenterX, m_CenterY); // output center of circle
		m_ColorStep = (i + 1) % 100;
		glColor4f(ORANGE);
		glVertex2f(x + m_CenterX, y + m_CenterY); // output vertex
	}
	glEnd();
	glPopMatrix();
}

// Draw regular polygon with center at (cx, cy) and radius r. A regular polygon is where each side is the same length and each angle is the same. The number of segments determines how many sides the polygon has. 
// For example, if segments is 3, it will draw a triangle. If segments is 4, it will draw a square, and so on.
void ProjectGL::DrawRegularPolygon(float m_CenterX, float m_CenterY, float m_Radius, int m_Segments)
{
	float rotationAngle = 0.0f; // Rotation angle in degrees
	glColor4f(RED);
	int m_ColorStep = 0;
	glTranslatef(0.0f, 0.0f, -3.0f); // Move the grid back so it's visible in the perspective view
	glPushMatrix();

	// Translate to centre of polygon before rotating
	glTranslatef(m_CenterX, m_CenterY, 0);
	glRotatef(rotation, 0, 0, 1.0f); // Rotate around the Z-axis
	glTranslatef(-m_CenterX, -m_CenterY, 0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < m_Segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(m_Segments); // get the current angle
		float x = m_Radius * cosf(theta); // calculate the x component
		float y = m_Radius * sinf(theta); // calculate the y component
		glVertex2f(x + m_CenterX, y + m_CenterY); // output vertex
	}

	glEnd();

	glPopMatrix();
}

void ProjectGL::DrawText(float x, float y, const std::string& text)
{
	glColor4f(WHITE);
	glRasterPos2f(x, y);
	for (char c : text)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
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

void ProjectGL::ProcessPolygon3d()
{
	int numVertices = 0;
	int numColours = 0;
	int numPolygons = 0;
	int index = 0;
	char delimiter = ',';
	std::string segment;
	std::string InputLine;
	int pos = 0;

	// Read the polygon data from the file and store it in the Vertices, Colours, and indices arrays
	//std::ifstream file("pyramid1.txt");
	std::ifstream file("polygon1.txt");
	std::string line;

	// read first line to determine how many vertices there are

	std::getline(file, line);
	std::istringstream iss(line);
	iss >> numVertices;

	// Read vertices
	Vertices = new point3d[numVertices];

	while (numVertices > 0 || numColours > 0 || numPolygons > 0)
	{
		if (numVertices > 0)
		{
			std::getline(file, line);
			InputLine = line;
			pos = InputLine.find(',');
			Vertices[index].x = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Vertices[index].y = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Vertices[index].z = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			numVertices--;
			index++;
		}

		if (numVertices == 0 && numColours == 0 && numPolygons == 0)
		{
			std::getline(file, line);
			iss = std::istringstream(line);
			iss >> numColours;
			Colours = new Colour[numColours];
			index = 0;
		}

		if (numColours > 0)
		{
			std::getline(file, line);
			InputLine = line;
			pos = InputLine.find(',');
			Colours[index].r = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Colours[index].g = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Colours[index].b = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			numColours--;
			index++;
		}

		if (numVertices == 0 && numColours == 0 && numPolygons == 0)
		{
			std::getline(file, line);
			iss = std::istringstream(line);
			iss >> numPolygons;
			PolygonCount = numPolygons;
			indices = new polygon3d[numPolygons];
			index = 0;
		}


		if (numPolygons > 0)
		{
			std::getline(file, line);
			InputLine = line;
			pos = InputLine.find(',');
			indices[index].a = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			indices[index].b = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			indices[index].c = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			numPolygons--;
			index++;
		}
	}
	file.close();

}

void ProjectGL::DrawPolygon3d(int a, int b, int c)
{
	glPushMatrix();
	// Translate to centre of polygon before rotating
	glTranslatef(0, 0, 0);
	glRotatef(rotation, 0.3, 0, 0.3f); // Rotate around the Z-axis
	glTranslatef(-0, -0, 0);

	// Implementation for drawing a 3D polygon with 4 vertices
	glBegin(GL_QUADS);
	glVertex3fv(&Vertices[a].x);
	glVertex3fv(&Vertices[b].x);
	glVertex3fv(&Vertices[c].x);
	glEnd();

	glPopMatrix();


}

void ProjectGL::DrawCube()
{
	int NUM_POLY = PolygonCount;
	for (int i = 0; i < NUM_POLY; i++)
	{
		glColor3f(Colours[i].r, Colours[i].g, Colours[i].b);
		DrawPolygon3d(indices[i].a, indices[i].b, indices[i].c);
	}
}


/// <summary>
/// The following is obsolete as new functions will be created to handle this in a more efficient way, but it is still useful to keep as a reference for how to read polygon data from a file and store it in arrays, and how to draw basic 3D polygons in OpenGL.
/// </summary>

void ProjectGL::ProcessPolygonOBJ()
{
	int numVertices = 0;
	int numColours = 0;
	int numPolygons = 0;
	int index = 0;
	char delimiter = ',';
	std::string segment;
	std::string InputLine;
	int pos = 0;

	// Read the polygon data from the file and store it in the Vertices, Colours, and indices arrays
	//std::ifstream file("pyramid1.txt");
	//std::ifstream file("polygon1.txt");
	std::ifstream file("teapot.txt");
	std::string line;

	// read first line to determine how many vertices there are

	std::getline(file, line);
	std::istringstream iss(line);
	iss >> numVertices;

	// Read vertices
	Vertices = new point3d[numVertices];

	while (numVertices > 0 || numColours > 0 || numPolygons > 0)
	{
		if (numVertices > 0)
		{
			std::getline(file, line);
			InputLine = line;
			pos = InputLine.find(',');
			Vertices[index].x = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Vertices[index].y = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			Vertices[index].z = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			numVertices--;
			index++;
		}

		//if (numVertices == 0 && numColours == 0 && numPolygons == 0)
		//{
		//	std::getline(file, line);
		//	iss = std::istringstream(line);
		//	iss >> numColours;
		//	Colours = new colour[numColours];
		//	index = 0;
		//}

		//if (numColours > 0)
		//{
		//	std::getline(file, line);
		//	InputLine = line;
		//	pos = InputLine.find(',');
		//	Colours[index].r = strtof(InputLine.substr(0, pos).c_str(), nullptr);
		//	InputLine.erase(0, pos + 1);

		//	pos = InputLine.find(',');
		//	Colours[index].g = strtof(InputLine.substr(0, pos).c_str(), nullptr);
		//	InputLine.erase(0, pos + 1);

		//	pos = InputLine.find(',');
		//	Colours[index].b = strtof(InputLine.substr(0, pos).c_str(), nullptr);
		//	InputLine.erase(0, pos + 1);

		//	numColours--;
		//	index++;
		//}

		if (numVertices == 0 && numColours == 0 && numPolygons == 0)
		{
			std::getline(file, line);
			iss = std::istringstream(line);
			iss >> numPolygons;
			PolygonCount = numPolygons;
			indices = new polygon3d[numPolygons];
			index = 0;
		}


		if (numPolygons > 0)
		{
			std::getline(file, line);
			InputLine = line;
			pos = InputLine.find(',');
			indices[index].a = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			indices[index].b = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			indices[index].c = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			pos = InputLine.find(',');
			indices[index].d = strtof(InputLine.substr(0, pos).c_str(), nullptr);
			InputLine.erase(0, pos + 1);

			numPolygons--;
			index++;
		}
	}
	file.close();

}

void ProjectGL::DrawPolygonOBJ(int a, int b, int c)
{
	//glColor4f(GRAY);
	glPushMatrix();
	// Translate to centre of polygon before rotating
	//glTranslatef(0, 0, 0);
	//glRotatef(rotation, 0.3, 0, 0.3f); // Rotate around the Z-axis
	//glTranslatef(-0, -0, 0);


	// try to scale the object down to fit in the view
	glTranslatef(0, -0.3, 0);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(rotation, 0.3, 0, 0.3f);
	glTranslatef(-0, -0.3, -0);

	// Implementation for drawing a 3D polygon with 4 vertices
	glBegin(GL_TRIANGLES);
	glVertex3fv(&Vertices[a].x);
	glVertex3fv(&Vertices[b].x);
	glVertex3fv(&Vertices[c].x);
	//glVertex3fv(&Vertices[d].x);
	glEnd();

	glPopMatrix();
}

void ProjectGL::DrawOBJ()
{
	int NUM_POLY = PolygonCount;
	for (int i = 0; i < NUM_POLY; i++)
	{
		//glColor3f(Colours[i].r, Colours[i].g, Colours[i].b);
		DrawPolygonOBJ(indices[i].a, indices[i].b, indices[i].c);
	}
}
ProjectGL::~ProjectGL(void)
{

}