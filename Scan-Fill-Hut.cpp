#include<iostream>
#include<GL/glut.h>

int fillFlag = 0;

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("scanfill");
}

void project() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
}


void draw_pixel(int x, int y)
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Bersenhem(int x1, int y1, int x2, int y2) {
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1) incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1; y = y1;
    if (dx > dy) {
        plot(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            plot(x, y);
        }
    }
    else
    {
        plot(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            plot(x, y);
        }
    }
}

void edgedetect(float x1, float y1, float x2, float y2, int* le, int* re)
{
    float mx, x, temp;
    int i;
    if ((y2 - y1) < 0)
    {
        temp = y1; y1 = y2; y2 = temp;
        temp = x1; x1 = x2; x2 = temp;
    }
    if ((y2 - y1) != 0)
        mx = (x2 - x1) / (y2 - y1);
    else
        mx = x2 - x1;
    x = x1;
    for (i = y1; i <= y2; i++)
    {
        if (x < (float)le[i])
            le[i] = (int)x;
        if (x > (float)re[i])
            re[i] = (int)x;
        x += mx;
    }
}


void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    int le[500], re[500];
    int i, y;
    for (i = 0; i < 500; i++)
    {
        le[i] = 500;
        re[i] = 0;
    }
    edgedetect(x1, y1, x2, y2, le, re);
    edgedetect(x2, y2, x3, y3, le, re);
    edgedetect(x3, y3, x4, y4, le, re);
    edgedetect(x4, y4, x1, y1, le, re);
    for (y = 0; y < 500; y++)
    {
        for (i = (int)le[y]; i < (int)re[y]; i++)
            draw_pixel(i, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    Bersenhem(10, 10, 90, 10);
    Bersenhem(90, 10, 90, 50);
    Bersenhem(90, 50, 10, 50);
    Bersenhem(10, 50, 10, 10);

    if (fillFlag == 1)
        scanfill(10, 10, 90, 10, 90, 50, 10, 50);
    glFlush();
}


void fillMenu(int option)
{
    if (option == 1)
        fillFlag = 1;
    if (option == 2)
        fillFlag = 2;
    display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    project();
    glutDisplayFunc(display);
    glutCreateMenu(fillMenu);
    glutAddMenuEntry("Fill Polygon", 1);
    glutAddMenuEntry("Empty Polygon", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
