//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ SDL Application
//	Simulation Loop Pattern: where to put it
//  ----------------------------------------------------------
//  How to compile:
//  note that we are no longer using glut to manage our rendering
//  this gives us more control over our simulation
//  note that we are now using both SDL2 and OpenGL, thus the -l for all libraries
//  sudo g++ -I/usr/include/ <filename>.cpp -o <output file> -L/usr/lib -lSDL2 -lGL -lGLU
//
// -I define the path to the includes folder
// -L define the path to the library folder
// -l ask the compiler to use the library
//	##########################################################

/****************************** INCLUDES ******************************/
#include "OGLUtil.h"    // all OpenGL headers
#include <SDL2/SDL.h>

/****************************** PROTOTYPES ******************************/
void initOpenGL();
int setViewport( int width, int height );
void renderScene();
void DrawSquare(float xPos, float yPos, float zPos, float red, float green, float blue);

/****************************** GLOBAL VARIABLES ******************************/
SDL_Event event;                // declare an SDL event
bool isRunning;                 // main loop state

SDL_Window* displayWindow;            // pointer to the display window
SDL_Renderer* displayRenderer;        // pointer to the renderer
SDL_RendererInfo displayRendererInfo; // renderer info

// background colour starts with black
float r, g, b = 0.0f;

/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    cout<<"*********************** Begin Simulation Loop ***********************"<<endl;

    cout<<"-------- Using OpenGL 3.0 core "<<endl;
    // Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    // set states
    isRunning = true;

    // initialise SDL Video out
    cout<<"-------- Initialise SDL"<<endl;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        cout<<"Unable to initialise SDL: "<<SDL_GetError()<<endl;
        exit(1);
    }

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &displayWindow, &displayRenderer);

    SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
    // Check that we have OpenGL
    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
        /*TODO: Handle this. We have no render surface and not accelerated. */
    }

    // Sets title bar
    SDL_SetWindowTitle(displayWindow, "OpenGL and SDL");

    // init the OpenGl window
    initOpenGL();

    // setup viewport
    setViewport(800, 600);


    // --------------------- SIMULATION BLOCK
    cout<<"------- SIMULATION BLOCK STARTED"<<endl;
    // Simulation main loop is defined here
    // note that without using GLUT, we are now able to control
    // everything which runs within the loop using our own implementation

    int frameRate = 1000 / 60;
    Uint32 timeStart = SDL_GetTicks();

    while (isRunning) {
        // SDL events polling here (manage keyboard controls)
        while(SDL_PollEvent(&event) != 0)
        {
            // Close the window X
            if(event.type == SDL_QUIT)
            {
              isRunning = false;
            }
            else if ( event.type == SDL_KEYDOWN )
            {
              // if escape key is pressed
              if ( event.key.keysym.sym == SDLK_ESCAPE )
                isRunning = false;
              else if ()
            }
        }

        // The while loop runs too quickly on most systems which can hang
        // most machines. The code below keeps the update consistent
        // increase the frameRate above to slow down the simulation
        if (SDL_GetTicks() >= timeStart + frameRate)
        {
          timeStart = SDL_GetTicks();
          //cout<<"timestart:"<<timeStart<<endl;

          // ------------------ START ALL UPDATES AND RENDERING HERE

          // gradually change the background color to white
          r+=0.001f; g+=0.0001f; b+=0.00005f;
          glClearColor(r, g, b, 1.f);

          // render the scene
          renderScene();

          // Update window with OpenGL rendering
          SDL_GL_SwapWindow(displayWindow);

          // ------------------ END ALL UPDATES AND RENDERING HERE

        }
    }

    cout<<"------- SIMULATION BLOCK ENDED"<<endl;

    // clear the screen to default
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    cout<<"------- Cleaning Up Memory"<<endl;
    // all codes to clean up memory HERE


    // Destroy window
    SDL_DestroyWindow(displayWindow);
    displayRenderer = NULL;
    displayWindow = NULL;
    cout<<"------- Objects in Memory Destroyed"<<endl;

    SDL_Quit();

   return 0;
}

// A general OpenGL initialization function that sets all initial parameters
void initOpenGL()
{
  cout<<"-------- Initialise OpenGL"<<endl;
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
  glClearDepth(1.0);                      // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LEQUAL);                   // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
  glShadeModel(GL_SMOOTH);                // Enables Smooth Color Shading
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); // Nicest perspective calculations
}

// Reset our viewport after a window resize
int setViewport( int width, int height )
{
    cout<<"-------- Setting OpenGL Viewport"<<endl;
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
    gluLookAt(0.0f, 50.0f, 0.0f, 0.0f, -10.0f, -5.0f, 0.0f, 1.0f, 0.0f);

    // now switch to the MODELVIEW MATRIX so that we can control (transform)
    // everything we draw (rectangles, etc.)
    glMatrixMode(GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity( );

    return 1;
}

void renderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen | depth buffer
  glLoadIdentity();                                   // Reset the matrix

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DrawSquare(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f); // white

  //SDL_RenderPresent(displayRenderer);

  //SDL_GL_SwapWindow(displayWindow);
}

void DrawSquare(float xPos, float yPos, float zPos, float red, float green, float blue)
{
	glColor3f(red, green, blue);		// set colour to red

	//glTranslatef(xPos, yPos, zPos);
	//glPushMatrix();
	glBegin(GL_POLYGON);				// draw the square
		glVertex3f(-0.5f, 0.0f, -0.5f);	// top left
		glVertex3f(0.5f, 0.0f, -0.5f);	//	top right
		glVertex3f(0.5f, 0.0f, 0.5f);	// bottom right
		glVertex3f(-0.5f, 0.0f, 0.5f);	// bottom left
	glEnd();
	//glPopMatrix();
}
