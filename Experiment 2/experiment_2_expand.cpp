#include <GLUT/glut.h>//在windows系统上运行请修改glut存储路径
#include <vector>
#include "lineClipping.cpp"
using namespace std;

rect obj;
int iKeyNum_p = 0;
int iKeyNum_c = 0;
int iPointNum = 0;
vector<point> points(100);
vector<point> point0(100);
int x1_rect=0,x2_rect=0,y1_rect=0,y2_rect=0;//矩形对角线的元素
int countp = 0,counte=0;
int x1=0,x2=0,y1=0,y2=0;//端点坐标
int winWidth = 400, winHeight = 300;
void Initial(void){
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void createrect(rect &obj){
    if(x1_rect<x2_rect){
        obj.w_xmin = x1_rect;
        obj.w_xmax = x2_rect;
    }
    else{
        obj.w_xmin = x2_rect;
        obj.w_xmax = x1_rect;
    }
    if(y1_rect<y2_rect){
        obj.w_ymin = y1_rect;
        obj.w_yman = y2_rect;
    }
    else{
        obj.w_ymin = y2_rect;
        obj.w_yman = y1_rect;
    }
}
void ChangeSize(int w,int h){
    winWidth = w;
    winHeight = h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    if (iKeyNum_c ==0) {
        glBegin(GL_LINE_STRIP);//画方框
        glVertex2i(x1_rect, y1_rect);
        glVertex2i(x2_rect, y1_rect);
        glVertex2i(x2_rect, y2_rect);
        glVertex2i(x1_rect, y2_rect);
        glVertex2i(x1_rect, y1_rect);
        glEnd();
        for(int i=0;i<countp;i++){
            glBegin(GL_LINE_STRIP);//画折线
            glVertex2i(points[i].x, points[i].y);
            glVertex2i(points[i+1].x, points[i+1].y);
            glEnd();
        }
    }
    else if(iKeyNum_c == 1){
        createrect(obj);
        for(int i=0;i<countp;i++){
            Line_Clipping_expand(points,obj,i);
        }
        glBegin(GL_LINE_STRIP);//绘制矩形
        glVertex2i(x1_rect, y1_rect);
        glVertex2i(x2_rect, y1_rect);
        glVertex2i(x2_rect, y2_rect);
        glVertex2i(x1_rect, y2_rect);
        glVertex2i(x1_rect, y1_rect);
        glEnd();
    }
    glutSwapBuffers();
}

void MousePlot(GLint button, GLint action, GLint xMouse,GLint yMouse){
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        if(iPointNum == 0 || iPointNum == 2){
            iPointNum = 1;
            x1_rect = xMouse;
            y1_rect = winHeight - yMouse;
        }
        else(iPointNum = 2);
        x2_rect = xMouse;
        y2_rect = winHeight - yMouse;
        glutPostRedisplay();
    }

}
void PassiveMouseMove(GLint xMouse,GLint yMouse){
    if(counte == 0){
        points[countp].x = xMouse;
        points[countp].y = winHeight - yMouse;
        glutPostRedisplay();
    }
    if(iPointNum == 1){
        x2_rect = xMouse;
        y2_rect = winHeight - yMouse;
        glutPostRedisplay();
    }
}
void Key(unsigned char key,GLint xMouse,GLint yMouse){
    if(key == 'p' && counte == 0) {
        points[countp].x = xMouse;
        points[countp].y = winHeight - yMouse;
        countp++;
        glutPostRedisplay();
    }
    if(key =='c'){
        iKeyNum_c += 1;
        glutPostRedisplay();
    }
    if(key == 'e'){
        counte++;
    }
}

int main(int argc,char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Clipping Expand");
    glutDisplayFunc(Display);
    glutMouseFunc(MousePlot);
    glutPassiveMotionFunc(PassiveMouseMove);//动态鼠标
    glutKeyboardFunc(Key);//键盘
    glutReshapeFunc(ChangeSize);
    Initial();
    glutMainLoop();
}

