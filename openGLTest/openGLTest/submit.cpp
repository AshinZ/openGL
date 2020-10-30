/*****************************************************************************
        FILE : submit.c (Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID: 161810329
 		Student Name: ����
*****************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<windows.h>
#include<math.h>


//��������
GLfloat arm = 20.0;
GLfloat user_place_x = 50.0;
GLfloat user_place_z = -100;

//��������
int action = 0;//������Ϊѡ���� ��Ӧ���̺��������

//��Դ����
float light_on = 1;
float material = 0.25;


//���Ӷ���
float tv_on = 0.0;

//���򶯻�
float ball_place_x = -80;
float ball_size = 1.0;
float ball_place_y = -90.0;

//�ƶ��۲���λ����Ƕ�
double deltaAngle = 0.0f;
double deltaMove = 0;
double deltaMoveX = 0;
double xOrigin = -1;
// angle of rotation for the camera direction
double angle = 0.0f;
// actual vector representing the camera's direction
double lx = 0.0f, lz = -1.0f;
// XZ position of the camera
double x = 0.0f, z = 5.0f;

//�鵹��
float book_angel = 0;

void computePos(float deltaMove) {

	x += deltaMove * lx * 10.0f;
	z += deltaMove * lz * 10.0f;
}

void computerXPlace(double deltaMoveX) {
	x += deltaMoveX * 10.0f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_NORMALIZE);  //�Զ����ɵ�λ����
	glEnable(GL_DEPTH_TEST); //��ֹ�ص�
	glEnable(GL_LIGHTING); //���ù�Դ
	glEnable(GL_LIGHT0); //����0�Ź�
	glEnable(GL_LIGHT1);  //����1�ŵ�
	glFrontFace(GL_CCW); //����������ͶӰ����εĶ���˳��Ϊ��ʱ�뷽��ı���Ϊ����
	glEnable(GL_COLOR_MATERIAL); //ִ�к�ͼ�Σ����ϣ������ݹ��ߵ���ҫ���з��䡣
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	//�������
	glEnable(GL_TEXTURE_2D);    // ��������
}

void display(void) // Here's Where We Do All The Drawing
{
	printf("display\n");
	if (deltaMove!=0)
		computePos(deltaMove);
	if (deltaMoveX != 0)
		computerXPlace(deltaMoveX);
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	//�������
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	// TODO:
	// Place light source here
	//̫����
	GLfloat lightpos[] = { 0.f, 1000.f, 400.f, 0 };			// ���趯��
	GLfloat light0_mat1[] = { 0.2, 0.2, 0.2, 0.3f };
	GLfloat light0_diff[] = { 1.0, 1.0, 1.0, 0.3 };
	//�ƹ�
	GLfloat lightpos2[] = { 0.0,96.0,-150.0,light_on }; //����
	GLfloat light1_mat1[] = { 0.1,0.1,0.1,0.3 };
	GLfloat light1_diff[] = { 0.1,0.1,0.1,0.3 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos); //ָ����Դλ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1); //������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff); //�������
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);  //��Դλ��
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1); //������
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff); //�������


	// TODO:
	// Draw walls and objects here
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat mat_specular[] = { 0.3,0.3,0.3,1.0 };
	GLfloat high_shininess[] = { 20.0 };
	GLfloat high_mat[] = { material,material,material,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //������ɫ
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //���ʵ�ɢ����ɫ
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //���淴����ɫ
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);//���淴��ָ��
	glMaterialfv(GL_FRONT, GL_EMISSION, high_mat);//�������ɫ


	glLoadIdentity();
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -300.0); //ƽ������
	static GLfloat wall_mat[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat); //����ǽ�ڵĻ�����ɫ��ɢ����ɫ ����

	//��ߵ�ǽ��
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); //���÷�������ָ��
	glVertex3f(-100.0, -100.0, 0.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glEnd();

	//�ұߵ�ǽ��
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0); //���÷�������ָ��
	glVertex3f(100.0, -100.0, 0.0);
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(100.0, 100.0, 0.0);
	glEnd();

	//�����ǽ��
	//glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); //���÷�������ָ��
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(100.0, 100.0, -300.0);
	glEnd();

	//����
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glEnd();

	//����
	glColor3f(0.5, 0.5, 0.4);
	glBegin(GL_QUADS); //�ı���
	glNormal3f(0.0, 1.0, 0.0); //���÷�������ָ��
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, 200.0);
	glVertex3f(100.0, -100.0, 200.0);
	glEnd();

	//����xΪ��-100��100�� y��-100,100�� z(-300,0) 
	//��ʼ����������Ʒ
	//��
	//�����ڲ�
	glPushMatrix();
	glColor3f(0.22, 0.52, 1.0);
	glTranslatef(-75.0, -70.0, -295);
	glScalef(50, 60, 10);
	glutSolidCube(1.0);
	glPopMatrix();

	//�����ⲿ
	glPushMatrix();
	glColor3f(0.2, 0.7, 1.0);
	glTranslatef(-75.0, -85.0, -195);
	glScalef(50, 30, 10);
	glutSolidCube(1.0);
	glPopMatrix();

	//����ƽ��
	glPushMatrix();
	glColor3f(0.2, 0.7, 1.0);
	glTranslatef(-75.0, -68.0, -245);
	glScalef(50, 4, 110);
	glutSolidCube(1.0);
	glPopMatrix();

	//����
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glTranslatef(-75.0, -64.0, -245);
	glScalef(50, 4, 110);
	glutSolidCube(1.0);
	glPopMatrix();

	//������1
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(30.0, -80.0, -265);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������2
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(30.0, -80.0, -220);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������3
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(80.0, -80.0, -265);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������4
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(80.0, -80.0, -220);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//����
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(55, -61.0, -242.5);
	glScalef(80, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//������Ʒ
	//���
	glPushMatrix();
	glColor3f(0.2, 0.7, 0.5);
	glTranslatef(35, -56.0, -242.5);
	glutSolidTeapot(10.0);
	glPopMatrix();



	//����
	glPushMatrix();
	glColor3f(0.0, 0.0, tv_on);
	glTranslatef(99, -20.0, -240);
	glScalef(2, 40, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//���ӿ�
	//��
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, 1, -240);
	glScalef(2, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();


	//��
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -41.0, -240);
	glScalef(2, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//��
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -20.0, -271);
	glScalef(2, 44, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//��
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -20.0, -209);
	glScalef(2, 44, 2);
	glutSolidCube(1.0);
	glPopMatrix();


	//����
	//������1
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0.0, -85.0, -260);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������2
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0.0, -85.0, -240);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������3
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20.0, -85.0, -260);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������4
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20.0, -85.0, -240);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//������
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-10.0, -69.0, -250);
	glScalef(24, 2, 24);
	glutSolidCube(1.0);
	glPopMatrix();

	//���ӱ�
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20, -54, -250);
	glScalef(4, 30, 24);
	glutSolidCube(1.0);
	glPopMatrix();


	//����
	glPushMatrix();
	glColor3f(0.88, 0.5, 0.5);
	glTranslatef(ball_place_x, ball_place_y, -100);
	glScalef(10, 10, 10);
	glutSolidSphere(ball_size, 100000, 100000);
	glPopMatrix();

	//�� ����
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.6);
	glTranslatef(0, 98, -150);
	glScalef(40, 4, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//�Ƶڶ���
	glPushMatrix();
	glColor3f(0.0, 0.6, 0.6);
	glTranslatef(0, 96, -150);
	glScalef(30, 4, 40);
	glutSolidCube(1.0);
	glPopMatrix();

	//��ܵ���
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(50, -20, -290);
	glScalef(60, 4, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	//������
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(21, -15, -290);
	glScalef(2, 10, 20);
	glutSolidCube(1.0);
	glPopMatrix();


	//����Ҳ�
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(79, -15, -290);
	glScalef(2, 10, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	//�鼮
	//��1
	glPushMatrix();
	glColor3f(1, 0.0, 0.0);
	glTranslatef(23, -10, -294);
	glScalef(2, 16, 12);
	glutSolidCube(1.0);
	glPopMatrix();
	//��2
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.2);
	glTranslatef(25, -10, -294);
	glScalef(2, 16, 12);
	glutSolidCube(1.0);
	glPopMatrix();
	//��3
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.0);
	glTranslatef(27, -8, -294);
	glScalef(2, 20, 12);
	glutSolidCube(1.0);
	glPopMatrix();

	//����ϵ�װ��Ʒ
	//����
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(75, -20, -295);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(6, 20, 10000, 10000);
	glPopMatrix();

	//�ϲ�
	glPushMatrix();
	glColor3f(0.4, 0.5, 1.0);
	glTranslatef(75, 4, -295);
	glRotatef(book_angel, 0, 1, 0);
	glutSolidTorus(1, 4, 1000, 1000);
	glPopMatrix();


	//��
	//�����˵�λ��
	glPushMatrix();
	glTranslatef(user_place_x, -10.0, user_place_z);		// ���趯��
	// �첲
	glColor3f(0.9, 0.7, 0.6);
	glPushMatrix();
	glTranslatef(-12.5, -25.0, 0.0);
	glRotatef(arm, 0.0, 0.0, -1.0);		// ���趯��
	glTranslatef(0.0, -15.0, 0.0);
	glScalef(5.0, 30.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(12.5, -25.0, 0.0);
	glRotatef(arm, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -15.0, 0.0);
	glScalef(5.0, 30.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();
	// ͷ
	glTranslatef(0.0, -10.0, 0.0);
	glColor3f(0.9, 0.7, 0.6);
	glutSolidSphere(8.0, 50, 50);
	// ����
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(8.0, 10.0, 10.0);
	glutSolidCube(1.0);
	// ����
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.125, 0.1, 0.1);
	glTranslatef(0.0, -18.0, 0.0);
	glScalef(25.0, 35.0, 15.0);
	glutSolidCube(1.0);
	// ��
	glColor3f(0.3, 0.3, 0.3);
	glScalef(1.0 / 25.0, 1.0 / 35.0, 1.0 / 15.0);
	glTranslatef(-9.0, -35.0, 0.0);
	glScalef(7.0, 35.0, 15.0);
	glutSolidCube(1.0);
	glScalef(1.0 / 7.0, 1.0 / 35.0, 1.0 / 15.0);
	glTranslatef(18.0, 0.0, 0.0);
	glScalef(7.0, 35.0, 15.0);
	glutSolidCube(1.0);
	glPopMatrix();



	glPopMatrix();
	glutSwapBuffers();
	glFlush();

	glutPostRedisplay();
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	if (h == 0)
		h = 1;
	printf("reshape\n");
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, w*0.85/h, 160.0f, 720.0f);
	//glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 160.0, 640.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	// TODO:
	// Add keyboard control here
	printf("���̴����¼�\n");
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;
	case 'p':
		action = 1;
		printf("����\n");
		break;
	case'b':
		action = 2;
		printf("�ص�\n");
		break;
	case 'c':
		action = 3;
		printf("������\n");
		break;
	case 'o':
		action = 4;
		printf("�ص���\n");
		break;
	case'k':
		action = 5;
		printf("̧��첲");
		break;
	case'l':
		action = 6;
		printf("���¸첲");
		break;
	case 'f':
		action = 7;
		printf("����");
		break;
	case'g':
		action = 8;
		printf("���С");
		break;
	case'a':
		action = 9;
		printf("������");
		break;
	case'd':
		action = 10;
		printf("������");
		break;
	case'w':
		action = 11;
		printf("������");
		break;
	case's':
		action = 12;
		printf("������");
		break;
	case 'h':
		action = 13;
		printf("���ƶ�");
		break;
	case 'n':
		action = 14;
		printf("��תװ��Ʒ");
		break;
	}
}

void idle()
{
	printf("idle\n");
	switch (action)
	{
	case 1://����
		light_on = 1;
		material = 0.25;
		break;
	case 2://�ص�
		light_on = 0;
		material = 0.0;
		break;
	case 3://������
		if (tv_on <= 1.0) {
			Sleep(100);
			tv_on += 0.1;
		}
		break;
	case 4://�ص���
		if (tv_on > 0.0) {
			Sleep(100);
			tv_on -= 0.1;
		}
		break;
	case 5: //̧��첲
		if (arm <= 130.0) {
			Sleep(1);
			arm += 1;
		}
		break;
	case 6: //���¸첲
		if (arm >= 20.0) {
			Sleep(1);
			arm -= 1;
		}
		break;
	case 7: //����
		if (ball_size < 1.5) {
			Sleep(100);
			ball_size += 0.1;
			ball_place_y += 1;
		}
		break; 
	case 8: //���С
		if (ball_size > 1.0) {
			Sleep(100);
			ball_size -= 0.1;
			ball_place_y -= 1;
		}
		break;
	case 9: //����
		user_place_x -= 2;
		action = 0;//�ָ�
		break;
	case 10: //����
		user_place_x += 2;
		action = 0;//�ָ�
		break;
	case 11: //�����ڲ�
		user_place_z -= 2;
		action = 0;//�ָ�
		break;
	case 12: //����
		user_place_z += 2;
		action = 0;//�ָ�
		break;
	case 13: //���ƶ�
		if (ball_place_x <-20) {
			Sleep(100);
			ball_place_x += 2;
		}
		break;
	case 14:
		if (book_angel <360) {
			Sleep(10);
			book_angel += 5;
		}
	}
}



void pressKey(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	case GLUT_KEY_LEFT: deltaMoveX = -0.5f; break;
	case GLUT_KEY_RIGHT:deltaMoveX = 0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	case GLUT_KEY_LEFT: 
	case GLUT_KEY_RIGHT:deltaMoveX = 0; break;
	}
}


void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}


void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	// �������µ�ʱ���¼��ת��
	if (xOrigin >= 0) {
		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);

	}
}

void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response 
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutSpecialFunc(pressKey);

	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	//��궯��
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();
	
}