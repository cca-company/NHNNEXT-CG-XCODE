#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "SOIL.h"


#define GL_PI 3.14159f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

GLfloat amb [] = { 0.3f, 0.3f, 0.3f, 1.0f};
GLfloat dif [] = { 0.8f, 0.8f, 0.8f, 1.0f}; 
GLfloat	lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f};

GLuint texID[2];

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	texID[0] = SOIL_load_OGL_texture("texture.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texID[1] = SOIL_load_OGL_texture("texture.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	for(int i =0; i<2 ; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}


}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glPushMatrix();
	glTranslatef(0.0f,5.0f, zDistance);
	glTranslatef(10.0f,-6.0f,0.0f);
	
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	

	
	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0,GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glTexEnvi(GL_TEXTURE_ENV,  GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	glColor3f(1.0f,1.0f,0.0f);
	glutSolidTeapot(5.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f,5.0f,0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTexEnvi(GL_TEXTURE_ENV,  GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glColor3f(1.0f,5.0f,0.0f);
	glutSolidTeapot(5.0f);
	//glutSolidSphere(5.0f,30,30);
	glPopMatrix();

	GLfloat fColor[4] = {1.0f,0.0f,0.0f,1.0f};

	glPushMatrix();
	glTranslatef(0.0f,-10.0f,0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR, fColor);
	glTexEnvi(GL_TEXTURE_ENV,  GL_TEXTURE_ENV_MODE,GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidTeapot(5.0f);
	//glutSolidSphere(5.0f,30,30);
	glPopMatrix();



	glDisable(GL_TEXTURE_2D);


	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key == GLUT_KEY_HOME)
		zDistance += 5.0f;

	if(key == GLUT_KEY_END)
		zDistance -= 5.0f;

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
    
	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; // Window¿« ¡æ»æ∫Ò ∞ËªÍ

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,500.0f); //(FOV,¡æ»æ∫Ò,near,far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-50.0f);
		
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2D texture - MULTI");
	glutSpecialFunc(KeyControl);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();
	
}

