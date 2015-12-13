//
//  Rectangle.cpp
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
    
    int w = 250;
    int h = 250;
    
    glViewport(0,0,w/2,h/2);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f,0.0f,0.0f);
    // ±◊∏≤¿ª ±◊∏± ªˆ¿ª ¡ˆ¡§
    glRectf(-10.0f,10.0f,10.0f,-10.0f);
    // ¡˜ªÁ∞¢«¸¿ª ±◊∑¡∂Û (x1,y1,x2,y2) - øﬁ¬ ªÛ¥‹ + ø¿∏•¬  «œ¥‹
    
    glViewport(w/2,h/2, w, h);
    //	glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f,0.0f,0.0f);
    // ±◊∏≤¿ª ±◊∏± ªˆ¿ª ¡ˆ¡§
    glRectf(-10.0f,10.0f,10.0f,-10.0f);
    glFlush(); // µÂ∑ŒøÏ ∏Ì∑…¿ª Ω««‡
}

// ∑ª¥ı∏µ ªÛ≈¬ º≥¡§
void SetupRC(void)
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    
}

void ChangeSize(GLsizei w, GLsizei h)
{
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w<=h)
        glOrtho(-100.0f,100.0f,-100.0f*h/w,100.0f*h/w,1.0f,-1.0f);
    // ¡æ¿« ∫Ò¿≤¿Ã ≈©π«∑Œ ¿€¿∫∞™¿ª ±‚¡ÿ¿∏∑Œ ¡æ¿« ∫Ò¿≤¿ª ∏¬√„
    else
        glOrtho(-100.0f*w/h,100.0f*w/h,-100.0f,100.0f,1.0f, -1.0f);
    // »æ¿« ∫Ò¿≤¿Ã ≈©π«∑Œ ¿€¿∫∞™(h)∏¶ ±‚¡ÿ¿∏∑Œ »æ¿« ∫Ò¿≤¿ª ∏¬√„
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // «¸∑ƒ ∫Ø»Ø¿¸ø° ¡¬«•∏¶ ¿Áº≥¡§ (
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Rectangle");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize); // RenderScene «‘ºˆ∏¶ µΩ∫«√∑π¿Ã callback «‘ºˆ∑Œ ªÁøÎ (Window drawing Ω√ «ÿ¥Á«‘ºˆ∏¶ ø¨º”¿˚¿∏∑Œ »£√‚)
    SetupRC();
    glutMainLoop();               // glut main «‘ºˆ »£√‚ (glut¿« ∏ﬁ¿Œ framework «‘ºˆ »£√‚)
    
}
















// Documentation ///////////////////////////////////////////////////////////////////////////
//point 1. glRectf(100.0f,150.0f,150.0f,100.0f); ªÁ∞¢«¸ ±◊∏Æ±‚
//point 2. glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0f,-1.0f) -> w/h ∫Ø∞Ê
//point 3. glutReshapeFunc(ChangeSize); callback «‘ºˆ (w,h) ∆ƒ∂ÛπÃ≈Õ ∏Æ≈œ