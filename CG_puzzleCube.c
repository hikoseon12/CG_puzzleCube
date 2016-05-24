#include <string.h>
#include<GL/glut.h>
#include<stdio.h>

static float speed=0.0;

int count = 0;
static int rotation=0;
int rotationcomplete=0;
static GLfloat theta=0.0;
static GLfloat angle=0.0;
static GLfloat p=0.0,q=0.0,r=0.0;
static GLint inverse=0;
int beginx=0,beginy=0;
int moving=0;
									
GLfloat vertices[27][3]={{-2.0,-2.0,-2.0},{0.0, -2.0,-2.0},{2.0,-2.0,-2.0}, // 0 1 2
						 {-2.0,-2.0, 0.0},{0.0, -2.0,0.0},{2.0,-2.0,0.0}, // 3 4 5
						 {-2.0,-2.0, 2.0},{0.0,-2.0, 2.0},{2.0,-2.0, 2.0}, // 6 7 8
						 
						 {-2.0,0.0,-2.0},{0.0,0.0,-2.0},{2.0,0.0,-2.0}, // 9 10 11
						 {-2.0,0.0, 0.0},{0.0,0.0, 0.0},{2.0,0.0, 0.0}, // 12 13 14
						 {-2.0,0.0, 2.0},{0.0,0.0, 2.0},{2.0,0.0, 2.0}, // 15 16 17 

						 {-2.0,2.0,-2.0}, {0.0,2.0,-2.0},{2.0,2.0,-2.0}, // 18 19 20 
						 {-2.0,2.0,0.0},{0.0,2.0,0.0},{2.0,2.0,0.0},     // 21 22 23 
						 {-2.0,2.0,2.0}, {0.0,2.0,2.0}, {2.0,2.0,2.0},  // 24 25 26
						};

GLfloat color[7][3]={{1.0,1.0,1.0},  //0 white
                    {1.0,0.5,0.0},  //1 orange
                    {0.0,0.0,1.0},  //2 blue
                    {0.0,1.0,0.0},  //3 green
                    {1.0,1.0,0.0},  //4 yellow
                    {1.0,0.0,0.0},  //5 red
					{0.5,0.5,0.5},  //6 black used to represent faces of cube without colour
					};

static int top[2][2]={{4,4},{4,4}},  //4 yellow
			bottom[2][2]={{0,0},{0,0}},//0 white
			left[2][2]={{1,1},{1,1},},//1 orange
			right[2][2]={{5,5},{5,5}},//5 red
			front[2][2]={{2,2},{2,2}},//2 blue
			back[2][2]={{3,3},{3,3}},//3 green
			temp[2][2];

void *font = GLUT_BITMAP_TIMES_ROMAN_24;
char defaultMessage[] = "<Puzzle Cube>";
char *message = defaultMessage;
char defaultcount[] = "count: ";
char *countterm = defaultcount;
char countnum[] = " 0 1 2 3 4 5 6 7 8 9101112131415161718192021222324252627282930";
char *numcount = countnum;
int start = 1;

void output(int x, int y, char *string)
{
  int len, i;
  
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);   
  }
}

void countoutput()
{
  int len, i;
//  printf("count = %d\n", count);
  if(start == 1){
  glRasterPos2f(-9, 3);
  len = (int) strlen(countterm);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, countterm[i]);   
  }

   glRasterPos2f(-5, 3);
   len = (int) strlen(countnum);
  for (i = count*2; i < (count*2)+2 ; i++){
    glutBitmapCharacter(font, countnum[i]);   
  }
  }
}

