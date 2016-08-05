#include "RoamingScenceManager.h"

#include <glm/gtx/rotate_vector.hpp>
#include"Dependencies/glew/glew.h"
#include"Dependencies/Freeglut/freeglut.h"
RoamingScenceManager::RoamingScenceManager()
{
	OldMouse = new glm::vec3();
	Mouse = new glm::vec3();

	NewEye = new glm::vec3(0, 0, 100);
	NewUp = new glm::vec3(0, 1, 0);
	NewView = new glm::vec3(0, 0, 0);

	AuxY = new glm::vec3(0, 1, 0);
	AuxZ = new glm::vec3();
	*AuxZ = *NewEye - *NewView;
	AuxX = new glm::vec3();

	*AuxX = glm::cross(*AuxY, *AuxZ);
	*AuxX=glm::normalize(*AuxX);

	TempTranslateVec = new glm::vec3(0, 0, 0);
	TempscaleFactor = 1;
}

RoamingScenceManager::~RoamingScenceManager()
{
	delete OldMouse;
	delete Mouse;
	delete NewEye;
	delete NewUp;
	delete NewView;
	delete AuxX;
	delete AuxY;
	delete AuxZ;
	delete TempTranslateVec;
}

void RoamingScenceManager::init()
{
	init_CoordinaryDisplayList();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.156, 0.156, 0.168, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2);
}

void RoamingScenceManager::render()
{
	glClearColor(0.156, 0.156, 0.168, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*NewView = -glm::vec3(*NewView);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(TempTranslateVec->x, TempTranslateVec->y, TempTranslateVec->z);

	glScalef(TempscaleFactor, TempscaleFactor, TempscaleFactor);
	gluLookAt(NewEye->x, NewEye->y, NewEye->z,
		NewView->x, NewView->y, NewView->z,
		NewUp->x, NewUp->y, NewUp->z);
	glColor3f(1, 0, 0);
// 	glutWireCube(250);
	glCallList(ID_COORDINATY);

#if ENABLE_LIGHTING
	GLfloat light_z = -50.0f;
	GLfloat light0_ambient[] = { 1.0f, 1.0f , 1.0f , 1.0f };
	GLfloat light0_diffuse[] = { 1.0f , 1.0f , 1.0f , 1.0 };
	GLfloat light0_specular[] = { 0.43f , 0.3f , 0.4f , 1.0 };
	GLfloat light0_position[] = { 0.0f , 0.0f , light_z , -1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glPushMatrix;
	glTranslatef(light0_position[0], light0_position[1], -light0_position[2]);
	glColor3f(1, 0, 0);
	glutSolidSphere(2, 180, 190);
	glPopMatrix;
#endif
	glPushMatrix();
	//	glLoadIdentity;
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(90.f, 0.f, 1.f, 0.f);
	// 	glRotatef(180.f, 0.f, 1.f, 0.f);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}

void RoamingScenceManager::executeRotateOperation(int x, int y)
{


	Mouse->x = x;
	Mouse->y = y;


	glm::vec3 MouseTrace = *AuxY*(OldMouse->y - Mouse->y) + *AuxX*(Mouse->x - OldMouse->x);
	glm::vec3 RotateAsix = glm::cross(MouseTrace, *AuxZ);
	RotateAsix = glm::normalize(RotateAsix);

	float angle = glm::length(MouseTrace);
	*NewEye = glm::rotate(*NewEye, glm::radians(angle), RotateAsix);
	*NewUp = glm::rotate(*NewUp, glm::radians(angle), RotateAsix);

	*NewUp=glm::normalize(*NewUp);
	*AuxY = *NewUp;
	*AuxZ = *NewEye - *NewView;
	*AuxX = glm::cross(*AuxY, *AuxZ);
	//更新鼠标
	*AuxX = glm::normalize(*AuxX);

	*OldMouse = *Mouse;
}

void RoamingScenceManager::executeScaleOperation(float factor)
{
	if (TempscaleFactor <= 0)
	{
		TempscaleFactor = 0.1f;
	}
	else
	{
		TempscaleFactor += factor;
	}
}

void RoamingScenceManager::executeTranslateOperation(int x, int y)
{
	Mouse->x = x;
	Mouse->y = y;

	glm::vec3 vec(-OldMouse->x + Mouse->x, -Mouse->y + OldMouse->y, 0);
	*TempTranslateVec = *TempTranslateVec + vec;
	*OldMouse = *Mouse;
}

void RoamingScenceManager::getInitPos(int x, int y)
{
	Mouse->x = x;
	Mouse->y = y;
	*OldMouse = *Mouse;
}

void RoamingScenceManager::init_CoordinaryDisplayList()
{
	ID_COORDINATY = glGenLists(1);
	glNewList(ID_COORDINATY, GL_COMPILE);
	/*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
	int length = 50;
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(length, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, length, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, length);
	glEnd();

	glLineWidth(1);
	glEnd();
	glEndList();
}