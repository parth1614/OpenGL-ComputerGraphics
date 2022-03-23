#include<GL/glut.h>
#include<iostream>

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("try");
}

void project() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 400);
}

void pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Bersenhem(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	int p;

	int x_inc = 1, y_inc = 1;

	int p_pos, p_neg;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;

	if (x2 < x1) x_inc = -1;
	if (y2 < y1) y_inc = -1;

	int x = x1, y = y1;
	if (dx < dy) {
		pixel(x, y);
		p = 2 * dx - dy;
		p_pos = 2 * (dx - dy);
		p_neg = 2 * dx;
		for (int i = 0; i < dx; i++) {
			if (p >= 0) {
				x += x_inc;
				p += p_pos;
			}
			else
				p += p_neg;
			
			y += y_inc;
			pixel(x, y);
		}
	}
	else {
		pixel(x, y);
		p = 2 * dy - dx;
		p_pos = 2 * (dy - dx);
		p_neg = 2 * dy;
		for (int i = 0; i < dy; i++) {
			if (p >= 0) {
				y += y_inc;
				
				p += p_pos;
			}
			else {
				p += p_neg;
				}
				x += x_inc;
				pixel(x, y);
			//}
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	Bersenhem(10, 10, 50, 50);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	project();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
