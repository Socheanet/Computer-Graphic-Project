#include<GL/gl.h>
#include<GL/glu.h>
#include<Gl/glut.h>
#include<windows.h>
#include<stdio.h>
#include<math.h>

int score = 0;
int lives = 0;

void display();
void init();
void reshape(int ,int);
void timer(int);
void key(unsigned char, int, int);
void mouse(int button, int state, int x, int y);
void drawBg();
void drawJet();
void drawAirCraft();
void moveBuilding();
void building1();
void building2();
void building3();
void building4();
void building5();
void bullet();
void moveBullet();
void moveJet();
void enemy();
void enemy1();
void moveEnemey();
void drawString();
void printScore();
void printLives();
void welcome();
void gameEnd();
int SCREENH=600,SCREENW=800;
bool wflag = true,gameEndStatus=false,instflag=false,abtflag=false,start=false;  //flags

float x_position = -8.0;
float y_position = 2.0;
float x_drop = 0.0;
float y_drop = 0.0;
float jet_x=10.0;
float jet_y=0.0;
float build_x1=10.0;
float build_x2=-5.0;
float build_x3 = 3.0;
float build_x4=6.0;
float build_y1=0.0;
float build_x5=0.0;
float build_y5=0.0;
float bul_x=0.0;
float bul_y=0.0;
float en_x=10.0;
float en_y=10.0;
float en_x1=10.0;
float en_y1=10.0;
int state = 1;
//int score=0;
char sscore[20];
//int lives=0;
char slives[20];


int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(400,100);
    glutInitWindowSize(800,600);

    glutCreateWindow("AirCraft_War");
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutTimerFunc(0,timer,0);
    init();
    glutReshapeFunc(reshape);



    glutMainLoop();
}

