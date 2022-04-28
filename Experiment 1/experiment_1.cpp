#include <iostream>
#include <GLUT/glut.h>//在windows系统上运行请修改glut存储路径

//
//author
//This code is finished with Macos whose document code is 'UTF-8',
//so if you find any grabled code when you open it, please change the document code from 'GB2312' or else to 'UTF-8'.
//

using namespace std;
int iPointNum = 0;
int a0=0,a1=0;
int x1=0,x2=0,y1=0,y2=0;
int x1_rect=0,x2_rect=0,y1_rect=0,y2_rect=0;
int pos_x = 0,pos_y = 0;
int judge;
int winWidth = 400, winHeight = 300;
void Initial(void){
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w,int h){
    winWidth = w;
    winHeight = h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void onMidPointEllispe(int a,int b){
    int x,y;
    float d1,d2;
    pos_x = 0.5*(x2+x1);
    pos_y = 0.5*(y2+y1);
    if(judge == 0)glTranslated(pos_x,pos_y,0);
    else if(judge == 1) glTranslated(pos_x,y1-b,0);
    glBegin(GL_POINTS);
    x=0;y=b;//起始点坐标
    d1=b*b+a*a*(-b+0.25);
    glVertex2i(x,y);
    glVertex2i(-x,-y);
    glVertex2i(-x,y);
    glVertex2i(x,-y);
    while(b*b*(x+1)<a*a*(y-0.5))
    {
        if(d1<=0){
            d1+=b*b*(2*x+3);
            x++;
        }
        else{
            d1+=b*b*(2*x+3)+a*a*(-2*y+2);
            x++; y--;
        }
        glVertex2f(x,y);
        glVertex2f(-x,-y);
        glVertex2f(-x,y);
        glVertex2f(x,-y);
    }/*while上半部分*/
    d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    while(y>0)
    {
        if(d2<=0){
            d2+=b*b*(2*x+2)+a*a*(-2*y+3);
            x++; y--;
        }
        else{
            d2+=a*a*(-2*y+3);
            y--;
        }
        glVertex2f(x,y);
        glVertex2f(-x,-y);
        glVertex2f(-x,y);
        glVertex2f(x,-y);
    }
    glEnd();
    if(judge == 0)glTranslated(-pos_x,-pos_y,0);
    else if(judge == 1) glTranslated(-pos_x,-(y1-b),0);
}
void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    if(judge == 0) {
        if (iPointNum >= 1) {
            onMidPointEllispe(abs(0.5 * (x2 - x1)), abs(0.5 * (y2 - y1)));
        }
        if (iPointNum == 1) {
            glBegin(GL_LINE_STRIP);//start to draw something
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y1);
            glEnd();
        }
    }
    else{
        if (iPointNum >= 1) {
            onMidPointEllispe(abs(0.5 * (x2 - x1)), abs(0.5 * (x2 - x1)));
        }
        if (iPointNum == 1) {
            glBegin(GL_LINE_STRIP);//start to draw something
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y1-abs((x2 - x1)));
            glVertex2i(x1, y1-abs((x2 - x1)));
            glVertex2i(x1, y1);
            glEnd();
        }
    }

    glutSwapBuffers();
}
void MousePlot(GLint button, GLint action, GLint xMouse,GLint yMouse){
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        if(iPointNum == 0 || iPointNum == 2){
            iPointNum = 1;
            x1 = xMouse;
            y1 = winHeight - yMouse;
        }
        else(iPointNum = 2);
        x2 = xMouse;
        y2 = winHeight - yMouse;
        glutPostRedisplay();
    }

}
void PassiveMouseMove(GLint xMouse,GLint yMouse){
    if(iPointNum == 1){
        x2 = xMouse;
        y2 = winHeight - yMouse;
        glutPostRedisplay();
    }
}
void ProcessMenu(int value){
    if(value == 1){
        glutMouseFunc(MousePlot);
        glutPassiveMotionFunc(PassiveMouseMove);
    }
}
void Key(unsigned char key, int i, int i1){
    if(key == 'r'){
        iPointNum = 0;
        judge = 0;
        glutPostRedisplay();
    }
    int mod = glutGetModifiers();
    if (mod == GLUT_ACTIVE_SHIFT and key == 'C') {
        judge = 1;
    }
}

int main(int argc,char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Drawing ellipse with rubber band technique");
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Ellipse",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(Key);//按shift+c画正圆，绘制完成后按下r键可以清除和重置
    Initial();
    glutMainLoop();
}

