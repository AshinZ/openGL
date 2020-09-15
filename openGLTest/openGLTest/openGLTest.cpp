#include <gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          //设置窗口背景色为白色
    glMatrixMode(GL_PROJECTION);        //指定设定投影参数
    gluOrtho2D(0.0, 200, 0.0, 150.0);            //设置投影参数
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);        //用当前背景色填充窗口
    glColor3f(0.0f, 0.0f, 0.0f);                  //设置当前的绘图颜色为黑色
    glRectf(50.0f, 100.0f, 150.0f, 50.0f);          //绘制一个矩形
    glFlush();                          //清空OpenGL命令缓冲区，执行OpenGL命令 
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //初始化窗口的显示模式
    glutInitWindowPosition(100, 100);                //设置窗口的位置
    glutInitWindowSize(400, 400);                   //设置窗口的大小
    glutCreateWindow("第一个OpenGL程序");       //创建窗口
    glutDisplayFunc(&myDisplay);                  //设置当前窗口的显示回调函数
    Initial();                                     //完成窗口初始化
    glutMainLoop();                              //启动主 GLUT事件处理循环
    return 0;
}