void drawString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void welcome()
{
	glColor3f(0.8,0.8,0.8);   //welcome background
	glBegin(GL_POLYGON);
	glVertex3f(-10.0,-10.0,0.0);
	glColor3f(0.137,0.137,0.556);
	glVertex3f(100.0,-10.0,0.0);
	glColor3f(0.196,0.196,0.8);
	glVertex3f(100.0,100.0,0.0);
	glVertex3f(-10.0,100.0,0.0);
	glEnd();
	//drawJet();

	// button 1 .. PLAY
	glColor3f(0.196,0.196,0.8);
	glRectf(-3.0,4.0,2.5,5.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(-2.7,4.3,2.2,5.2);
	glColor3f(0.137,0.137,0.556);
	drawString(-1.0,4.5,0,GLUT_BITMAP_HELVETICA_18,"PLAY");

	// button 2 .. instructions
	glColor3f(0.196,0.196,0.8);
	glRectf(-3.0,2.0,2.5,3.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(-2.7,2.3,2.2,3.2);
	glColor3f(0.137,0.137,0.556);
	drawString(-2.0,2.5,0,GLUT_BITMAP_HELVETICA_18,"INSTRUCTIONS");

	// button 3 .. ABOUT
	glColor3f(0.196,0.196,0.8);
	glRectf(-3.0,0.0,2.5,1.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(-2.7,0.3,2.2,1.2);
	glColor3f(0.137,0.137,0.556);
	drawString(-1.0,0.5,0,GLUT_BITMAP_HELVETICA_18,"ABOUT");

	// button 4 .. exit
	glColor3f(0.196,0.196,0.8);
	glRectf(-3.0,-2.0,2.5,-0.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(-2.7,-1.7,2.2,-0.8);
	glColor3f(0.137,0.137,0.556);
	drawString(-0.7,-1.5,0,GLUT_BITMAP_HELVETICA_18,"EXIT");


	glPushMatrix();

	glColor3f(0.137,0.137,0.556);
	drawString(-5.0,9.2,0,GLUT_BITMAP_TIMES_ROMAN_24,"COMPUTER GRAPHICS PROJECT ");
	drawString(-3.5,8.0,0,GLUT_BITMAP_TIMES_ROMAN_24,"AIRCRAFT WAR GAME ");
	glPopMatrix();
	glColor3f(0.137,0.137,0.556);

}

void drawBg()
{
	glPushMatrix();

	glColor3f(0.0,0.48,0.047);		// green floor

	glBegin(GL_POLYGON);
	glVertex2f(-10.0,-8.0);
	glVertex2f(100.0,-8.0);
	glColor3f(0.0,0.3,0.03);
	glVertex2f(100.0,-7.0);
	glVertex2f(-10.0,-7.0);
	glVertex2f(-10.0,-8.0);
	glEnd();

	glColor3f(0.474,0.298,0.074);  // brown ground
	glBegin(GL_POLYGON);
	glVertex2f(-10.0,-17.0);
	glVertex2f(100.0,-17.0);
	glColor3f(0.3,0.1,0.03);
	glVertex2f(100.0,-8.0);
	glVertex2f(-10.0,-8.0);
	glEnd();

	glColor3f(0.5,0.6,0.79);
	glBegin(GL_POLYGON);				//ceiling
	glVertex2f(-10.0,100.0);
	glVertex2f(100.0,100.0);
	glColor3f(0.6,0.7,0.89);
	glVertex2f(100.0,80.0);
	glVertex2f(-10.0,80.0);
	glEnd();

	glColor3f(0.5,0.6,0.79);// sky blue
	glBegin(GL_POLYGON);   //background screen
	glVertex2f(-10.0,90.0);
	glVertex2f(100.0,90.0);
	glColor3f(0.7,0.8,0.99);//sky
	glVertex2f(100.0,-7.0);
	glVertex2f(-10.0,-7.0);
	glEnd();

	glPopMatrix();
}

void drawAirCraft(){

     glTranslatef(x_position,y_position,0.0);
    glPushMatrix();

    //pilot
    glBegin(GL_QUADS);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.5,0.0);
    glVertex2f(0.5,0.3);
    glVertex2f(1.1,0.3);
    glVertex2f(1.1,0.0);
    glEnd();
    //body
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-0.5,-1.0);
    glVertex2f(-0.5,0.0);
    glVertex2f(1.5,0.0);
    glVertex2f(1.5,-1.0);
    glEnd();

    //tail
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-1.0,0.5);
    glVertex2f(0.5,-1.0);
    glEnd();
    //Head
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(1.5,-1.0);
    glVertex2f(1.5,0.0);
    glVertex2f(1.8,-0.5);
    glEnd();





}

void drawJet(){


    glPushMatrix();
   // glTranslatef(jet_x,jet_y,0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(jet_x+0.5,8.0);
    glVertex2f(jet_x+1,8.5);
    glVertex2f(jet_x+1,7.5);
    glEnd();
     //Tail
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(jet_x+1.5,8.0);
    glVertex2f(jet_x+2.5,8.7);
    glVertex2f(jet_x+2.5,7.3);
    glEnd();
    //body
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(jet_x+1,7.5);
    glVertex2f(jet_x+1,8.5);
    glVertex2f(jet_x+2,8.5);
    glVertex2f(jet_x+2,7.5);
    glEnd();



}

void building1(){
    glPushMatrix();
    glTranslatef(build_x1,0.0,0.0);

    //1st Building
    //Building Black Blue
   glBegin(GL_QUADS);
   glColor3f(0.1,0.1,0.1);
   glVertex2f(-10.0,-7.0);
   glVertex2f(-10.0,0.0);
   glColor3f(0.0,0.0,1.0);
   glVertex2f(-6.5,0.0);
   glVertex2f(-6.5,-7.0);
   glEnd();

   //Windows
   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5,-2.0);
   glVertex2f(-9.5,-1.0);       //Third Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5,-1.0);
   glVertex2f(-8.5,-2.0);
   glEnd();


   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0,-2.0);
   glVertex2f(-8.0,-1.0);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0,-1.0);
   glVertex2f(-7.0,-2.0);
   glEnd();

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5,-2.5);
   glVertex2f(-9.5,-3.5);
   glColor3f(1.0,1.0,1.0);    //Second Floor
   glVertex2f(-8.5,-3.5);
   glVertex2f(-8.5,-2.5);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0,-2.5);
   glVertex2f(-8.0,-3.5);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0,-3.5);
   glVertex2f(-7.0,-2.5);
   glEnd();

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5,-5.0);
   glVertex2f(-9.5,-4.0);   //First Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5,-4.0);
   glVertex2f(-8.5,-5.0);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0,-5.0);
   glVertex2f(-8.0,-4.0);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0,-4.0);
   glVertex2f(-7.0,-5.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.0,-7.0);
   glVertex2f(-9.0,-5.5);   //Ground Door
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.5,-5.5);
   glVertex2f(-7.5,-7.0);
   glEnd();
   glPopMatrix();

}


