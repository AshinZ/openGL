/*****************************************************************************
FILE : submit.c (Assignment 1)
NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
Student Information
Student ID: 161620222
Student Name: 刘鸿搏
*****************************************************************************/

#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include <GL/glut.h>
#include<math.h>
const GLdouble FRUSTDIM = 100.0f; //大小
//参数 用来进行动画绘制
GLfloat door = 0.0;  
GLfloat sticker = 45.0;
GLfloat screen = 0.0;
GLfloat arm = 20.0;
GLfloat xiaom = -60.0;
//动画的选项
int option = 0;
int doorOpen = 0;
float l1 = 0.25;
float ll = 1.0;

#define PI 3.1415926535
static int du = 90, OriX = -1, OriY = -1;   //du是视点和x轴的夹角
static float r = 1.5, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数

void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//glEnable 启用功能
	// 不加此项会出现放大后物体变暗问题
	glEnable(GL_DEPTH_TEST);//检查是否存在两个物体在一个像素
	glEnable(GL_LIGHTING); //启用灯源
	glEnable(GL_LIGHT0); //启用0号灯
	glEnable(GL_LIGHT1);  //启用1号灯
	glFrontFace(GL_CCW); //窗口坐标上投影多边形的顶点顺序为逆时针方向的表面为正面
	glEnable(GL_COLOR_MATERIAL); //执行后，图形（材料）将根据光线的照耀进行反射。
}