void polygon(int a,int b,int c,int d,int e)
{

	glColor3f(0,0,0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);  // 테두리 라인 그리기
	glVertex3fv(vertices[d]);
	glVertex3fv(vertices[e]);
	glEnd();

	glColor3fv(color[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glVertex3fv(vertices[e]);
	glEnd(); 
}

void smallcube1()  // bottom back left
{
	polygon(back[1][1],0,9,10,1); //3 = green
	polygon(6,3,4,13,12);
	polygon(left[0][1],0,3,12,9); // 1 = orange
    polygon(6,4,1,10,13);
	polygon(6,9,12,13,10);
	polygon(bottom[0][0],0,1,4,3);

}
void smallcube2() // bottom back right
{
	polygon(back[0][1],1,10,11,2); 
	polygon(6,4,5,14,13);
	polygon(6,1,4,13,10); 
   	polygon(right[1][1],5,2,11,14);
	polygon(6,10,13,14,11);
	polygon(bottom[1][0],1,2,5,4);
}

void smallcube3() //bottom front left
{

	polygon(6,3,12,13,4); 
	polygon(front[0][1],6,7,16,15);
	polygon(left[1][1],3,6,15,12); 
   	polygon(6,7,4,13,16);
	polygon(6,12,15,16,13);
	polygon(bottom[0][1],6,3,4,7);

}

void smallcube4()//bottom front right
{
	polygon(6,4,13,14,5); 
	polygon(front[1][1],7,8,17,16);
	polygon(6,4,7,16,13); 
   	polygon(right[0][1],8,5,14,17);
	polygon(6,13,16,17,14);
	polygon(bottom[1][1],7,4,5,8);
}

void smallcube5() //top back left
{
	polygon(back[1][0],9,18,19,10);
	polygon(6,12,13,22,21);
	polygon(left[0][0],9,12,21,18);
    polygon(6,13,10,19,22);
	polygon(top[0][0],18,21,22,19);
	polygon(6,9,10,13,12);

}

void smallcube6() // top back right
{
	polygon(back[0][0],10,19,20,11); 
	polygon(6,13,14,23,22);
	polygon(6,10,13,22,19); 
   	polygon(right[1][0],14,11,20,23);
	polygon(top[1][0],19,22,23,20);
	polygon(6,10,11,14,13);
}

void smallcube7() //top front left
{
	polygon(6,12,21,22,13); 
	polygon(front[0][0],15,16,25,24);
	polygon(left[1][0],12,15,24,21); 
   	polygon(6,16,13,22,25);
	polygon(top[0][1],21,24,25,22);
	polygon(6,15,12,13,16);

}


void smallcube8()//top front right
{
	polygon(6,13,22,23,14); 
	polygon(front[1][0],16,17,26,25);
	polygon(6,13,16,25,22); 
   	polygon(right[0][0],17,14,23,26);
	polygon(top[1][1],22,25,26,23);
	polygon(6,16,13,14,17);
}

void success(){
	int success = 0;
	int i, j;

	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			if(top[i][j] == 4 && bottom[i][j] == 0 && front[i][j] == 2 && back[i][j] == 3 && left[i][j] == 1 && right[i][j] == 5){
					success++;
			}
		}
	}
	if(success == 4 && count != 0 && rotationcomplete==1){	
		output(-9,0,"SUCCESS");
		 inverse = 0;
	}
}

