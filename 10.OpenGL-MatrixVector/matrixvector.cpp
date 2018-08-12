//	##########################################################
//	By Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ OpenGL Application
//	A short introduction on how to use the Matrix4x4.h and Vector3f.h code
//
// How to compile:
// sudo g++ matrixvector.cpp -o matrixvector
//	##########################################################

/****************************** INCLUDES ******************************/
#include <iostream>
#include <GL/gl.h>        // OpenGL
#include <GL/freeglut.h>  // OpenGL Utility Kit
#include <GL/glu.h>       // GLU is higher level function for OpenGL

// OpenGL Utilities
#include "Matrix4x4.h"  // Matrix Maths Functions
#include "Vector3f.h"   // Vector Maths functions

using namespace std;


Vector3f vec;              // vector declaration


/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    cout<<"*********************** Matrix ***********************"<<endl;
    // The matrix class has:
    // void translate(float x, float y, float z)
    // void rotateX(float angle) rotateY(float angle) rotateZ(float angle)
    // Vector3f multiply(Vector3f v)
    // Matrix4x4 multiply(Matrix4x4 N)
    // void identity()
    // void zero()
    // void fillMatrix()
    // void print()
    // it also contains other operator overloading as utility

    // To use a Matrix class you declare it with
    Matrix4x4 myMatrix;

    // printing the matrix should show you the identity matrix
    cout<<"-------- Default"<<endl;
    myMatrix.print();

    // zeroing the matrix
    myMatrix.zero();
    cout<<"-------- Zeroing"<<endl;
    myMatrix.print();

    // reverting back to identity
    myMatrix.identity();
    cout<<"-------- Identity"<<endl;
    myMatrix.print();

    // translation x=2, y=3, z=4
    myMatrix.translate(2, 3, 4);
    cout<<"-------- Translation"<<endl;
    myMatrix.print();

    // rotate x 45 degree
    myMatrix.rotateX(45);
    cout<<"-------- Rotation X Axis"<<endl;
    myMatrix.print();

    // rotate x 45 degree
    myMatrix.rotateY(90);
    cout<<"-------- Rotation Y Axis"<<endl;
    myMatrix.print();

    // rotate x 45 degree
    myMatrix.rotateZ(180);
    cout<<"-------- Rotation Z Axis"<<endl;
    myMatrix.print();

    // separating translation and rotation matrix
    // and using multiply to join them together
    cout<<"-------- Seperating translation and rotation"<<endl;
    Matrix4x4 mPos;
    Matrix4x4 mRot;
    Matrix4x4 mNew;

    cout<<"-------- Translation"<<endl;
    mPos.translate(2, 3, 4);
    mPos.print();
    cout<<"-------- Rotation X Axis"<<endl;
    mRot.rotateX(45);
    mRot.print();

    cout<<"-------- Multiplying into a new Matrix"<<endl;
    mNew = mPos * mRot;
    mNew.print();

    cout<<"*********************** Vector ***********************"<<endl;
    // The vector class is used for moving an agent in
    // a direction, it is used with the Matrix class
    // The vector class has
    // float dotProduct(Vector3f v2)
    // angleDotProd(Vector3f v2)
    // magnitude()
    // distance(Vector3f v1, Vector3f v2)
    // void normalise()
    // Vector3f crossProduct(Vector3f v2)
    // and various operator overloading

    // To use a Matrix class you declare it with
    Vector3f vec1(1,1,1);
    Vector3f vec2(1,2,3);
    Vector3f vecNew;

    // printing the matrix should show you the identity matrix
    cout<<"-------- Default"<<endl;
    vec1.print();
    vec2.print();

    cout<<"-------- dotProduct"<<endl;
    float val = vec1.dotProduct(vec2);
    cout<<"val = "<<val<<endl;

    cout<<"-------- magnitude"<<endl;
    cout<<"magnitude = "<<vec2.magnitude()<<endl;

    cout<<"-------- distance"<<endl;
    cout<<"distance between vec1 and vec2 = "<<vec1.distance(vec1, vec2)<<endl;

    cout<<"-------- normalise"<<endl;
    vec2.normalise();
    vec2.print();

    cout<<"-------- cross product"<<endl;
    vecNew = vec1.crossProduct(vec2);
    vecNew.print();


   return 0;
}
