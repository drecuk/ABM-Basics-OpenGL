//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ OpenGL Application
//	Drawing a Rectangle with OpenGL and GLUT
//
// How to compile:
// sudo g++ -I/usr/include <filename>.cpp -o <output file> -L/usr/lib -lGL -lGLU -lglut
//
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

/****************************** INCLUDES ******************************/
#include <iostream>
#include <GL/gl.h>        // OpenGL
#include <GL/freeglut.h>  // OpenGL Utility Kit
#include <GL/glu.h>       // GLU is higher level function for OpenGL

// OpenGL Utilities
#include "OGLUtil.h"    // all OpenGL headers
#include "Matrix4x4.h"  // Matrix Maths Functionsß

using namespace std;

/****************************** GLOBAL VARIABLES ******************************/
Matrix4x4 mPos;            // matrices for positional transform
Matrix4x4 mRot;            // matrices for rotational transform
float rx, ry, rz = 0;

// Reset our viewport after a window resize
int setViewport( int width, int height )
{
    GLfloat ratio;

    // prevent divide by zero
    if ( height == 0 ) { height = 1; }

    // calculate ratio
    ratio = ( GLfloat )width / ( GLfloat )height;

    // Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    // specify which matrix is the current matrix
    // GL_PROJECTION means that we are applying all matrix to the PROJECTION MATRIX
    glMatrixMode(GL_PROJECTION);

    // Reset The Projection Matrix, generally done before we do anything to the matrix
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // use glu function to set a camera looking at
    // void gluLookAt(	GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
   	//                  GLdouble centerX, GLdouble centerY, GLdouble centerZ,
   	//                  GLdouble upX, GLdouble upY, GLdouble upZ);
    // the units below essentially looks down on a map view
    // putting the eye 50 units above the origin
    // looking at target at -10 units below the origin (looking down)
    // up vector is Y
    gluLookAt(0.0f, 50.0f, 0.0f, 0.0f, -10.0f, -5.0f, 0.0f, 1.0f, 0.0f);

    // now switch to the MODELVIEW MATRIX so that we can control (transform)
    // everything we draw (rectangles, etc.)
    glMatrixMode(GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity( );

    return 1;
}

// this is the render function used for rendering all geometry
void render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black
    glClear(GL_COLOR_BUFFER_BIT);             // GL_COLOR_BUFFER_BIT is flag
    glColor3f(1.0, 1.0, 1.0);                 // white
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ortho projection

    // rotation update
    rx += 0.1f;
    ry += 0.1f;
    rz += 0.1f;

    // Construct the matrix to apply to the first white rectangle
    mPos.identity();
  	mPos.translate(0, 0, 0);
  	glLoadMatrixf(mPos.matrix);

    // each time you apply a rotation axis, you'll need to multiply it
    mRot.rotateX(rx);
    glMultMatrixf(mRot.matrix);
    mRot.rotateY(ry);
    glMultMatrixf(mRot.matrix);
    mRot.rotateZ(rz);
    glMultMatrixf(mRot.matrix);

    // draw front and back line (don't cull back vertices)
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // draws a square 1 unit in length/width centred on the origin (0,0,0)
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube

    // glFlush empties all buffers, causing all issued commands
    // to be executed as quickly as they are accepted by the actual
    // rendering engine.
    glFlush();

    glutSwapBuffers();
    glutPostRedisplay();  // draw the window continuously
}

// Keyboard function to send to glut Keyboard function 
void keyboardFunc(unsigned char key, int x, int y) {

  // ESC key to quit
	if (key == 27) {
		exit(0);
	}

}

/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    cout<<"*********************** Begin OpenGL with GLUT ***********************"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL Hello World");

    setViewport(800, 800);

    cout<<"------- CALLBACK FUNCTION BLOCK"<<endl;
    // Callback Function Block:----------- drawing everything here START
    // basically all simulation is done here

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboardFunc);

    // Callback Function Block:----------- drawing everything here ENDS

    cout<<"------- ENTERING MAIN LOOP"<<endl;
    glutMainLoop();

   return 0;
}
