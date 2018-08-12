//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ OpenGL Application
//	Drawing a Rectangle with OpenGL and GLUT
//
// How to compile:
// // sudo g++ -I/usr/include <filename>.cpp -o <output file> -L/usr/lib -lGL -lGLU -lglut
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

/****************************** INCLUDES ******************************/
#include <iostream>
#include <GL/gl.h>        // OpenGL
#include <GL/freeglut.h>  // OpenGL Utility Kit
#include <GL/glu.h>       // GLU is higher level function for OpenGL
using namespace std;

// this is the render function used for rendering all geometry
void render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black
    glClear(GL_COLOR_BUFFER_BIT);             // GL_COLOR_BUFFER_BIT is flag
    glColor3f(1.0, 1.0, 1.0);                 // white
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ortho projection

    // draws a square 1 unit in length/width centred on the origin (0,0,0)
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5); // first vertex
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5); // last vertex
    glEnd();

    // glFlush empties all buffers, causing all issued commands
    // to be executed as quickly as they are accepted by the actual
    // rendering engine.
    glFlush();
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

    cout<<"------- CALLBACK FUNCTION BLOCK"<<endl;
    // Callback Function Block:----------- drawing everything here START
    // basically all simulation is done here

    glutDisplayFunc(render);

    // Callback Function Block:----------- drawing everything here ENDS

    cout<<"------- ENTERING MAIN LOOP"<<endl;
    glutMainLoop();

   return 0;
}
