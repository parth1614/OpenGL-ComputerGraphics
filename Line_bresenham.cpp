#include<GL/glut.h>
#include<iostream>
using namespace std;

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(x , y );
    glEnd();
}

void bres(int x, int y, int x1, int y1) {
    int dx = x1 - x;
    int dy = y1 - y;
    int xinc = 1; int yinc = 1;
    if (x > x1) {
        xinc = -1;
    }
    if (y > y1) {
        yinc = -1;
    }

    if (dx > dy) {
        int pd = 2 * dy - dx;
        plot(x, y);
        for (int i = 0; i < dy; ++i) {
            if (pd >= 0) {
                y += yinc;
                pd += 2 * (dy - dx);
            }
            else {
                pd += 2 * dy;
            }
            x += xinc;
            plot(x, y);
        }
    }
    else {
        int pd = 2 * dx - dy;
        plot(x, y);
        for (int i = 0; i < dx; ++i) {
            if (pd >= 0) {
                x += xinc;
                pd += 2 * (dx - dy);
            }
            else {
                pd += 2 * dx;
            }
            y += yinc;
            plot(x, y);
        }
    }
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    bres(20, 10, 250, 100);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