void display()

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3fv(color[0]);
	output(-3,7,message);
	
	glColor3f(1.0,0.0,1.0);
	success();

	glColor3f(0.0,1.0,1.0);
	countoutput();
	
	glColor3fv(color[0]);
	switch(rotation){
	case 1:
		output(-9,4,"Top");
		break;
	case 2:
		output(-9,4,"Bottom");
		break;
	case 3:
		output(-9,4,"Left");
		break;
	case 4:
		output(-9,4,"Right");
		break;
	case 5:
		output(-9,4,"Front");
		break;
	case 6:
		output(-9,4,"Back");
		break;
	default:
		break;

	}
	if(inverse == 1)
		output(-6,4,"inverted");

	glPushMatrix(); //마우스 드래그에 따라 움직이기
    glRotatef(25.0+p,1.0,0.0,0.0);
    glRotatef(-30.0+q,0.0,1.0,0.0);
    glRotatef(0.0+r,0.0,0.0,1.0);

	if(rotation==0){
		smallcube1();
		smallcube2();
		smallcube3();
		smallcube4();
		smallcube5();
		smallcube6();
		smallcube7();
		smallcube8();
	}

	if(rotation==1){
		smallcube1();
		smallcube2();
		smallcube3();
		smallcube4();

		if(inverse==0){
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,0.0,1.0,0.0);
		}
		else{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,0.0,1.0,0.0);
		}
		smallcube5();
		smallcube6();
		smallcube7();
		smallcube8();
	}

	if(rotation==2){
		smallcube5();
		smallcube6();
		smallcube7();
		smallcube8();

		if(inverse==0)
		{	
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,0.0,1.0,0.0);
		}
		else
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,0.0,1.0,0.0);
		}
		smallcube1();
		smallcube2();
		smallcube3();
		smallcube4();
	}

	if(rotation==3){
		smallcube2();
		smallcube4();
		smallcube6();
		smallcube8();

		if(inverse==0)
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,1.0,0.0,0.0);
		}
		else
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,1.0,0.0,0.0);
		}
		smallcube1();
		smallcube3();
		smallcube5();
		smallcube7();
	}

	if(rotation==4){
		smallcube1();
		smallcube3();
		smallcube5();
		smallcube7();

		if(inverse==0)
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,1.0,0.0,0.0);
		}
		else
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,1.0,0.0,0.0);
		}
		smallcube2();
		smallcube4();
		smallcube6();
		smallcube8();
	}

	if(rotation==5){
		smallcube1();
		smallcube2();
		smallcube5();
		smallcube6();

		if(inverse==0)
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,0.0,0.0,1.0);
		}
		else
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,0.0,0.0,1.0);
		}

		smallcube3();
		smallcube4();
		smallcube7();
		smallcube8();
	}

	if(rotation==6){
		smallcube3();
		smallcube4();
		smallcube7();
		smallcube8();

		if(inverse==0)
		{	glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(theta,0.0,0.0,1.0);
		}
		else
		{
			glPushMatrix();
			glColor3fv(color[0]);
			glPopMatrix();
			glRotatef(-theta,0.0,0.0,1.0);
		}
		smallcube1();
		smallcube2();
		smallcube5();
		smallcube6();
	}
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void topchange()
{
	int tmp1 = front[0][0];
	int tmp2 = front[1][0];

	int tmp;
	tmp=top[0][0];
	top[0][0]=top[0][1];
	top[0][1]=top[1][1];
	top[1][1]=top[1][0];
	top[1][0]=tmp;

	front[0][0] = right[0][0];
	front[1][0] = right[1][0];

	right[0][0] = back[0][0];
	right[1][0] = back[1][0];

	back[0][0] = left[0][0];
	back[1][0] = left[1][0];

	left[0][0] = tmp1;
	left[1][0] = tmp2;
}

void bottomchange()
{
	int tmp1 = front[0][1];
	int tmp2 = front[1][1];

	int tmp;
	tmp=bottom[0][0];
	bottom[0][0]=bottom[1][0];
	bottom[1][0]=bottom[1][1];
	bottom[1][1]=bottom[0][1];
	bottom[0][1]=tmp;

	front[0][1] = left[0][1];
	front[1][1] = left[1][1];

	left[0][1] = back[0][1];
	left[1][1] = back[1][1];

	back[0][1] = right[0][1];
	back[1][1] = right[1][1];

	right[0][1] = tmp1;
	right[1][1] = tmp2;
}

void leftchange()
{
	int tmp1 = top[0][0];
	int tmp2 = top[0][1];

	int tmp;
	tmp=left[0][0];
	left[0][0]=left[0][1];
	left[0][1]=left[1][1];
	left[1][1]=left[1][0];
	left[1][0]=tmp;
	
	top[0][0] = back[1][1];
	top[0][1] = back[1][0];

	back[1][1] = bottom[0][1];
	back[1][0] = bottom[0][0];

	bottom[0][1] = front[0][0];
	bottom[0][0] = front[0][1];

	front[0][0] = tmp1;
	front[0][1] = tmp2;
}