void display(void) // Here's Where We Do All The Drawing
{
	glPushMatrix(); //保存当前状态
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	//清楚缓存
	//必须放在display中否则动画会有bug
	// Place light source here
	GLfloat lightpos[] = { 0.f, 100.f, -450.f, ll };			// 可设动画
	GLfloat light0_mat1[] = { 0.2, 0.2, 0.2, 0.3f };
	GLfloat light0_diff[] = { 1.0, 1.0, 1.0, 0.3 };
	GLfloat lightpos2[] = { 0.0,0.0,0.0,ll };
	GLfloat light1_mat1[] = { 0.1,0.1,0.1,0.3 };
	GLfloat light1_diff[] = { 0.1,0.1,0.1,0.3 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos); //指定光源位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1); //环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff); //漫反射光
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);  //光源位置
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1); //环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff); //漫反射光

	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat mat_specular[] = { 0.3,0.3,0.3,1.0 };
	GLfloat high_shininess[] = { 20.0 };
	GLfloat high_mat[] = { l1,l1,l1,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //材质的散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //镜面反射颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);//镜面反射指数
	glMaterialfv(GL_FRONT, GL_EMISSION, high_mat);//反射光颜色

	glTranslatef(0.0, 0.0, -300.0); //平移
	// TODO:
	// Draw walls and objects here
	glPushMatrix();
	static GLfloat wall_mat[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat); //设置墙壁的环境颜色与散射颜色 材质

	// back wall
	glColor3f(0.5, 0.6, 0.6);
	glBegin(GL_QUADS); //四边形
	glNormal3f(0.0, 0.0, 1.0); //设置法向量的指向
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(100.0, -100.0, -300.0);
	glEnd();

	// bottom wall
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(100.0, -100.0, 0.0);
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, 0.0);
	glEnd();

	// top wall
	glColor3f(0.7, 0.7, 0.9);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(100.0, 100.0, -300.0);
	glEnd();

	// left wall
	glColor3f(0.5, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(-100.0, -100.0, 0.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glEnd();

	// right wall
	glColor3f(0.5, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(100.0, -100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(100.0, -100.0, -300.0);
	glEnd();

	// bed
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.5);
	glTranslatef(-65.0, 20.0, -175.0);
	glScalef(3.5, 1.0, 12.5);//缩放函数
	glutSolidCube(20.0); //绘制实心立方体
	glPopMatrix();

	// wardrobe
	glPushMatrix();
	glColor3f(0.6, 0.4, 0.2);
	glTranslatef(-65.0, -45.0, -175.0);
	glScalef(14.0, 22.0, 50.0);
	glutSolidCube(5.0);
	glPopMatrix();

	// mirror
	glPushMatrix();
	glTranslatef(-65.0, -45.0, -49.0);
	glColor3f(0.79, 0.82, 0.98);
	glScalef(60.0, 100.0, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// xiaoming
	glPushMatrix();
	glTranslatef(xiaom, -10.0, -30.0);		// 可设动画
	// arms
	glColor3f(0.9, 0.7, 0.6);
	glPushMatrix();
	glTranslatef(-12.5, -25.0, 0.0);
	glRotatef(arm, 0.0, 0.0, -1.0);		// 可设动画
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
	// head
	glTranslatef(0.0, -10.0, 0.0);
	glColor3f(0.9, 0.7, 0.6);
	glutSolidSphere(8.0, 50, 50);
	// neck
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(8.0, 10.0, 10.0);
	glutSolidCube(1.0);
	// body
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.125, 0.1, 0.1);
	glTranslatef(0.0, -18.0, 0.0);
	glScalef(25.0, 35.0, 15.0);
	glutSolidCube(1.0);
	// legs
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

	// stairs
	glPushMatrix();
	glTranslatef(-30.0, -100.0, -275.0);
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(65.0, 13.0, -13.0);
	glScalef(65.0, 13.0, 13.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(54.0, 39.0, -13.0);
	glScalef(54.0, 13.0, 13.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(43.0, 65.0, -13.0);
	glScalef(43.0, 13.0, 13.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(32.0, 91.0, -13.0);
	glScalef(32.0, 13.0, 13.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(21.0, 117.0, -13.0);
	glScalef(21.0, 13.0, 13.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glPopMatrix();

	// top light
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.5);
	glTranslatef(0.0, 94.0, -150.0);
	glScalef(80.0, 4.0, 80.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.6, 0.5, 0.5);
	glTranslatef(0.0, 99.0, -150.0);
	glScalef(100.0, 2.0, 100.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// door
	glPushMatrix();
	// door blanket
	glPushMatrix();
	glColor3f(0.4, 0.12, 0.5);
	glTranslatef(75.0, -99.9, -40.0);
	glBegin(GL_QUADS);
	glVertex3f(25.0, 0.0, 35.0);
	glVertex3f(25.0, 0.0, -35.0);
	glVertex3f(-25.0, 0.0, -35.0);
	glVertex3f(-25.0, 0.0, 35.0);
	glEnd();
	glPopMatrix();
	// outdoor
	glTranslatef(99.9, -50.0, -40.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(0.0, -50.0, 35.0);
	glVertex3f(0.0, 50.0, 35.0);
	glVertex3f(0.0, 50.0, -35.0);
	glVertex3f(0.0, -50.0, -35.0);
	glEnd();
	// the door
	glColor3f(0.8, 0.6, 0.4);
	glTranslatef(0.0, 0.0, -35.0);
	glRotatef(door, 0.0, -1.0, 0.0);			// 可设动画
	glTranslatef(0.0, 0.0, 35.0);
	glScalef(6.0, 100.0, 70.0);
	glutSolidCube(1.0);
	// cat eye
	glScalef(1.0 / 6.0, 0.01, 1.0 / 70.0);
	glTranslatef(4.0, 30.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	glutSolidSphere(1.0, 10, 10);

	glTranslatef(-8.0, 0.0, 0.0);
	glutSolidSphere(1.0, 10, 10);
	glTranslatef(12.0, 0.0, 0.0);

	// door sticker
	glTranslatef(-4.5, -35.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(sticker, 1.0, 0.0, 0.0);		// 可设动画
	glBegin(GL_QUADS);
	glVertex3f(0.0, 15.0, 15.0);
	glVertex3f(0.0, 15.0, -15.0);
	glVertex3f(0.0, -15.0, -15.0);
	glVertex3f(0.0, -15.0, 15.0);
	glEnd();
	glPopMatrix();

	// desk & computer & seat & teapot
	glPushMatrix();
	// desk
	glColor3f(0.22, 0.52, 1.0);
	glTranslatef(20.0, -50.0, -225.0);
	glScalef(80.0, 4.0, 50.0);
	glutSolidCube(1.0);
	glScalef(1.0 / 60.0, 0.25, 0.02);
	// computer
	glTranslatef(-5.0, 2.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glScalef(40.0, 2.0, 30.0);
	glutSolidCube(1.0);
	glScalef(1.0 / 40.0, 0.5, 1.0 / 30.0);
	glTranslatef(0.0, 15.0, -20.0);
	glScalef(40.0, 30.0, 2.0);
	glColor3f(0.0, 0.0, screen);			// 可设特效
	glutSolidCube(1.0);
	glScalef(1.0 / 40.0, 1.0 / 30.0, 0.5);
	// teapot
	glTranslatef(27.0, -10.0, 20.0);
	glColor3f(0.5, 0.3, 0.1);
	glutSolidTeapot(5.0);
	// seat
	glTranslatef(-27.0, -50.0, 60.0);
	glColor3f(1.0, 0.5, 0.13);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj* g_text;
	g_text = gluNewQuadric();
	gluCylinder(g_text, 10.0, 10.0, 30.0, 50, 4);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 30.0, 0.0);
	glScalef(35.0, 5.0, 35.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// TODO:
	// Add animation here
	//glLoadIdentity();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //视口大小
	glMatrixMode(GL_PROJECTION); //投影变换
	glLoadIdentity(); //单位矩阵
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 300., 800.);//透视方式
	glMatrixMode(GL_MODELVIEW); //模型视图
	glLoadIdentity(); //单位矩阵
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;

		// TODO:
		// Add keyboard control here
	case'1':
		printf("computer power on\n");
		option = 1;
		break;
	case'2':
		printf("computer power off\n");
		option = 2;
		break;
	case'3':
		printf("xiaoming hands up\n");
		option = 3;
		break;
	case'4':
		printf("xiaoming hands down\n");
		option = 4;
		break;
	case'5':
		printf("xiaoming walk left\n");
		option = 5;
		break;
	case'6':
		printf("xiaoming walk right\n");
		option = 6;
		break;
	case'7':
		printf("open the door");
		option = 7;
		break;
	case'8':
		printf("close the door\n");
		option = 8;
		break;
	case'9':
		printf("turn on the light\n");
		option = 9;
		break;
	case'0':
		printf("turn off the light\n");
		option = 10;
		break;
	default:
		printf("error\n");
	}
}

void idle()
{
	if (option == 1) {
		if (screen <= 1.0) {
			Sleep(100);
			screen += 0.1;
		}
	}
	if (option == 2) {
		if (screen >= 0.0) {
			Sleep(100);
			screen -= 0.1;
		}
	}
	if (option == 3) {
		if (arm <= 130.0) {
			Sleep(5);
			arm += 1;
		}
	}
	if (option == 4) {
		if (arm >= 20.0) {
			Sleep(5);
			arm -= 1;
		}
	}
	if (option == 5) {
		if (xiaom >= -60.0) {
			if (doorOpen == 1) {
				Sleep(5);
				xiaom -= 1;
			}
		}
	}
	if (option == 6) {
		if (doorOpen == 1) {
			if (xiaom <= 150.0) {
				Sleep(5);
				xiaom += 1;
			}
		}
		else {
			if (xiaom <= 15.0) {
				Sleep(5);
				xiaom += 1;
			}
		}
	}
	if (option == 7) {
		doorOpen = 1;
		if (door <= 90.0) {
			Sleep(5);
			door += 1;
		}
	}
	if (option == 8) {
		doorOpen = 0;
		if (door >= 0.0) {
			Sleep(5);
			door -= 1;
		}
	}
	if (option == 9) {
		l1 = 0.25;
		ll = 1.0;
	}
	if (option == 10) {
		l1 = 0.0;
		ll = 0.0;
	}
	glutPostRedisplay();
}


void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)  //记录鼠标按下位置
		OriX = x, OriY = y;
}

void onMouseMove(int x, int y)   //处理鼠标拖动
{
	du += x - OriX; //鼠标在窗口x轴方向上的增量加到视点与x轴的夹角上，就可以左右转
	h += 0.03 * (y - OriY);  //鼠标在窗口y轴方向上的改变加到视点y的坐标上，就可以上下转
	if (h > 1.0)   h = 1.0;  //对视点y坐标作一些限制，不会使视点太奇怪
	else if (h < -1.0) h = -1.0;
	OriX = x, OriY = y;  //将此时的坐标作为旧值，为下一次计算增量做准备
}

void main(int argc, char** argv)
{
	/*Initialization of GLUT Library */
	glutInit(&argc, argv); //初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //设置显示模式
	// 颜色模式 双缓冲模式  

	/*Create a window with title specified */
	glutInitWindowSize(600, 600); //窗口大小
	glutInitWindowPosition(100, 100); //窗口位于屏幕的位置
	glutCreateWindow("Assignment 1");	//标题
	// 修改bug，createWindow前应设置好窗口大小和位置

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape); //重新绘制函数
	glutDisplayFunc(display); //展示
	glutKeyboardFunc(keyboard); //事件处理 得到option
	glutIdleFunc(idle); //处理option
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop(); //进入事件循环
}