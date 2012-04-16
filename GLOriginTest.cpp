#include "GLOriginTest.h"

#include <iostream>
using namespace std;

GLOriginTest::GLOriginTest()
{
    vertexArrayID = 0;
}

GLOriginTest::~GLOriginTest()
{

}

void GLOriginTest::render()
{
    if (vertexArrayID <= 0)
    {
        setupBuffer();
    }
}

void GLOriginTest::setupBuffer()
{
    glGenVertexArrays(1, &vertexArrayID);
    cout << "vertex array id: " << vertexArrayID << endl;
    glBindVertexArray(vertexArrayID);
}