void rightchange()
{
	int tmp1 = top[1][0];
	int tmp2 = top[1][1];

	int tmp;
	tmp=right[0][0];
	right[0][0]=right[0][1];
	right[0][1]=right[1][1];
	right[1][1]=right[1][0];
	right[1][0]=tmp;
	
	top[1][0] = front[1][0];
	top[1][1] = front[1][1];

	front[1][0] = bottom[1][1];
	front[1][1] = bottom[1][0];

	bottom[1][1] = back[0][1];
	bottom[1][0] = back[0][0];

	back[0][1] = tmp1;
	back[0][0] = tmp2;
}

void frontchange()
{
	int tmp1 = top[0][1];
	int tmp2 = top[1][1];

	int tmp;
	tmp=front[0][0];
	front[0][0]=front[0][1];
	front[0][1]=front[1][1];
	front[1][1]=front[1][0];
	front[1][0]=tmp;
	
	top[0][1] = left[1][1];
	top[1][1] = left[1][0];

	left[1][1] = bottom[1][1];
	left[1][0] = bottom[0][1];

	bottom[1][1] = right[0][0];
	bottom[0][1] = right[0][1];

	right[0][0] = tmp1;
	right[0][1] = tmp2;
}


void backchange()
{
	int tmp1 = top[0][0];
	int tmp2 = top[1][0];

	int tmp;
	tmp=back[0][0];
	back[0][0]=back[1][0];
	back[1][0]=back[1][1];
	back[1][1]=back[0][1];
	back[0][1]=tmp;
	
	top[0][0] = right[1][0];
	top[1][0] = right[1][1];

	right[1][0] = bottom[1][0];
	right[1][1] = bottom[0][0];

	bottom[1][0] = left[0][1];
	bottom[0][0] = left[0][0];

	left[0][1] = tmp1;
	left[0][0] = tmp2;
}

void spincube()
{   
	theta+=0.4+speed;
	
	if(theta==360.0)
		theta-=360.0;
	
	if(theta>=90.0)
	{
		rotationcomplete = 1;
		glutIdleFunc(NULL);

		if(rotation==1&&inverse==0)
		{
			topchange();
		}
		if(rotation==1&&inverse==1)
		{
			topchange();
			topchange();
			topchange();
		}
	
		if(rotation==2&&inverse==0)
		{
			bottomchange();
	   }
		if(rotation==2&&inverse==1)
		{
			bottomchange();
			bottomchange();
			bottomchange();
		}
		if(rotation==3&&inverse==0)
		{
			leftchange();
		}
		if(rotation==3&&inverse==1)
		{
			leftchange();
			leftchange();
			leftchange();
		}
		if(rotation==4&&inverse==0)
		{
			rightchange();
		}
		if(rotation==4&&inverse==1)
		{
			rightchange();
			rightchange();
			rightchange();
		}
		if(rotation==5&&inverse==0)
		{
			frontchange();
		}
		if(rotation==5&&inverse==1)
		{
			frontchange();
			frontchange();
			frontchange();
		}
		if(rotation==6&&inverse==0)
		{
			backchange();
		}
		if(rotation==6&&inverse==1)
		{
			backchange();
			backchange();
			backchange();
		}

		rotation=0;
		inverse = 0;
		theta=0;
	}

	glutPostRedisplay();
}


void motion(int x, int y)
{
  if (moving) {

    q=q + (x - beginx);
    beginx = x;
    p=p + (y - beginy);
	beginy=y;
	glutPostRedisplay();
  }
}


void mouse(int btn,int state,int x,int y)
{
   moving = 1;
   beginx = x;
   beginy = y;
}

