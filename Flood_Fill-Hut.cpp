#include<iostream>
#include<GL/glut.h>

float intCol[3] = { 0.0, 0.0, 0.0 };
float fillCol[3] = { 0.0, 1.0, 1.0 };

int sx = 2, sy = 2;

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
void setPixel(int pointx, int pointy, float f[3])
{
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}
void getPixel(int x, int y, float pixels[3])
{
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

void floodfill4(int x, int y, float oldcolor[3], float newcolor[3]) {
    float color[3];
    getPixel(x, y, color);
    if (color[0] == oldcolor[0] && (color[1]) == oldcolor[1] && (color[2]) == oldcolor[2])
    {
        setPixel(x, y, newcolor);
        floodfill4(x + 1, y, oldcolor, newcolor);
        floodfill4(x - 1, y, oldcolor, newcolor);
        floodfill4(x, y + 1, oldcolor, newcolor);
        floodfill4(x, y - 1, oldcolor, newcolor);
    }
}
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xi = x;
        int yi = (400 - y);
        floodfill4(xi, yi, intCol, fillCol);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    Bersenhem(10, 10, 90, 10);
    Bersenhem(90, 10, 90, 50);
    Bersenhem(90, 50, 10, 50);
    Bersenhem(10, 50, 10, 10);

    Bersenhem(10, 50, 20, 75);
    Bersenhem(20, 75, 30, 50);

    Bersenhem(20, 75, 80, 75);
    Bersenhem(80, 75, 90, 50);

    Bersenhem(30, 10, 30, 50);

    glFlush();
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    project();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}
