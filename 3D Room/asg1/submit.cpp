/*****************************************************************************
        FILE : submit.c (Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID: 161810329
 		Student Name: 荀正
*****************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<windows.h>
#include<math.h>


//人物数据
GLfloat arm = 20.0;
GLfloat user_place_x = 50.0;
GLfloat user_place_z = -100;

//动画参数
int action = 0;//动作行为选择器 对应键盘和鼠标输入

//光源参数
float light_on = 1;
float material = 0.25;


//电视动画
float tv_on = 0.0;

//篮球动画
float ball_place_x = -80;
float ball_size = 1.0;
float ball_place_y = -90.0;

//移动观察者位置与角度
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

//书倒了
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
	glEnable(GL_NORMALIZE);  //自动生成单位法向
	glEnable(GL_DEPTH_TEST); //防止重叠
	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0); //启用0号光
	glEnable(GL_LIGHT1);  //启用1号灯
	glFrontFace(GL_CCW); //窗口坐标上投影多边形的顶点顺序为逆时针方向的表面为正面
	glEnable(GL_COLOR_MATERIAL); //执行后，图形（材料）将根据光线的照耀进行反射。
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	//清楚缓存
	glEnable(GL_TEXTURE_2D);    // 启用纹理
}

void display(void) // Here's Where We Do All The Drawing
{
	printf("display\n");
	if (deltaMove!=0)
		computePos(deltaMove);
	if (deltaMoveX != 0)
		computerXPlace(deltaMoveX);
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	//清楚缓存
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	// TODO:
	// Place light source here
	//太阳光
	GLfloat lightpos[] = { 0.f, 1000.f, 400.f, 0 };			// 可设动画
	GLfloat light0_mat1[] = { 0.2, 0.2, 0.2, 0.3f };
	GLfloat light0_diff[] = { 1.0, 1.0, 1.0, 0.3 };
	//灯光
	GLfloat lightpos2[] = { 0.0,96.0,-150.0,light_on }; //开灯
	GLfloat light1_mat1[] = { 0.1,0.1,0.1,0.3 };
	GLfloat light1_diff[] = { 0.1,0.1,0.1,0.3 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos); //指定光源位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1); //环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff); //漫反射光
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);  //光源位置
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1); //环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff); //漫反射光


	// TODO:
	// Draw walls and objects here
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat mat_specular[] = { 0.3,0.3,0.3,1.0 };
	GLfloat high_shininess[] = { 20.0 };
	GLfloat high_mat[] = { material,material,material,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //材质的散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //镜面反射颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);//镜面反射指数
	glMaterialfv(GL_FRONT, GL_EMISSION, high_mat);//反射光颜色


	glLoadIdentity();
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -300.0); //平移整体
	static GLfloat wall_mat[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat); //设置墙壁的环境颜色与散射颜色 材质

	//左边的墙壁
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); //设置法向量的指向
	glVertex3f(-100.0, -100.0, 0.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glEnd();

	//右边的墙壁
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0); //设置法向量的指向
	glVertex3f(100.0, -100.0, 0.0);
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(100.0, 100.0, 0.0);
	glEnd();

	//后面的墙壁
	//glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0); //设置法向量的指向
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(100.0, 100.0, -300.0);
	glEnd();

	//顶部
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, -300.0);
	glVertex3f(-100.0, 100.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glEnd();

	//地面
	glColor3f(0.5, 0.5, 0.4);
	glBegin(GL_QUADS); //四边形
	glNormal3f(0.0, 1.0, 0.0); //设置法向量的指向
	glVertex3f(100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, -300.0);
	glVertex3f(-100.0, -100.0, 200.0);
	glVertex3f(100.0, -100.0, 200.0);
	glEnd();

	//房间x为（-100，100） y（-100,100） z(-300,0) 
	//开始绘制室内物品
	//床
	//床板内部
	glPushMatrix();
	glColor3f(0.22, 0.52, 1.0);
	glTranslatef(-75.0, -70.0, -295);
	glScalef(50, 60, 10);
	glutSolidCube(1.0);
	glPopMatrix();

	//床板外部
	glPushMatrix();
	glColor3f(0.2, 0.7, 1.0);
	glTranslatef(-75.0, -85.0, -195);
	glScalef(50, 30, 10);
	glutSolidCube(1.0);
	glPopMatrix();

	//床的平面
	glPushMatrix();
	glColor3f(0.2, 0.7, 1.0);
	glTranslatef(-75.0, -68.0, -245);
	glScalef(50, 4, 110);
	glutSolidCube(1.0);
	glPopMatrix();

	//被褥
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glTranslatef(-75.0, -64.0, -245);
	glScalef(50, 4, 110);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌子腿1
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(30.0, -80.0, -265);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌子腿2
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(30.0, -80.0, -220);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌子腿3
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(80.0, -80.0, -265);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌子腿4
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(80.0, -80.0, -220);
	glScalef(4, 40, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌面
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(55, -61.0, -242.5);
	glScalef(80, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//桌上物品
	//茶壶
	glPushMatrix();
	glColor3f(0.2, 0.7, 0.5);
	glTranslatef(35, -56.0, -242.5);
	glutSolidTeapot(10.0);
	glPopMatrix();



	//电视
	glPushMatrix();
	glColor3f(0.0, 0.0, tv_on);
	glTranslatef(99, -20.0, -240);
	glScalef(2, 40, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//电视框
	//上
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, 1, -240);
	glScalef(2, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();


	//下
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -41.0, -240);
	glScalef(2, 2, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//左
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -20.0, -271);
	glScalef(2, 44, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	//右
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(99, -20.0, -209);
	glScalef(2, 44, 2);
	glutSolidCube(1.0);
	glPopMatrix();


	//椅子
	//椅子腿1
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0.0, -85.0, -260);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//椅子腿2
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0.0, -85.0, -240);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//椅子腿3
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20.0, -85.0, -260);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//椅子腿4
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20.0, -85.0, -240);
	glScalef(4, 30, 4);
	glutSolidCube(1.0);
	glPopMatrix();

	//椅子面
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-10.0, -69.0, -250);
	glScalef(24, 2, 24);
	glutSolidCube(1.0);
	glPopMatrix();

	//椅子背
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(-20, -54, -250);
	glScalef(4, 30, 24);
	glutSolidCube(1.0);
	glPopMatrix();


	//篮球
	glPushMatrix();
	glColor3f(0.88, 0.5, 0.5);
	glTranslatef(ball_place_x, ball_place_y, -100);
	glScalef(10, 10, 10);
	glutSolidSphere(ball_size, 100000, 100000);
	glPopMatrix();

	//灯 底座
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.6);
	glTranslatef(0, 98, -150);
	glScalef(40, 4, 60);
	glutSolidCube(1.0);
	glPopMatrix();

	//灯第二层
	glPushMatrix();
	glColor3f(0.0, 0.6, 0.6);
	glTranslatef(0, 96, -150);
	glScalef(30, 4, 40);
	glutSolidCube(1.0);
	glPopMatrix();

	//书架底盘
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(50, -20, -290);
	glScalef(60, 4, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	//书架左侧
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(21, -15, -290);
	glScalef(2, 10, 20);
	glutSolidCube(1.0);
	glPopMatrix();


	//书架右侧
	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(79, -15, -290);
	glScalef(2, 10, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	//书籍
	//书1
	glPushMatrix();
	glColor3f(1, 0.0, 0.0);
	glTranslatef(23, -10, -294);
	glScalef(2, 16, 12);
	glutSolidCube(1.0);
	glPopMatrix();
	//书2
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.2);
	glTranslatef(25, -10, -294);
	glScalef(2, 16, 12);
	glutSolidCube(1.0);
	glPopMatrix();
	//书3
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.0);
	glTranslatef(27, -8, -294);
	glScalef(2, 20, 12);
	glutSolidCube(1.0);
	glPopMatrix();

	//书架上的装饰品
	//底座
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(75, -20, -295);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(6, 20, 10000, 10000);
	glPopMatrix();

	//上部
	glPushMatrix();
	glColor3f(0.4, 0.5, 1.0);
	glTranslatef(75, 4, -295);
	glRotatef(book_angel, 0, 1, 0);
	glutSolidTorus(1, 4, 1000, 1000);
	glPopMatrix();


	//人
	//控制人的位置
	glPushMatrix();
	glTranslatef(user_place_x, -10.0, user_place_z);		// 可设动画
	// 胳膊
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
	// 头
	glTranslatef(0.0, -10.0, 0.0);
	glColor3f(0.9, 0.7, 0.6);
	glutSolidSphere(8.0, 50, 50);
	// 脖子
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(8.0, 10.0, 10.0);
	glutSolidCube(1.0);
	// 身体
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.125, 0.1, 0.1);
	glTranslatef(0.0, -18.0, 0.0);
	glScalef(25.0, 35.0, 15.0);
	glutSolidCube(1.0);
	// 腿
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
	printf("键盘处理事件\n");
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;
	case 'p':
		action = 1;
		printf("开灯\n");
		break;
	case'b':
		action = 2;
		printf("关灯\n");
		break;
	case 'c':
		action = 3;
		printf("开电视\n");
		break;
	case 'o':
		action = 4;
		printf("关电视\n");
		break;
	case'k':
		action = 5;
		printf("抬起胳膊");
		break;
	case'l':
		action = 6;
		printf("放下胳膊");
		break;
	case 'f':
		action = 7;
		printf("球变大");
		break;
	case'g':
		action = 8;
		printf("球变小");
		break;
	case'a':
		action = 9;
		printf("人往左");
		break;
	case'd':
		action = 10;
		printf("人往右");
		break;
	case'w':
		action = 11;
		printf("人往内");
		break;
	case's':
		action = 12;
		printf("人往外");
		break;
	case 'h':
		action = 13;
		printf("球移动");
		break;
	case 'n':
		action = 14;
		printf("旋转装饰品");
		break;
	}
}

void idle()
{
	printf("idle\n");
	switch (action)
	{
	case 1://开灯
		light_on = 1;
		material = 0.25;
		break;
	case 2://关灯
		light_on = 0;
		material = 0.0;
		break;
	case 3://开电视
		if (tv_on <= 1.0) {
			Sleep(100);
			tv_on += 0.1;
		}
		break;
	case 4://关电视
		if (tv_on > 0.0) {
			Sleep(100);
			tv_on -= 0.1;
		}
		break;
	case 5: //抬起胳膊
		if (arm <= 130.0) {
			Sleep(1);
			arm += 1;
		}
		break;
	case 6: //放下胳膊
		if (arm >= 20.0) {
			Sleep(1);
			arm -= 1;
		}
		break;
	case 7: //球变大
		if (ball_size < 1.5) {
			Sleep(100);
			ball_size += 0.1;
			ball_place_y += 1;
		}
		break; 
	case 8: //球变小
		if (ball_size > 1.0) {
			Sleep(100);
			ball_size -= 0.1;
			ball_place_y -= 1;
		}
		break;
	case 9: //人左
		user_place_x -= 2;
		action = 0;//恢复
		break;
	case 10: //人右
		user_place_x += 2;
		action = 0;//恢复
		break;
	case 11: //人往内部
		user_place_z -= 2;
		action = 0;//恢复
		break;
	case 12: //人外
		user_place_z += 2;
		action = 0;//恢复
		break;
	case 13: //球移动
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
	// 当被按下的时候记录旋转角
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

	//鼠标动作
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();
	
}