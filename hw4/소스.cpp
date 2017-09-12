#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

GLUquadricObj *p;
void getaxis(int index);
double getcolor();
int axi[16];
double colR[16];
double colG[16];
double colB[16];
static float theta[3];
GLdouble angle;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2.0, 2.0, 0, 0, 0, 0, 1.0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position0[4] = { 100, 100, 100, 1 };
	GLfloat ambient0[4] = { 0, 0, 0.6,0 };
	GLfloat diffuse0[4] = { 1.0, 1.0, 0, 1 };
	GLfloat specular0[4] = { 1, 1, 1, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_specular[4] = { 1,1,1,1 };
	GLfloat mat_shininess = 25.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	double xp = -1.6;
	double yp = 2.4;
	int a = 0;
	int b = 0;
	
	for (int i = 0; i < 4; i++)
	{
		xp = -1.6;
		for (int k = 0; k < 4; k++)
		{
			glPushMatrix();
			glTranslatef(xp, yp, 0.0);

				if (axi[a] == 0)
					glRotatef(angle, 1, 0, 0);
				else if (axi[a] == 1)
					glRotatef(angle, 0, 1, 0);
				else
					glRotatef(angle, 0, 0, 1);
			glColor3f(colR[b], colG[b], colB[b]);
			glutSolidTeapot(0.2);
			glPopMatrix();
			a++;
			b++;
			xp = xp + 0.8;
		}
		yp = yp - 0.8;
	}
	glutSwapBuffers();
}
void getaxis(int index)
{
	if (index == 0)
		glRotatef(angle, 1, 0, 0);
	else if (index == 1)
		glRotatef(angle, 0, 1, 0);
	else
		glRotatef(angle, 0, 0, 1);
}

void rtimer(int value)
{
	angle += 2;
	glutTimerFunc(30, rtimer, 0);
	glutPostRedisplay();
}
double getcolor(void)
{
	double c;
	c= (double)rand() / RAND_MAX;
	return c;
}

void init(void)
{
	srand(time(NULL));
	theta[0] = 0;
	theta[1] = 0;
	theta[2] = 0;
	for (int t = 0; t < 16; t++)
	{
		axi[t] = rand() % 3;
		colR[t] = (double)rand() / RAND_MAX;
		colG[t] = (double)rand() / RAND_MAX;
		colB[t] = (double)rand() / RAND_MAX;
	}
}

void SetupRc(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	}
	else
	{
		glOrtho(-2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -2.0, 2.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ex4");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(30, rtimer, 1);
	init();
	SetupRc();
	glutMainLoop();
}