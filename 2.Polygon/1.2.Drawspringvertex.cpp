#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


void RenderScene(void)
{
	GLfloat x,y,z,angle;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot,1.0f,0.0f,0.0f); //(angle)
	glRotatef(yRot,0.0f,1.0f,0.0f);

	glBegin(GL_POINTS);

	z=-50.0f;

	for(angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle +=0.1f)  // 3.14/0.1 °³ÀÇ Æ÷ÀÎÆ®¸¦ »Ñ¸°´Ù ÃÑ 3¹ÙÄû 
	{
		x = 60.0f*cos(angle);
		y = 60.0f*sin(angle);

		glVertex3f(x,y,z);
		z +=0.5f;
	}
	glEnd();

	glPopMatrix();
	//glFlush();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f); 

	glColor3f(1.0f,0.0f,0.0f);
	
}


void KeyControl(int key, int x, int y) // add
{
	if(key == GLUT_KEY_UP)
		xRot -=5.0f;
	
	if(key == GLUT_KEY_DOWN)
		xRot +=5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -=5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot +=5.0f;

	glutPostRedisplay();

	
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w ,h );

	if(w<=h)
		glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange, nRange);
	else
		glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// add
	glutInitWindowPosition(0,0); // add
	glutInitWindowSize(512,512); // add
	glutCreateWindow("SpringVertex");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl); // add
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	
}
