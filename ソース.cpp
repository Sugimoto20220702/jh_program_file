/*���̃v���O������2021�N��8���ɍs��ꂽ�I�[�v���L�����p�X��
�@�i�r�Q�[�V�����V�X�e���̊ȒP��d�g�݂Ƃ������̂�������邽�߂�
 �@�쐬�����f���p�̃v���O�����ł�*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>
#include<GL/glut.h> // Open GL�ŕ`�悷�邽�߂̃w�b�_�[�t�@�C���̃C���X�g�[��

#define WIDTH 640
#define HEIGHT 640


int nPoint = 14;
double x[20], y[20]; //�n�_��x���W�Ay���W�̒l������z��B�Ƃ肠����20��
double a[100], b[100]; //�n�_�Ԃ̐����\���p�z��
double nx[20], ny[20]; //���ɒn�_������ꍇ�Ɏg���z��
int xnum, ynum; //traffic jam�ł̐��ς���p
int sp = 0;/* �o���n�̒n�_�ԍ� */
int spp = 0;  //���ݒn�̕ۑ��p
int dp = 13;/* �ړI�n�̒n�_�ԍ� */
int road[20];  //�ړ��o�H�ۑ��p
int nroad = 1;

int Distance[14][14] = { //�����̃}�b�v�p�z��@-1���ƒ��_�Ԃɕӂ��Ȃ����Ƃ�\��
	 {0,2,8,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},  //0
	 {2,0,-1,-1,5,3,-1,-1,-1,-1,-1,-1,-1,-1},  //1
	 {8,-1,0,-1,-1,2,3,-1,-1,-1,-1,-1,-1,-1},  //2
	 {4,-1,-1,0,-1,-1,8,7,-1,-1,-1,-1,-1,-1},  //3
	 {-1,5,-1,-1,0,3,-1,-1,4,-1,-1,-1,-1,-1},  //4
	 {-1,3,2,-1,3,0,-1,-1,-1,9,-1,-1,-1,-1},   //5
	 {-1,-1,3,8,-1,-1,0,3,-1,3,-1,-1,-1,-1},   //6
	 {-1,-1,-1,7,-1,-1,3,0,-1,-1,3,-1,-1,-1},  //7
	 {-1,-1,-1,-1,4,-1,-1,-1,0,3,-1,7,-1,-1},  //8
	 {-1,-1,-1,-1,-1,9,3,-1,3,0,-1,3,5,-1},    //9
	 {-1,-1,-1,-1,-1,-1,-1,3,-1,-1,0,-1,8,-1}, //10
	 {-1,-1,-1,-1,-1,-1,-1,-1,7,3,-1,0,-1,6},  //11
	 {-1,-1,-1,-1,-1,-1,-1,-1,-1,5,8,-1,0,5},  //12
	 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,5,0}, //13
};
int Distance2[14][14] = { //�������㏑���p
	 {0,2,8,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},  //0
	 {2,0,-1,-1,5,3,-1,-1,-1,-1,-1,-1,-1,-1},  //1
	 {8,-1,0,-1,-1,2,3,-1,-1,-1,-1,-1,-1,-1},  //2
	 {4,-1,-1,0,-1,-1,8,7,-1,-1,-1,-1,-1,-1},  //3
	 {-1,5,-1,-1,0,3,-1,-1,4,-1,-1,-1,-1,-1},  //4
	 {-1,3,2,-1,3,0,-1,-1,-1,9,-1,-1,-1,-1},   //5
	 {-1,-1,3,8,-1,-1,0,3,-1,3,-1,-1,-1,-1},   //6
	 {-1,-1,-1,7,-1,-1,3,0,-1,-1,3,-1,-1,-1},  //7
	 {-1,-1,-1,-1,4,-1,-1,-1,0,3,-1,7,-1,-1},  //8
	 {-1,-1,-1,-1,-1,9,3,-1,3,0,-1,3,5,-1},    //9
	 {-1,-1,-1,-1,-1,-1,-1,3,-1,-1,0,-1,8,-1}, //10
	 {-1,-1,-1,-1,-1,-1,-1,-1,7,3,-1,0,-1,6},  //11
	 {-1,-1,-1,-1,-1,-1,-1,-1,-1,5,8,-1,0,5},  //12
	 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,5,0}, //13
};

