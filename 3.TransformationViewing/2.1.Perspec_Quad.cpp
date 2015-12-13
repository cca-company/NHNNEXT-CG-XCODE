#include <math.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;


void SetupRC()
{
	// Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);  // Enable lighting

	// Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

}

void RenderScene()
{
	  float fZ,bZ;

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    fZ = 100.0f;
    bZ = -100.0f;

    // Save the matrix state and do the rotations
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f,0.0f, zDistance);

    // Set material color, Red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Front Face ///////////////////////////////////
    glBegin(GL_QUADS);
        // Pointing straight out Z
        glNormal3f(0.0f, 0.0f, 1.0f);	

        // Left Panel
        glVertex3f(-50.0f, 50.0f, fZ);
        glVertex3f(-50.0f, -50.0f, fZ);
        glVertex3f(-35.0f, -50.0f, fZ);
        glVertex3f(-35.0f,50.0f,fZ);

        // Right Panel
        glVertex3f(50.0f, 50.0f, fZ);
        glVertex3f(35.0f, 50.0f, fZ);
        glVertex3f(35.0f, -50.0f, fZ);
        glVertex3f(50.0f,-50.0f,fZ);

        // Top Panel
        glVertex3f(-35.0f, 50.0f, fZ);
        glVertex3f(-35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 50.0f,fZ);

        // Bottom Panel
        glVertex3f(-35.0f, -35.0f, fZ);
        glVertex3f(-35.0f, -50.0f, fZ);
        glVertex3f(35.0f, -50.0f, fZ);
        glVertex3f(35.0f, -35.0f,fZ);

        // Top length section ////////////////////////////
        // Normal points up Y axis
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-50.0f, 50.0f, fZ);
        glVertex3f(50.0f, 50.0f, fZ);
        glVertex3f(50.0f, 50.0f, bZ);
        glVertex3f(-50.0f,50.0f,bZ);
		
        // Bottom section
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-50.0f, -50.0f, fZ);
        glVertex3f(-50.0f, -50.0f, bZ);
        glVertex3f(50.0f, -50.0f, bZ);
        glVertex3f(50.0f, -50.0f, fZ);

        // Left section
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 50.0f, fZ);
        glVertex3f(50.0f, -50.0f, fZ);
        glVertex3f(50.0f, -50.0f, bZ);
        glVertex3f(50.0f, 50.0f, bZ);

        // Right Section
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f, 50.0f, fZ);
        glVertex3f(-50.0f, 50.0f, bZ);
        glVertex3f(-50.0f, -50.0f, bZ);
        glVertex3f(-50.0f, -50.0f, fZ);
    glEnd();

    glFrontFace(GL_CW);		// clock-wise polygons face out

    glBegin(GL_QUADS);
        // Back section
        // Pointing straight out Z
        glNormal3f(0.0f, 0.0f, -1.0f);	

        // Left Panel
        glVertex3f(-50.0f, 50.0f, bZ);
        glVertex3f(-50.0f, -50.0f, bZ);
        glVertex3f(-35.0f, -50.0f, bZ);
        glVertex3f(-35.0f,50.0f,bZ);

        // Right Panel
        glVertex3f(50.0f, 50.0f, bZ);
        glVertex3f(35.0f, 50.0f, bZ);
        glVertex3f(35.0f, -50.0f, bZ);
        glVertex3f(50.0f,-50.0f,bZ);

        // Top Panel
        glVertex3f(-35.0f, 50.0f, bZ);
        glVertex3f(-35.0f, 35.0f, bZ);
        glVertex3f(35.0f, 35.0f, bZ);
        glVertex3f(35.0f, 50.0f,bZ);

        // Bottom Panel
        glVertex3f(-35.0f, -35.0f, bZ);
        glVertex3f(-35.0f, -50.0f, bZ);
        glVertex3f(35.0f, -50.0f, bZ);
        glVertex3f(35.0f, -35.0f,bZ);
	
        // Insides /////////////////////////////
    	glColor3f(0.75f, 0.75f, 0.75f);

        // Normal points up Y axis
        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(-35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 35.0f, fZ);
        glVertex3f(35.0f, 35.0f, bZ);
        glVertex3f(-35.0f,35.0f,bZ);
		
        // Bottom section
        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(-35.0f, -35.0f, fZ);
        glVertex3f(-35.0f, -35.0f, bZ);
        glVertex3f(35.0f, -35.0f, bZ);
        glVertex3f(35.0f, -35.0f, fZ);

        // Left section
        glNormal3f(1.0f, 0.0f, 0.0f);

        glVertex3f(-35.0f, 35.0f, fZ);
        glVertex3f(-35.0f, 35.0f, bZ);
        glVertex3f(-35.0f, -35.0f, bZ);
        glVertex3f(-35.0f, -35.0f, fZ);

        // Right Section
        glNormal3f(-1.0f, 0.0f, 0.0f);

        glVertex3f(35.0f, 35.0f, fZ);
        glVertex3f(35.0f, -35.0f, fZ);
        glVertex3f(35.0f, -35.0f, bZ);
        glVertex3f(35.0f, 35.0f, bZ);
    glEnd();

    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

void ChangeSize(int w, int h)
{

	GLfloat fAspect;
	
	glViewport(0,0,w,h);

	fAspect = (GLfloat)w/(GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	gluPerspective(60.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f, -200.0f); //add

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


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,800);
	glutCreateWindow("Perpective Projection");
	
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();

}