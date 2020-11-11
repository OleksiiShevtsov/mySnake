#include <glut.h>
#include <cstdlib>
#include <vector>

using namespace std;

int X = 30, Y = 20;
int Scale = 25;

int L = Scale * X;
int H = Scale * Y;

int dir = 4;

struct Snake {
	public:
		int x;
		int y;

		Snake(int x, int y) {
			this->x = x;
			this->y = y;
		}
};
vector <Snake> snakeVec;

struct Fruct
{
public:
	int x, y;

	void NewFruct() {
		x = rand() % X;
		y = rand() % Y;
	}

	void DrawFruct() {
		glColor3f(1.0, 0.0, 0.0);
		glRectf((x + 0.2)*Scale, (y + 0.2)*Scale, (x + 0.8)*Scale, (y + 0.8)*Scale);
	}
};

Fruct fruct;

void Tick() {
	
	int temp_x = snakeVec[snakeVec.size() - 1].x;
	int temp_y = snakeVec[snakeVec.size() - 1].y;

	if (snakeVec.size() > 1) {
		for (int i = snakeVec.size(); i > 1; --i) {
			snakeVec[i - 1].x = snakeVec[i - 2].x;
			snakeVec[i - 1].y = snakeVec[i - 2].y;
		}
	}
	
	if (dir == 0)snakeVec[0].y += 1;
	if (dir == 1)snakeVec[0].x -= 1;
	if (dir == 2)snakeVec[0].x += 1;
	if (dir == 3)snakeVec[0].y -= 1;
	
	if ((snakeVec[0].x == fruct.x) && (snakeVec[0].y == fruct.y)) {
		snakeVec.push_back(Snake(temp_x, temp_y));
		fruct.NewFruct();
	}

	if (snakeVec[0].x > X) {
		snakeVec[0].x = 0;
	}
	if (snakeVec[0].x < 0) {
		snakeVec[0].x = X;
	}
	if (snakeVec[0].y > Y) {
		snakeVec[0].y = 0;
	}
	if (snakeVec[0].y < 0) {
		snakeVec[0].y = Y;
	}

	for (int i = 1; i < snakeVec.size(); i++) {
		if ((snakeVec[0].x == snakeVec[i].x) && (snakeVec[0].y == snakeVec[i].y)) {
			snakeVec.pop_back();
		}
	}
}

void DrawFiled() {
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINES);

	for (int i = 0; i < L; i += Scale) {
		glVertex2f(i, 0);
		glVertex2f(i, H);
	}
	for (int j = 0; j < H; j += Scale) {
		glVertex2f(0, j);
		glVertex2f(L, j);
	}
	glEnd();
}

void DrawSnake() {

	glColor3f(0.4, 0.4, 0.4);
	for (int i = 1; i < snakeVec.size(); i++) {
		glRectf(snakeVec[i].x*Scale, snakeVec[i].y*Scale, (snakeVec[i].x + 0.96)*Scale, (snakeVec[i].y + 0.96)*Scale);
	}

	glColor3f(0.8, 0.7, 0.1);
	glRectf(snakeVec[0].x*Scale, snakeVec[0].y*Scale, (snakeVec[0].x + 0.96)*Scale, (snakeVec[0].y + 0.96)*Scale);
}

void MyKeyboard(unsigned char key, int a, int b) {
	
	switch (dir) {
	case 0:
		switch (key) {
		case 'a':dir = 1; break;
		case 'd':dir = 2; break;
		} break;
	case 1:
		switch (key) {
		case 'w':dir = 0; break;
		case 's':dir = 3; break;
		} break;
	case 2:
		switch (key) {
		case 'w':dir = 0; break;
		case 's':dir = 3; break;
		} break;
	case 3:
		switch (key) {
		case 'a':dir = 1; break;
		case 'd':dir = 2; break;
		} break;
	case 4:
		switch (key) {
		case 'w':dir = 0; break;
		case 'a':dir = 1; break;
		case 'd':dir = 2; break;
		case 's':dir = 3; break;
		} break;
	}
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	fruct.DrawFruct();

	DrawFiled();
	DrawSnake();
	glFlush();
}

void timer(int = 0) {

	display();
	Tick();

	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv) {

	snakeVec.push_back(Snake(X / 2, Y / 2));
	fruct.NewFruct();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(L, H);
	glutCreateWindow("Snake");
	glClearColor(0.1, 0.1, 0.1, 0.0);//çàêðàñèòü ïîëå
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, L, 0, H);

	glutTimerFunc(20, timer, 0);
	glutKeyboardFunc(MyKeyboard);
	glutDisplayFunc(display);
	glutMainLoop();
}