void building2(){
    glPushMatrix();
    //2nd Building

    //Building Black red
   glTranslatef(build_x2,0.0,0.0);
   glBegin(GL_QUADS);
   glColor3f(0.1,0.1,0.1);
   glVertex2f(-10.0+5.5,-7.0);
   glVertex2f(-10.0+5.5,1.5);
   glColor3f(1.0,0.0,0.0);
   glVertex2f(-6.5+5.5,1.5);
   glVertex2f(-6.5+5.5,-7.0);
   glEnd();


   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+5.5,-0.5);
   glVertex2f(-9.5+5.5,0.5);       //Fourth Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5+5.5,0.5);
   glVertex2f(-8.5+5.5,-0.5);
   glEnd();


   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+5.5,-0.5);
   glVertex2f(-8.0+5.5,0.5);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+5.5,0.5);
   glVertex2f(-7.0+5.5,-0.5);
   glEnd();

   //Windows
   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+5.5,-2.0);
   glVertex2f(-9.5+5.5,-1.0);       //Third Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5+5.5,-1.0);
   glVertex2f(-8.5+5.5,-2.0);
   glEnd();


   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+5.5,-2.0);
   glVertex2f(-8.0+5.5,-1.0);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+5.5,-1.0);
   glVertex2f(-7.0+5.5,-2.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+5.5,-2.5);
   glVertex2f(-9.5+5.5,-3.5);
   glColor3f(1.0,1.0,1.0);    //Second Floor
   glVertex2f(-8.5+5.5,-3.5);
   glVertex2f(-8.5+5.5,-2.5);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.0);
   glVertex2f(-8.0+5.5,-2.5);
   glVertex2f(-8.0+5.5,-3.5);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+5.5,-3.5);
   glVertex2f(-7.0+5.5,-2.5);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+5.5,-5.0);
   glVertex2f(-9.5+5.5,-4.0);   //First Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5+5.5,-4.0);
   glVertex2f(-8.5+5.5,-5.0);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.0+5.5,-5.0);
   glVertex2f(-8.0+5.5,-4.0);
   glColor3f(0.0,0.0,0.0);
   glVertex2f(-7.0+5.5,-4.0);
   glVertex2f(-7.0+5.5,-5.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.0+5.5,-7.0);
   glVertex2f(-9.0+5.5,-5.5);   //Ground Door
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.5+5.5,-5.5);
   glVertex2f(-7.5+5.5,-7.0);
   glEnd();
   glPopMatrix();
}

void building3(){
    glPushMatrix();
    //3rd Building
   //Building Green Yellow
   glTranslatef(build_x3,0.0,0.0);
   glBegin(GL_QUADS);
   glColor3f(0.,0.8,0.0);
   glVertex2f(-10.0+11.0,-7.0);
   glVertex2f(-10.0+11.0,-1.0);
   glColor3f(0.8,0.8,0.0);
   glVertex2f(-6.5+11.0,-1.0);
   glVertex2f(-6.5+11.0,-7.0);
   glEnd();

   //Windows

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+11.0,-2.5);
   glVertex2f(-9.5+11.0,-3.5);
   glColor3f(1.0,1.0,1.0);    //Second Floor
   glVertex2f(-8.5+11.0,-3.5);
   glVertex2f(-8.5+11.0,-2.5);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+11.0,-2.5);
   glVertex2f(-8.0+11.0,-3.5);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+11.0,-3.5);
   glVertex2f(-7.0+11.0,-2.5);
   glEnd();

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+11.0,-5.0);
   glVertex2f(-9.5+11.0,-4.0);   //First Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5+11.0,-4.0);
   glVertex2f(-8.5+11.0,-5.0);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+11.0,-5.0);
   glVertex2f(-8.0+11.0,-4.0);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+11.0,-4.0);
   glVertex2f(-7.0+11.0,-5.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.0+11.0,-7.0);
   glVertex2f(-9.0+11.0,-5.5);   //Ground Door
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.5+11.0,-5.5);
   glVertex2f(-7.5+11.0,-7.0);
   glEnd();
   glPopMatrix();

}
void building4(){
    glPushMatrix();
    //4th Building
   //Building blue Yellow
   glTranslatef(build_x4,0.0,0.0);
   glBegin(GL_QUADS);
   glColor3f(0.,0.8,0.8);
   glVertex2f(-10.0+15.0,-7.0);
   glVertex2f(-10.0+15.0,-1.0);
   glColor3f(0.8,0.8,0.0);
   glVertex2f(-6.5+15.0,-1.0);
   glVertex2f(-6.5+15.0,-7.0);
   glEnd();

   //Windows

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+15.0,-2.5);
   glVertex2f(-9.5+15.0,-3.5);
   glColor3f(1.0,1.0,1.0);    //Second Floor
   glVertex2f(-8.5+15.0,-3.5);
   glVertex2f(-8.5+15.0,-2.5);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+15.0,-2.5);
   glVertex2f(-8.0+15.0,-3.5);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+15.0,-3.5);
   glVertex2f(-7.0+15.0,-2.5);
   glEnd();

   glColor3f(0.8,0.5,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.5+15.0,-5.0);
   glVertex2f(-9.5+15.0,-4.0);   //First Floor
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-8.5+15.0,-4.0);
   glVertex2f(-8.5+15.0,-5.0);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.8,0.5,0.0);
   glVertex2f(-8.0+15.0,-5.0);
   glVertex2f(-8.0+15.0,-4.0);
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.0+15.0,-4.0);
   glVertex2f(-7.0+15.0,-5.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(-9.0+15.0,-7.0);
   glVertex2f(-9.0+15.0,-5.5);   //Ground Door
   glColor3f(1.0,1.0,1.0);
   glVertex2f(-7.5+15.0,-5.5);
   glVertex2f(-7.5+15.0,-7.0);
   glEnd();
   glPopMatrix();

}

