#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>


#define GL_PI 3.1415f


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;		//ADD

void RenderScene()
{
	static GLfloat fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, zDistance); 
	glTranslatef(0.0f, 0.0f, -100.0f);  // z 축으로 -100만큼 이동 

	glColor3ub(255, 0,0);
	glutSolidSphere(10.0f,15,15);
	glPushMatrix();						// viewing transformation 저장 (1) 
										// (1) - z축으로 -100만큼 이동		
	
	glRotatef(fElect1, 0.0f,1.0f,0.0f); // y축 방향으로 fElect1 각만큼 회전
	glTranslatef(90.0f,0.0f,0.0f);      // 변환된 x축으로 90만큼 이동
	glColor3ub(255,255,0);
	glutSolidSphere(6.0f,15,15);        // 원 그리기
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
										// (1) - z축으로 -100만큼 이동		
	
	// 두번째 원자 그리기
	glPushMatrix();						// viewing transformation 저장 (1) 				
	glRotatef(45.0f, 0.0f,0.0f, 1.0f);  
	glRotatef(fElect1, 0.0f,1.0f,0.0f);
	glTranslatef(-70.0f, 0.0f,0.0f);
	glutSolidSphere(6.0f,15,15);
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
										// (1) - z축으로 -100만큼 이동		


	glPushMatrix();                     // viewing transformation 저장 (1) 	
	glRotatef(90.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);// 변환된 z축으로 90만큼 이동
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();						// STACK에 저장된 (1) 의 상태로 변환행렬 재설정
										// (1) - z축으로 -100만큼 이동		


	fElect1 += 10.0f;					// 회전각 증가
	if(fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers(); 
	
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

	
void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

}

void ContorolKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key == GLUT_KEY_HOME) //add
		zDistance += 5.0f;
	
	if(key == GLUT_KEY_END) //add
		zDistance -= 5.0f;

	glutPostRedisplay();
}


void ChangeSize(int w, int h)
{
	/*
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);  //add
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  //add


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

	GLfloat fAspect;

	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h; // Window의 종횡비 계산
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,fAspect,1.0f,500.0f); //(FOV,종횡비,near,far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f,0.0f, -100.0f);
	
	
}



int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Atom_Perspective");

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunc,1 );
	glutSpecialFunc(ContorolKey);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}

