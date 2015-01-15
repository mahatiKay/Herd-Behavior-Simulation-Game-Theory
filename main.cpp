using namespace std;
#include<iostream>
#include<string.h>
#include<GLUT/glut.h>
#include "game1.h"

void myinit()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}
void drawAxis()
{
	char opt[] = "OPTIMIZER";
	char imt[] = "IMITATOR";
	int i;
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(100,100);
	glVertex2d(400,100);
	glVertex2d(100,100);
	glVertex2d(100,400);
	glEnd();
	glFlush();
	
	for(i=0;i<strlen(opt);i++)
	{
		glRasterPos2d(200+(i*18), 50);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, opt[i]);
	}
	for(i=0;i<strlen(imt);i++)
	{
		glRasterPos2d(50, 300-(i*18));
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, imt[i]);
	}
	glRasterPos2d(90, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(140, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '2');
	glRasterPos2d(150, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(180, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '4');
	glRasterPos2d(190, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(220, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '6');
	glRasterPos2d(230, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(260, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '8');
	glRasterPos2d(270, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(300, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');
	glRasterPos2d(310, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	glRasterPos2d(320, 85);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	
	
	// y axis
	
	glRasterPos2d(80, 140);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '2');
	glRasterPos2d(90, 140);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(80, 180);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '4');
	glRasterPos2d(90, 180);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(80, 220);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '6');
	glRasterPos2d(90, 220);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(80, 260);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '8');
	glRasterPos2d(90, 260);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	glRasterPos2d(70, 300);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');
	glRasterPos2d(80, 300);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	glRasterPos2d(90, 300);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
	
	
	
}
void plotpoints(float x,float y,int value)
{
	//printf("\nValue : %d",value);
	if(value==0)
		glColor3f(0.7,0.7,0.7);
	else if(value<N/5)
		glColor3f(1,1,0);	//Level 1: YELLOW
	else if(value<2*N/5)
		glColor3f(1,0,1);	//Level 2: Magenta
	else if(value<3*N/5)
		glColor3f(0,1,0);	//Level 3: GREEN
	else if(value<4*N/5)
		glColor3f(0,0,1);	//Level 4: BLUE
	else if(value<N)
		glColor3f(1,0,0);	//Level 5: RED

		
		
	glVertex2d(x,y);
	
}
void legend()
{
	glPointSize(10.0);
	glBegin(GL_POINTS);
	
	char letters[5];
	int i=0;
	//strcpy(letters,"20");
	glColor3f(1,1,0);
	glVertex2d(300,390);
	
	
	glColor3f(1,0,1);
	glVertex2d(300,360);
	
	glColor3f(0,1,0);
	glVertex2d(300,330);

	glColor3f(0,0,1);
	glVertex2d(300,300);

	glColor3f(1,0,0);
	glVertex2d(300,270);
	
	
	glColor3f(0.7,0.7,0.7);
	glVertex2d(300,240);
	
	glEnd();
	glFlush();
	
	
	
	glColor3f(0,0,0);
	strcpy(letters,"X=Av.Sz.Herd");
	for(i=0;i<strlen(letters);i++)
		
	{
		glRasterPos2d(300+(i*9),420);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"X<20%N");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),387);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"20%N<X<40%N");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),357);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"40%N<X<60%N");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),327);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"60%N<X<80%N");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),297);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"80%N<X ");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),267);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
	
	strcpy(letters,"No Herd.");
	for(i=0;i<strlen(letters);i++)
	{
		glRasterPos2d(320+(i*9),237);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letters[i]);
	}
}
void myDisplay()
{
	int hp,nr,value;
	initialize_game();
	glClear(GL_COLOR_BUFFER_BIT);
	printf("\n Game Initializd.\n");
	drawAxis();
	glBegin(GL_POINTS);
	
	for(hp=5,nr=60;hp<=20;hp++,nr-=2)
	{
		//printf("\nBefore game start for CONST Randomizer %d.",r);
		//for(nr=5;nr<=100;nr+=5)
		//{
			value = play_game1(nr,hp);
			plotpoints((hp*2)+100,(nr*2)+100,value);
			reinitialize();
		//}
		printf(".");
	}
	printf("\nGAME OVER.");
	glEnd();
	glFlush();
	legend();
	glFlush();
}

/*void myDisplay1()
{
	int i;
	float *value;//=(int*)malloc(sizeof(int)*NR*2);
	initialize_game();
	glClear(GL_COLOR_BUFFER_BIT);
	printf("Game intialized.\n");
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(100,100);
	glVertex2d(400,100);
	glVertex2d(100,100);
	glVertex2d(100,400);
	glEnd();
	glFlush();
	
	value = play_game2(30,10);
	glBegin(GL_LINES);
	for(i=0;i<2*NR;i++)
	{
		glPointSize(1.0);
		glColor3f(1.0,0.0,0.0);
		glVertex2d(100+(i+1)*5,100);
		glVertex2d(100+(i+1)*5,100+10*value[i]);
		
		i++;
		glColor3f(0.0,0.0,1.0);
		glVertex2d(100+(i+1)*5+2,100);
		glVertex2d(100+(i+1)*5+2,100+10*value[i]);
		
	}
	glEnd();
	glFlush();
}*/

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Graph plotting");
	
	glutDisplayFunc(myDisplay);
	myinit();
	glutMainLoop();
	return 0;
}
