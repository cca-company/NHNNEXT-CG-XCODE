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
	glRotatef(xRot,1.0f,0.0f,0.0f); 
	glRotatef(yRot,0.0f,1.0f,0.0f);
	
	glBegin(GL_LINES); //add
	z =  0.0f;

	// add - 20개의 line drawing
	for(angle =0.0f ; angle < GL_PI; angle +=(GL_PI/20.0f)) 
	{
		x = 50.0f*sin(angle);             // add - 처음 그릴 line setup
		y = 50.0f*cos(angle);

		glVertex3f(x,y,z);

		x = 50.0f*sin(angle+GL_PI);       
		y = 50.0f*cos(angle+GL_PI);

		glVertex3f(x,y,z);               

	}

	glEnd();
	

	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f); 

	glColor3f(0.0f,1.0f,0.0f);
	
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
	glutCreateWindow("DrawLine");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl); // add
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	
}