void render_string(float x, float y, const char* string)
{
	float z = -1.0f;
	glRasterPos3f(x, y, z);
	char* p = (char*)string;
	while (*p != '\0') glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p++);
}
void drawCircle(double x, double y, double radius)
{
	int i; double PI = 3.14159; int CIRCLE_RES = 60;
	glBegin(GL_POLYGON);
	for (i = 0; i < CIRCLE_RES; i++)
		glVertex2f(x + radius * cos((2. * PI * i) / CIRCLE_RES),
			y + radius * sin((2. * PI * i) / CIRCLE_RES));
	glEnd();
}
void accident() //����
{
	int num1, num2;
	
	for (;;) {
		num1 = (int)(rand() % 14);
		num2 = (int)(rand() % 14);
		if (num1 != num2)
			if ((num1 != 12 && num2 != 13) || (num1 != 13 && num2 != 12)) {// ��΂ɃS�[���ւ̓����Ȃ��Ȃ�Ȃ��悤�ɂ��邽�߂̏�����
				if (Distance[num1][num2] != -1) {
					break;
				}
			}
	}
	if (Distance[6][9] != -1) {
		num1 = 6;
		num2 = 9;
	}
	
	printf("���̂��������C�n�_%d�ƒn�_%d�Ԃ̓����ʂ�Ȃ��Ȃ�܂����B\n", num1, num2);
	Distance[num1][num2] = -1;
	Distance[num2][num1] = -1;
}
void Traffic_jam() //�a��
{

	int num1, num2;

	for (;;) {
		num1 = (int)(rand() % 14);
		num2 = (int)(rand() % 14);
		if (num1 != num2)
			if (Distance[num1][num2] != -1) {
				break;
			}
			
	}
	if (Distance[9][11] < 5) {
		num1 = 9;
		num2 = 11;
	}

	printf("�a�؂��������C�n�_%d�ƒn�_%d�Ԃ̓��ł����鎞�Ԃ�2�{�ɂȂ�܂����B\n", num1, num2);
	Distance[num1][num2] = Distance[num1][num2] * 2;
	Distance[num2][num1] = Distance[num2][num1] * 2;

	xnum = num1;
	ynum = num2;
}
void dijkstra()
{
	printf("���ݒn�̒n�_�ԍ� ==> %d\n",sp);
	printf("�ړI�n�̒n�_�ԍ� ==> %d\n",dp);

	/* �o�͕ϐ�sRoute��sDist���` */
	int sRoute[14];/* �o���n����ړI�n�܂ł̍ŒZ�o�H��̒n�_�̒n�_�ԍ���ړI�n����o���n�̏��ɐݒ肷��1�����z�� */
	int sDist;/* �o���n����ړI�n�܂ł̍ŒZ���� */

	/* ���̑��g���ϐ� */
	int pDist[14];/* �o���n����e�n�_�܂ł̍ŒZ������ݒ肷��z�� */
	int pRoute[14];
	bool pFixed[14];/* �o���n����e�n�_�܂ł̍ŒZ�������m�肵�Ă��邩�ǂ��������ʂ��邽�߂̔z�� */
	int sPoint, i, j, newDist;
	int num1, num2;

	sDist = 99999; /* �o���n����ړI�n�܂ł̍ŒZ�����ɏ����l���i�[����i�ύX���Ȃ��Ă悢�j */

	for (i = 0; i < nPoint; i++) {
		sRoute[i] = -1; /* �ŒZ�o�H��̒n�_�̒n�_�ԍ��ɏ����l���i�[���� */
		pDist[i] = 99999; /* �o���n����e�n�_�܂ł̍ŒZ�����ɏ����l���i�[���� */
		pFixed[i] = false; /* �e�n�_�̍ŒZ�����̊m���Ԃɏ����l���i�[���� */
	}
	pDist[sp] = 0;/* �o���n����o���n���̂ւ̍ŒZ������0��ݒ肷�� */
	while (true) { /* �ŒZ�o�H�T������ */
		i = 0;
		while (i < nPoint) {/* ���m��̒n�_��1�T�� */
			if (pFixed[i] == 0) {
				break; /* �ē����̌J��Ԃ����甲���� */
			}
			i = i + 1;
		}

		if (i == nPoint) { /* �o���n����S�Ă̒n�_�܂ł̍ŒZ�o�H���m�肵�Ă���� */
			break; /* �ŒZ�o�H�T�������𔲂��� */
		}

		for (j = i + 1; j < nPoint; j++) { /* �ŒZ���������Z���n�_��T�� */
			if ((pFixed[j] == 0) && (pDist[j] < pDist[i])) {
				i = j;
			}
		}
		sPoint = i;
		pFixed[sPoint] = true; /* �o���n����̍ŒZ�������m�肷�� */
		
		for (j = 0; j < nPoint; j++) {
			if ((Distance[sPoint][j] > 0) && (pFixed[j] == 0)) {
				newDist = pDist[sPoint] + Distance[sPoint][j];
				if (newDist < pDist[j]) {
					pDist[j] = newDist;
					pRoute[j] = sPoint;
				}
			}
		}

	}
	sDist = pDist[dp];
	j = 0;
	i = dp;
	while (i != sp) {
		sRoute[j] = i;
		i = pRoute[i];
		j = j + 1;
	}
	sRoute[j] = sp;
	spp = sp;
	sp = sRoute[j - 1];
	/* �o�͒l�\�� */
	printf("���ݒn����ړI�n�܂ł̍ŒZ�o�H\n");
	for (i = j; i >= 0; i--) {
		printf("%d,", sRoute[i]);
	}
	printf("\n���ݒn����ړI�n�܂ł̍ŒZ���� = %d\n\n", sDist);
	road[nroad] = sp;
	nroad += 1;
	if (spp == 13) {
		printf("�ʂ����o�H�@==> 0,");
		for (i = 1; i < nroad - 1; i++) {
			printf(" %d,", road[i]);
		}
		printf("\n\n");
	}
}
void mouse(int button, int state, int X, int Y)
{
	int i, j;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (Y >=480) {
			
			
			if (X <= 160) { // ������
				printf("�����ʒu�ɖ߂�܂����B\n");
				sp = 0;
				spp = 0;
				nroad = 1;
				xnum = 0; ynum = 0;
				for (i = 0; i < 14; i++) {
					for (j = 0; j < 14; j++) {
						Distance[i][j] = Distance2[i][j];
					}
				}	
			}
			else if (X <= 320 && X > 160) { //�@��i��
				if (spp != 13) {
					xnum = 0; ynum = 0;
					printf("���̈ʒu�ɐi�݂܂����B\n");
					dijkstra();
				}
			}
			else if (X <= 480 && X > 320) { //�@���̔���
				if (spp != 13) {
					xnum = 0; ynum = 0;
					accident();
					dijkstra();
				}
			}
			else if (X > 480) { //�@�a�ؔ���
				if (spp != 13) {
					xnum = 0; ynum = 0;
					Traffic_jam();
					dijkstra();
				}
			}
			glutPostRedisplay();  // �R�[���o�b�N�֐�display()���Ăяo��
		}
		
	}
}
void display(void)
{
	if (sp == 0) {
		dijkstra();
	}
	int i, j, k, m;
	char str[256];
	double r = 0.75;
	glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
	glClearColor(1.0, 1.0, 1.0, 1.0); // �w�i�F�̎w��

	x[0] = -9.0; y[0] = 2.0; // ���W�̎w��B
	x[1] = -6.0; y[1] = 4.0;
	x[2] = -3.0; y[2] = 2.0;
	x[3] = -6.0; y[3] = 0.0;
	x[4] = 0.0; y[4] = 8.0;
	x[5] = 0.0; y[5] = 4.0;
	x[6] = 0.0; y[6] = 0.0;
	x[7] = 0.0; y[7] = -4.0;
	x[8] = 3.0; y[8] = 6.0;
	x[9] = 3.0; y[9] = 2.0;
	x[10] = 3.0; y[10] = -2.0;
	x[11] = 6.0; y[11] = 4.0;
	x[12] = 6.0; y[12] = 0.0;
	x[13] = 9.0; y[13] = 2.0;

	a[0] = -7.7; b[0] = 3.5; //0,1�ԁ@�ȉ��ԏȗ�
	a[1] = -6.0; b[1] = 2.3; //0,2
	a[2] = -7.3; b[2] = 1.0; //0,3
	a[3] = -3.5; b[3] = 6.3; //1,4
	a[4] = -3.0; b[4] = 4.3; //1,5
	a[5] = -2.3; b[5] = 3.0; //2,5
	a[6] = -1.5; b[6] = 1.3; //2,6
	a[7] = -3.0; b[7] = 0.3; //3,6
	a[8] = -3.0; b[8] = -1.8; //3,7
	a[9] = 0.4; b[9] = 6.0; //4,5
	a[10] = 1.5; b[10] = 7.0; //4,8
	a[11] = 1.5; b[11] = 3.1; //5,9
	a[12] = 0.4; b[12] = -2.0; //6,7
	a[13] = 1.2; b[13] = 1.3; //6,9
	a[14] = 1.4; b[14] = -2.7; //7,10
	a[15] = 3.4; b[15] = 4.0; //8,9
	a[16] = 4.5; b[16] = 5.1; //8,11
	a[17] = 4.4; b[17] = 3.3; //9,11
	a[18] = 4.5; b[18] = 1.1; //9,12
	a[19] = 4.4; b[19] = -0.7; //10,12
	a[20] = 7.5; b[20] = 3.1; //11,13
	a[21] = 7.4; b[21] = 1.3; //12,13

	/*
	a[0] = -7.5; b[0] = 3.0; //0,1�ԁ@�ȉ��ԏȗ�
	a[1] = -6.0; b[1] = 2.0; //0,2
	a[2] = -7.5; b[2] = 1.0; //0,3
	a[3] = -3.0; b[3] = 6.0; //1,4
	a[4] = -3.0; b[4] = 4.0; //1,5
	a[5] = -1.5; b[5] = 3.0; //2,5
	a[6] = -1.5; b[6] = 1.0; //2,6
	a[7] = -3.0; b[7] = 0.0; //3,6
	a[8] = -3.0; b[8] = -2.0; //3,7
	a[9] = 0.0; b[9] = 6.0; //4,5
	a[10] = 1.5; b[10] = 7.0; //4,8
	a[11] = 1.5; b[11] = 3.0; //5,9
	a[12] = 0.0; b[12] = -2.0; //6,7
	a[13] = 1.5; b[13] = 1.0; //6,9
	a[14] = 1.5; b[14] = -3.0; //7,10
	a[15] = 3.0; b[15] = 4.0; //8,9
	a[16] = 4.5; b[16] = 5.0; //8,11
	a[17] = 4.5; b[17] = 3.0; //9,11
	a[18] = 4.5; b[18] = 1.0; //9,12
	a[19] = 4.5; b[19] = -1.0; //10,12
	a[20] = 7.5; b[20] = 3.0; //11,13
	a[21] = 7.5; b[21] = 1.0; //12,13
	*/
	nx[1] = 10.0; ny[1] = -5.0;  //mouse����p�̋�؂���p���W
	nx[2] = -10.0; ny[2] = -10.0;
	nx[3] = 5.0; ny[3] = -7.5;
	nx[4] = 0.0; 
	nx[5] = -5.0; 

	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0, 1.0, 1.0);
	k = 0;
	for (i = 0; i < nPoint; i++) {
		for (j = i + 1; j < nPoint; j++) {
			if (Distance2[i][j] != -1) {
				if (Distance[i][j] != -1) {
					glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
					sprintf(str, "%d", Distance[i][j]);
					render_string(a[k], b[k], str);
					glEnd();
					k += 1;
				}
				if (Distance[i][j] == -1) {
					k += 1;
				}
			}
		}
	}

	for (i = 0; i < nPoint; i++) {
		glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
		for (j = i + 1; j < nPoint; j++) {
			if (Distance[i][j] != -1) {
				glLineWidth(10.0); // ���𑾂�
				glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
				if ((i == xnum && j == ynum) || (j == xnum && i == ynum)) {
					glColor3f(0.0, 1.0, 0.0); // �}�`�̐F�̎w��
				}
				glBegin(GL_LINES); // glVertex2d�Ŏw�肵���e���W�����ɒ����Ō��ԁB
				glVertex2d(x[i], y[i]);
				glVertex2d(x[j], y[j]);
				glEnd();
			}
		}
		glLineWidth(1.0); // �������ʂ��
	}
	glLineWidth(5.0); // ���𑾂�
	glBegin(GL_LINES); // glVertex2d�Ŏw�肵���e���W�����ɒ����Ō��ԁB
	glVertex2d(nx[1], ny[1]);
	glVertex2d(nx[2], ny[1]);

	glVertex2d(nx[3], ny[1]);
	glVertex2d(nx[3], ny[2]);

	glVertex2d(nx[4], ny[1]);
	glVertex2d(nx[4], ny[2]);

	glVertex2d(nx[5], ny[1]);
	glVertex2d(nx[5], ny[2]);
	glLineWidth(1.0); // �������ʂ��
	glEnd();
	
	for (i = 0; i < nPoint; i++) {
		glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
		drawCircle(x[i], y[i], r);
		glColor3f(1.0, 1.0, 1.0); // �}�`�̐F�̎w��
		if (i == spp) {
			glColor3f(1.0, 0.0, 0.0); // �}�`�̐F�̎w��
		}
		if (i == dp) {
			glColor3f(0.0, 0.0, 1.0); // �}�`�̐F�̎w��
		}
		if (spp == dp && i==dp) {
			glColor3f(1.0, 0.0, 1.0); // �}�`�̐F�̎w��
		}
		drawCircle(x[i], y[i], r - 0.1);
		glColor3f(0.0, 0.0, 0.0);
		glEnd();
	}
	for (i = 0; i < nPoint; i++) {
			glColor3f(0.0, 0.0, 0.0); // �}�`�̐F�̎w��
			sprintf(str, "%d", i);
			render_string(x[i]-0.2, y[i]-0.15, str);
			glEnd();
	}
	render_string(nx[2]+1, ny[3], "Reset"); // ()���ɁAx���W�Ay���W�A������̏��ɋL�q 
	render_string(nx[5]+1, ny[3], "Move");
	render_string(nx[4]+1, ny[3], "Accident"); 
	render_string(nx[3]+1, ny[3], "Traffic jam");
	glFlush();
	glutSwapBuffers(); // png�\���p�D
	
}
int main(int argc, char** argv)
{
	int dummy;
	srand((unsigned int)time(NULL));
	dummy = rand(); // �o�O�΍�i�����̕΂�������j
	dummy = rand();

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT); // �E�B���h�E�T�C�Y��400x400�h�b�g
	glutInitWindowPosition(1000, 300); // �E�B���h�E�̕\���ʒu�̎w��
	glutCreateWindow("�ŒZ�o�H");
	// ���W�͈̔͂��w��BglOrtho(���[��x���W, �E�[��x���W, ���[��y���W, ��[��y���W, �c
	glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
	printf("�J�n���܂��B�����L�[�������Ă��������B"); getchar();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}