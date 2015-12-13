#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define GL_PI 3.14159f

static  GLfloat xRot = 0.0f;
static  GLfloat yRot = 0.0f;

void SetupRC(void)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
}

void RenderScene(void)
{
	GLfloat x,y,z;
	GLfloat fSizes[2]; // add
	GLfloat fCurSize;  // add

	glClear(GL_COLOR_BUFFER_BIT);

	x = 0.0f;
	z = 0.0f;
	glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes); // 사용 가능한 두께 범위와 최소 두께를 얻는다 [0] / [1]
	fCurSize = fSizes[0];

	// add
	for(y =- 90.0f; y <= 90.0f ; y+=20.0f) 
	{
		glLineWidth(fCurSize);  // add - 선 두께를 설정
		glBegin(GL_LINES);
		glVertex3f(-80,y,z);
		glVertex3f(80,y,z);
		glEnd();
		fCurSize += 1.0f;    // 선 두께를 증가
	}

	glutSwapBuffers();

}
void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(w <= h)
		glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w, -nRange,nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange,-nRange,nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0,0);
	glutCreateWindow( "Draw Geometry_line_strip_width");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(KeyControl);
	SetupRC();
	glutMainLoop();
}