void reset()
{
	int i, j;
	for(i = 0;i < 2 ;i++){
		for(j = 0; j < 2; j++){
			top[i][j] = 4;
			bottom[i][j] = 0;
			left[i][j] = 1;
			right[i][j] = 5;
			front[i][j] = 2;
			back[i][j] = 3;
		}
	}
	count = 0;
	inverse = 0;
	theta=0;
	beginx=0;beginy=0;
	p=0.0,q=0.0,r=0.0;
}

static void keyboard(unsigned char key,int x,int y)
{
	if(key=='a'&&rotationcomplete==1)
	{     rotationcomplete=0;
          rotation=1;
		  inverse=0;
		  ++count;
		  glutIdleFunc(spincube);
	}
	
	if(key=='q'&&rotationcomplete==1)
	{     rotationcomplete=0;
          rotation=1;
		  inverse=1;
		  ++count;
		  glutIdleFunc(spincube);
	}
	
	if(key=='s'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=2;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	}
	
	if(key=='w'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=2;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='d'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=3;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='e'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=3;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	}


	if(key=='f'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=4;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='r'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=4;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='g'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=5;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='t'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=5;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	}


	if(key=='h'&&rotationcomplete==1)
	{
		rotationcomplete=0;
		rotation=6;
		inverse=0;
		++count;
		glutIdleFunc(spincube);

	}


	if(key=='y'&&rotationcomplete==1)
	{	rotationcomplete=0;
		rotation=6;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	}

	if(key=='m'&&rotationcomplete==1)
	{
        speed=speed+0.2;
		glutPostRedisplay();
	}

	if(key=='n'&&rotationcomplete==1)
	{
		if(speed > 0.2){
			speed=speed-0.1;
		}
		glutPostRedisplay();
	}
	if(key=='z'&&rotationcomplete==1)
	{
		reset();
		glutPostRedisplay();
	}
}


void myshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
	glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}

void mymenu(int id)
{
	if(rotationcomplete==1)
	{rotationcomplete=0;
switch(id)
{
    case 1:
		rotation=1;
       	inverse=0;
		++count;
	    glutIdleFunc(spincube);
	break;

	case 2:
		rotation=1;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	break;

	case 3:
		rotation=2;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	break;

	case 4:
		rotation=2;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	break;

	case 5:
		rotation=3;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	break;

	case 6:
		rotation=3;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	break;

	case 7:
		rotation=4;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	break;

	case 8:
		rotation=4;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	break;

	case 9:
		rotation=5;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	break;

	case 10:
		rotation=5;
		++count;
		glutIdleFunc(spincube);
	break;

	case 11:
		rotation=6;
		inverse=0;
		++count;
		glutIdleFunc(spincube);
	break;

	case 12:
		rotation=6;
		inverse=1;
		++count;
		glutIdleFunc(spincube);
	break;
		
	case 13:
		exit(0);
	break;
	}
	}
}
int main(int argc, char** argv)
{
	GLint i;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutCreateWindow ("Puzzle Cube-CG project");
	glutReshapeFunc (myshape);
	glutIdleFunc(spincube);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutCreateMenu(mymenu);
	glutAddMenuEntry("Top			:a",1);
	glutAddMenuEntry("Top Inverted	:q",2);
	glutAddMenuEntry("Bottom		:s",3);
	glutAddMenuEntry("Bottom Inverted:	w",4);
	glutAddMenuEntry("Left			:d",5);
	glutAddMenuEntry("Left Inverted	:e",6);
	glutAddMenuEntry("Right			:f",7);
	glutAddMenuEntry("Right Inverted	:r",8);
	glutAddMenuEntry("Front			:g",9);
	glutAddMenuEntry("Front Inverted	:t",10);
	glutAddMenuEntry("Back			:h",11);
	glutAddMenuEntry("Back Inverted	:y",12);

	glutAddMenuEntry("Exit",13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc (display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