void building5(){
  glColor3f(0.0,0.0,0.0);   //Orange White
   glBegin(GL_QUADS);
   glVertex2f(0.0,0.0);
   glVertex2f(0.0,0.0);   //Ground Door
   glVertex2f(0.0,0.0);
   glVertex2f(0.0,0.0);
   glEnd();
   glPopMatrix();
}


void bullet(){

    glPushMatrix();
    glTranslatef(bul_x,bul_y,0.0);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,-0.40);
    glVertex2f(0.40,-0.20);
    glEnd();

    glPopMatrix();


}

void enemy(){
    glPushMatrix();
    glTranslatef(en_x,en_y,0.0);
    //head
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glEnd();

    //body
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.5,-0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(1.5,0.5);
    glVertex2f(1.5,-0.5);
    glEnd();

    //tail
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(1.3,-0.2);
    glVertex2f(1.3,0.2);
    glVertex2f(1.8,0.7);
    glVertex2f(1.8,-0.7);
    glEnd();
    glPopMatrix();
}



void enemy1(){
 glPushMatrix();
    glTranslatef(en_x1,en_y1,0.0);
    //head
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glEnd();

    //body
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.5,-0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(1.5,0.5);
    glVertex2f(1.5,-0.5);
    glEnd();

    //tail
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(1.3,-0.2);
    glVertex2f(1.3,0.2);
    glVertex2f(1.8,0.7);
    glVertex2f(1.8,-0.7);
    glEnd();
    glPopMatrix();
}



void printScore(){
    glColor3f(1.0,1.0,0.0); // score
    drawString(-9.0,9.0,0,GLUT_BITMAP_TIMES_ROMAN_24,"Score:");
    sprintf_s(sscore,"%d", (int) score);
    drawString(-7.5,9.0,0,GLUT_BITMAP_TIMES_ROMAN_24, sscore);

}

void printLives(){
    glColor3f(1.0,1.0,0.0); // score
    drawString(6.0,9.0,0,GLUT_BITMAP_TIMES_ROMAN_24,"Lives Lost:");
    sprintf_s(slives,"%d", (int) lives);
    drawString(9,9.0,0,GLUT_BITMAP_TIMES_ROMAN_24, slives);
}

void moveEnemey(){

    if(en_x>-12){
        en_x-=0.1;
        if(bul_x>=en_x && bul_y<=en_y+1.0 && bul_y >=en_y-1){
            en_x=10.0;
            en_y=en_y-3;
            score = score+1;
        }
    }
    else {
        lives= lives +1;
        en_x=10.0;
        en_y=en_y-3;

    }
    if(en_y<=-6){
        en_y=8;
    }
    if(en_x1>-12){
        en_x1-=0.1;
         if(bul_x>=en_x1 && bul_y<=en_y1+1.0 && bul_y >=en_y1-1){
            en_x1=10.0;
            en_y1=en_y1+4;
            score = score + 1;
        }
    }
    else {
        lives = lives + 1;
        en_x1=10.0;
        en_y1 = en_y1+4;
    }
    if(en_y1>8){
        en_y1=-6;
    }

}

