//#pragma once
//
//#include <Windows.h>
//#include "gl/GL.h"
//#include "gl/GLU.h"
//#include "GL/freeglut.h"
//#include "GLUTCallbacks.h"
//#include <math.h>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include "Structures.h"
//#include "SceneObject.h"
//#include "Cube.h"
//
//#define REFRESHRATE 16
//
//class ProjectGL
//{
//private:
//	//Private member variables and functions
//	float rotation;
//
//	static Vertex vertices[];
//	static Colour colours[];
//	Camera* camera;
//	Cube* cube;
//	//point3d* Vertices;
//	//Colour* Colours;
//	//polygon3d* indices;
//	//int PolygonCount;
//
//public:
//	//Constructor and Destructor
//	ProjectGL(int argc, char* argv[]);
//	~ProjectGL(void);
//
//	void Update();
//	void Display();
//
//	void Keyboard(unsigned char key, int x, int y);
//	void DrawGrid(float gridSize, int numLines);
//
//	/// Old code for drawing 2D polygons, which will be replaced with new functions that are more efficient and flexible, 
//	/// but still useful to keep as a reference for how to draw basic 2D shapes in OpenGL.
//
//	//void DrawPolygon();
//	//void DrawRegularPolygon(float m_CenterX, float m_CenterY, float m_Radius, int m_Segments);
//	//void DrawFilledCircle(float m_CenterX, float m_CenterY, float m_Radius, int m_Segments);
//	//void DrawPolygon2D(float m_Vertices[][2], int m_Sides);
//	//void DrawText(float x, float y, const std::string& text);
//
//
//	////3d drawing functions
//	//void ProcessPolygon3d();
//	//void DrawPolygon3d(int a, int b, int c);
//	//void DrawCube();
//
//	//void ProcessPolygonOBJ();
//	//void DrawPolygonOBJ(int a, int b, int c);
//	//void DrawOBJ();
//};
//#pragma once
