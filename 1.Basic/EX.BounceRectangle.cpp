#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

GLfloat x1 = -100.0f;
GLfloat y1 = 100.0f; // initialize (상단 사각형)
GLfloat y2 = -50.0f; // initialize (하단 사각형)
GLsizei rsize = 50.0f;

GLfloat top_ystep = 1.0f;    // 움직이는 간격 및 방향 (1 or -1)
GLfloat bottom_ystep = 1.0f; // 움직이는 간격 및 방향 (1 or -1)

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
//  glColor3f(1.0f,0.0f,0.0f);
//  glRectf(x1,y1,x1+rsize,y1-rsize); // 첫번째 사각형
//
//  glColor3f(0.0f,1.0f,0.0f);
//  glRectf(x1+rsize, y2,x1+2*rsize, y2-rsize); // 두번째 사각형
//
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glRectf(x1+2*rsize, y1, x1+3*rsize, y1-rsize); // 세번째 사각형
//
//	glColor3f(0.0f,0.0f,0.0f);
 	glRectf(x1+3*rsize, y2, x1+4*rsize, y2-rsize); // 네번째 사각형
	
    //(-100,+100) 기준점
	// ----------------
	// | -> +
	// | -
	// |              +
	// |           - <-
	// ----------------
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x1,y1,x1+rsize,y1-rsize); // 첫번째 사각형
	glColor3f(0.0f,0.0f,0.0f);
	glRectf(x1+10, y1-10, x1+rsize-10,y1-rsize+10); // 안쪽 사각형


    glColor3f(0.0f,1.0f,0.0f);
    glRectf(x1+rsize, y2,x1+2*rsize, y2-rsize); // 두번째 사각형
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(x1+rsize+10, y2-10,x1+2*rsize-10, y2-rsize+10); // 안쪽사각형


	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(x1+2*rsize, y1, x1+3*rsize, y1-rsize); // 세번째 사각형
	glColor3f(0.0f,1.f,0.0f);
	glRectf(x1+2*rsize +10, y1-10, x1+3*rsize-10, y1-rsize+10); // 안쪽 사각형

	glColor3f(0.0f,0.0f,0.0f);
	glRectf(x1+3*rsize, y2, x1+4*rsize, y2-rsize); // 네번째 사각형
	glColor3f(1.0f,0.0f,0.0f);
	glRectf(x1+3*rsize +10, y2-10, x1+4*rsize-10, y2-rsize+10); // 안쪽 사각형

   glutSwapBuffers();
}

void TimerFunction2(int value)
{

	if( y1>window_height || y1<-window_height+rsize)
	{
		top_ystep = -top_ystep;

	}
	if( y2>window_height || y2<-window_height + rsize)
	{
		bottom_ystep = -bottom_ystep;

	}

	if(y1 >window_height)
	{
		y1 = window_height -1;
		
	}
	if(y2 >window_height)
	{
		y2 = window_height -1;
	}

	y1 += top_ystep;
	y2 += bottom_ystep;
	
	glutPostRedisplay();
	glutTimerFunc(1,TimerFunction2, 1);

}

void SetupRC(void) 
{	glClearColor(1.0f,1.0f,1.0f,1.0f);  }

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	{
		window_width = 100.0f; 
		window_height = 100.0f*h/w; 
		glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w/h; 
		window_height = 100.0f; 
		glOrtho (-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(600,600);
	glutCreateWindow("EX2_Chap1.Test"); 
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize); 
	glutTimerFunc(2000,TimerFunction2,1); 
    SetupRC();
	glutMainLoop();  	
	
}
