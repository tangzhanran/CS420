#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <time.h>

#include "Point.h"

using namespace std;

#define NumOfPoints 100000

GLuint buffer;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the window

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0, NumOfPoints);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Hello,GL"
	glutCreateWindow("Sierpinski Gasket");
	glutDisplayFunc(display);

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	Point initvertex[3] = { Point(-1.0, -1.0), Point(1.0, -1.0), Point(0.0, 1.0) }; //vertices of triangle
	Point vertices[NumOfPoints];
	vertices[0].x = 0.0;
	vertices[0].y = 0.0;
	srand(time(NULL));
	for (int i = 1; i < NumOfPoints; i++)
	{
		int r = rand() % 3;
		vertices[i].x = (vertices[i-1].x + initvertex[r].x) / 2;
		vertices[i].y = (vertices[i-1].y + initvertex[r].y) / 2;
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glutMainLoop();

	return 0;
}