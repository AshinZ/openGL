#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    //画分割线，分成四个视见区  
    glViewport(0, 0, 400, 400);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0);
    glVertex2f(1.0, 0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
    //定义在左下角的区域  
    glColor3f(0.0, 1.0, 0.0);
    glViewport(0, 0, 200, 200);
    glBegin(GL_LINES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义在右上角的区域  
    glColor3f(0.0, 0.0, 1.0);
    glViewport(200, 200, 400, 400);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义在左上角的区域  
    glColor3f(1.0, 0.0, 0.0);
    glViewport(0, 200, 200, 400);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    //定义在右下角  
    glColor3f(1.0, 1.0, 1.0);
    glViewport(200, 0, 400, 200);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.5, -0.5,1);
    glVertex3f(-0.5, 0.5,0.5);
    glVertex3f(0.5, 0.5,0.5);
    glVertex3f(0.5, -0.5,1);
    glVertex3f(-0.5, -0.5,-1);
    glVertex3f(-0.5, 0.5,-1);
    glVertex3f(0.5, 0.5,-1);
    glVertex3f(0.5, -0.5,-1);
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL程序");
    glutDisplayFunc(&myDisplay);
    init();
    glutMainLoop();
    return 0;
}