void moveBullet(){

    y_position = y_position-0.03;
    if(y_position <= -8){
        y_position=-8;
    }
    bul_x=bul_x+0.90;

    if(bul_x>11){
        bul_x=x_position;
         bul_y=y_position-0.3;

    }
}
void moveBuilding(){
    build_x2-=0.20;
    build_x1-=0.20;
    build_x3-=0.20;
    build_x4-=0.20;


if(build_x2<-10){
    build_x2=20;
}
if(build_x1<-10){

    build_x1=20;
}
if(build_x3<-15){
    build_x3=20;
}
if(build_x4<-20){
    build_x4=20;
}

}

void moveJet(){

    if(jet_x>-12){
        jet_x = jet_x-0.15;


    }
    else {
        jet_x=10.0;
    }

}



void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BITS) ;
    glLoadIdentity();

    if(lives >=3){
        start = false;
        gameEndStatus=true;

    }

    if(wflag==true){
        welcome();
    }
    else if(gameEndStatus == true)//Welcome Screen
	{

        glColor3f(0.3,0.56,0.84);   // background
        glBegin(GL_POLYGON);
        glVertex3f(-10.0,-10.0,0.0);
        glVertex3f(-10.0,10.0,0.0);
        glVertex3f(10.0,10.0,0.0);
        glVertex3f(10.0,-10.0,0.0);
        glEnd();

        glColor3f(0.137,0.137,0.556);
		glRectf(-8.0,-9.0,8.0,3.5);
		glColor3f(0.8,0.8,0.8);
		glRectf(-7.9,-8.9,7.9,3.4);

        glColor3f(0.196,0.196,0.8);   //restart button
        glRectf(-8.0,6.5,-4.0,8.0);
        glColor3f(0.8,0.8,0.8);
        glRectf(-7.8,6.7,-4.2,7.8);
        glColor3f(0.137,0.137,0.556);

        drawString(-7.3,7.0,0,GLUT_BITMAP_TIMES_ROMAN_24,"RESTART");
        drawString(-2.0,2.5,0,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER!!!");
        drawString(-4,-2.0,0,GLUT_BITMAP_HELVETICA_18,"SCORE :");
        drawString(-0.5,-2.0,0,GLUT_BITMAP_TIMES_ROMAN_24,sscore);


        drawString(-3,-7.0,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

        glutPostRedisplay();

	}
	else if (instflag == true)
	{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(-10.0,-10.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(-10.0,10.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(10.0,10.0,0.0);
		glVertex3f(10.0,-10.0,0.0);
		glEnd();
		//glPushMatrix();
		//glScalef(0.8,0.8,0);
		//drawJet();
		//glPopMatrix();
       // glPushMmatrix();
		glColor3f(0.196,0.196,0.8);
		glRectf(-9.5,8.0,-6.5,9.5);
		glColor3f(0.8,0.8,0.8);
		glRectf(-9.3,8.2,-6.7,9.3);

		glColor3f(0.137,0.137,0.556);
		drawString(-8.7,8.4,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		glRectf(-8.0,-9.0,8.0,7.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(-7.9,-8.9,7.9,6.9);


		glColor3f(0.137,0.137,0.556);
		drawString(-2.0,5.5,0,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");
		drawString(-6,4.0,0,GLUT_BITMAP_HELVETICA_18,"- Press (w) to move the aircraft upward");
		drawString(-6,3.0,0,GLUT_BITMAP_HELVETICA_18,"- Press (s) to move the aircraft downward");
		drawString(-6,2.0,0,GLUT_BITMAP_HELVETICA_18,"- Press (a) to move the aircraft backward");
		drawString(-6,1.0,0,GLUT_BITMAP_HELVETICA_18,"- Press (d) to move the aircraft forward");
		drawString(-6,-1.0,0,GLUT_BITMAP_HELVETICA_18,"-> RULES: ");
		drawString(-6,-2,0,GLUT_BITMAP_HELVETICA_18,"- Your aircraft has 3 lives");
		drawString(-6,-3.0,0,GLUT_BITMAP_HELVETICA_18,"- Whenever you let enemy come across you, you'll lose a life");
		drawString(-6,-4.0,0,GLUT_BITMAP_HELVETICA_18,"- Your score will increase 1 when your a bullet hits an enemy");
		drawString(-6,-5.0,0,GLUT_BITMAP_HELVETICA_18,"- Let's see how much score you can get ");
		drawString(-3,-7.0,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

		glutPostRedisplay();

	}
	else if (abtflag == true)
	{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(-10.0,-10.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(-10.0,10.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(10.0,10.0,0.0);
		glVertex3f(10.0,-10.0,0.0);
		glEnd();

		glColor3f(0.196,0.196,0.8);
		glRectf(-9.5,8.0,-6.5,9.5);
		glColor3f(0.8,0.8,0.8);
		glRectf(-9.3,8.2,-6.7,9.3);

		glColor3f(0.137,0.137,0.556);
		drawString(-8.7,8.4,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		glRectf(-8.0,-9.0,8.0,7.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(-7.9,-8.9,7.9,6.9);

		glColor3f(0.137,0.137,0.556);
		drawString(-1.0,5.5,0,GLUT_BITMAP_TIMES_ROMAN_24,"ABOUT");
		drawString(-6,3.0,0,GLUT_BITMAP_HELVETICA_18,"            COMPUTER GRAPHICS PROJECT BY ");
		drawString(-6,1.0,0,GLUT_BITMAP_HELVETICA_18,"            LOEM SOCHEANET        2K19/IT/073 ");

		drawString(-3.0,-7.0,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");
		glutPostRedisplay();

	}
	else if(start == true){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BITS) ;
    glLoadIdentity();


    drawBg();
  //  drawJet();
    building1();
    building2();
    building3();
    building4();
     bullet();
     enemy();
     enemy1();
    printScore();
    printLives();
    drawAirCraft();
    building5();

//    drawString();


   // moveJet();
    moveBullet();
    moveBuilding();
    moveEnemey();
    gameEndStatus=false;
	}
    glFlush();
    glutSwapBuffers();

}

void init(){
    glClearColor(0.0,0.0,0.0,1.0);

}
void reshape(int w, int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW);
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
}

void key(unsigned char ch, int px, int py){
    switch(ch){
        case 'd'|'D':
            if(x_position<9){
                x_position = x_position + 0.40;
            }
            else{
                x_position = x_position + 0.0;
            }
            break;
        case 'a'|'A':
            if(x_position>-9)
                x_position-= 0.40;
            else
                x_position-=0.0;
            break;
        case 'w'| 'W':
            if(y_position<10)
                y_position += 1.40;
            else
                y_position+=0.0;
            break;
        case 's' | 'S':
            if(y_position>-9)
                y_position-= 1.40;
            else
                y_position-=0.0;
            break;
        case 'C' |'c':
                if(y_position>-9)
                    y_position-=5;
                else
                    y_position-=0.0;
                break;
        case 'T' | 't':
                if(y_position <10)
                    y_position +=5;
                else
                    y_position +=0.0;
                break;
    }
}


void mouse(int button, int state, int x, int y)            // takes input from mouse
{
    int mx=x*100/SCREENW,my=(SCREENH-y)*100/SCREENH;		// m = mouse cordinate to graphics
	/*		mouse calculation//converting to screen coordinates-ortho values */


    if(instflag || abtflag || gameEndStatus)
	{
		if(mx>0 && mx<40)
		{
			if(my>80 && my<100)
			{
				wflag = true;
				if(instflag)
					instflag = false;
				else if (abtflag)
					abtflag = false;
				if(gameEndStatus)
				{
					wflag = true;
					gameEndStatus = false;

					init();

					score=0;
					lives=0;
                    start = true;
					glutPostRedisplay();
				}


			}
		}
	}


	if(wflag == true)
	{
	    if(mx>30 && mx< 55)
        {
            if(my>70&& my<80)
			{
				start = true;
				wflag=false;
				gameEndStatus=false;
            }

			else if(my> 60 && my<69)
			{
				instflag = true;
				wflag = false;
			}
			else if(my>50 && my<59)
			{
				abtflag = true;
				wflag = false;
			}
			else if( my>40 && my<49)
			{
			    exit(0);

			}
        }
    }
}




