#include "./freeglut-3.2.1/include/GL/freeglut.h"
#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std;

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle Bresenham");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(x + 200, y + 300);
    glEnd();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    int x = 0;
    int r = 80;
    int y = r;
    // int transX = 200;
    // int transY = 300;
    float dp = 3 - (2 * r);
    plot(x, y);
    while (x < y) {
        if (dp >= 0) {
            x++;
            y--;
            dp += 4 * (x - y) + 10;
        }
        else {
            x++;
           
            dp += (4 * x) + 6;
        }

        plot(x, y);
        plot(x, -y);
        plot(-x, y);
        plot(-x, -y);
        plot(y, x);
        plot(-y, x);
        plot(y, -x);
        plot(-y, -x);
    }

    glEnd();

    glFlush();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
