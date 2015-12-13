//
//  main.cpp
//  OpenGL-1-1
//
//  Created by CHANT-MAC on 2015. 12. 11..
//  Copyright © 2015년 NHNNEXT. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>


void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void SetupRC(void)
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}