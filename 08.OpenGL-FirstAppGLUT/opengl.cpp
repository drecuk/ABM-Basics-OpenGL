//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018 | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ OpenGL Application
//	Initialise OpenGL and Setting up a Window with GLUT
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

/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    cout<<"*********************** Begin OpenGL with GLUT ***********************"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE );
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL Hello World");

    cout<<"------- CALLBACK FUNCTION BLOCK"<<endl;
    /* Callback Function Block: draw everything here, including callbacks
      // render is a method for rendering OpenGL polygons: void render() {...}
      // there should also be functions to update the scene here
      // basically all simulation is done within this block

      glutDisplayFunc(render);

      // there are others below used for managing events:
      // glutMouseFunc(...);
      // glutReshapeFunc(...);
      // glutKeyboardFunc(...);
      // glutIdleFunc(...);

    */

    // glutMainLoop enters the GLUT event processing loop.
    // This routine should be called at most once in a GLUT program.
    // Once called, this routine will never return. It will call as
    // necessary any callbacks that have been registered.
    // for each event in the queue, GLUT executes the appropriate
    // callback function if one is defined - these are in the Callback Block

    cout<<"------- ENTERING MAIN LOOP"<<endl;
    glutMainLoop();

   return 0;
}
