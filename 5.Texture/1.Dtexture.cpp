#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "gltools.h"

#define GL_PI 3.14159f

static int Widht;
static int Height;


void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glClearColor(0.4f, 0.4f, 1.0f, 1.0f );
}

// Called to draw scene
void RenderScene(void)
{
	GLfloat x,y,z, angle;

	static GLubyte image[8][4] =
	{
		{0x3f, 0x00, 0x3f, 0x80}, // Áøº¸¶ó
		{0x7f, 0x00, 0x7f, 0x80}, // º¸¶ó 
		{0xbf, 0x00, 0xbf, 0x80}, // ³²»ö 
		{0x00, 0x00, 0xff, 0x80}, // ÆÄ¶û
		{0x00, 0xff, 0x00, 0x80}, // ±×¸°
		{0xff, 0xff, 0x00, 0x80}, // ³ë¶û
		{0xff, 0x7f, 0x00, 0x80}, // ¿À·»Áö
		{0xff, 0x00, 0x00, 0x80} // »¡°­
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage1D(GL_TEXTURE_1D,0,4,8,0,GL_RGBA,GL_UNSIGNED_BYTE,image);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glDisable(GL_TEXTURE_1D);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	//glRotatef(10.0f,0.0f,1.0,0.0f);
	glTranslatef(0.0f,-40.0f,-100.0f);

	glColor3f(0.0f,0.8f,0.0f);
	glBegin(GL_POLYGON);

	for(angle = 0.0; angle < (2.0*GL_PI) ; angle += (0.03125 *GL_PI))
	{
		x = 200.0f *cos(angle);
		z = 200.0 * sin(angle);
		glVertex3f (x,0.0f,z);

	}
	glEnd();

	glEnable(GL_TEXTURE_1D);
	glBegin(GL_QUAD_STRIP);

	for( angle =0.0f; angle <= GL_PI ; angle +=(0.03125 *GL_PI))
	{
		x= 50.0f *cos(angle);
		y= 50.0f *sin(angle);
		z = -50.0f;
		glTexCoord1f(0.0f);
		glVertex3f(x,y,z);

		x= 55.0f*cos(angle);
		y= 55.0f*sin(angle);
		z= -50.0f;

		glTexCoord1f(0.7f);
		glVertex3f(x,y,z);
	}
	glEnd();

	glPopMatrix();
	glutSwapBuffers();	

}



void ChangeSize(int w, int h)
{
	GLfloat fAspect;
    
	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; // WindowÀÇ Á¾È¾ºñ °è»ê

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,500.0f); //(FOV,Á¾È¾ºñ,near,far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
}
	
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("1D texture rainbow");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}