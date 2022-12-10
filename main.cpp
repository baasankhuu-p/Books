#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#define COL 40
#define ROW 40
#define MAX 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

int gridX, gridY;
int length_inc=0;
int seedflag = 0;
int score;
int game_over;
int food=0;
int row=0,col=0;
int sDirection = RIGHT;
int foodx,foody;
int posx[MAX+1]={4,3,2,1,0,-1,-1};
int posy[MAX+1]={10,10,10,10,10,10,10};
int length=7;

void initGrid(int x,int y)
{
    col=x;
    row=y;
}
void unit(int x,int y)
{
    glLoadIdentity();
    if(x==0||x==col-1||y==0||y==row-1)
    {
        glColor3f(0.5,0.2,0.9);
        glLineWidth(1.0);
    }
    else
    {
        glColor3f(0.8,0.8,0.8);
        glLineWidth(0.0);
    }
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(x,y); glVertex2d(x+1,y);
        glVertex2d(x+1,y); glVertex2d(x+1,y+1);
        glVertex2d(x+1,y+1); glVertex2d(x,y+1);
        glVertex2d(x,y+1); glVertex2d(x,y);
    glEnd();
}

void d_grid(){
    int i,j;
    i =0;
    while(i<col){
        j=0;
        while(j<row){
            unit(i,j);
            j++;
        }
        i++;
    }
}


void d_snake()
{
    int i =length-1;
    while(i>0)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
        i--;
    }
    i=0;
    while(i<length)
    {
        glColor3f(0.5,0.3,0.5);
        if(i==0)
        {
            glColor3f(0.5,0.2,0.9);
            switch(sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            if(posx[i]==0||posx[i]==col-1||posy[i]==0||posy[i]==row-1)
                game_over=1;
            else if(posx[i]==foodx && posy[i]==foody)
            {
                food=0;
                score++;
                if(length<=MAX)
                    length_inc=1;
            }
            for(int j=1;j<length;j+=1)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=1;
            }
        }
        glBegin(GL_QUADS);
            glVertex2d(posx[i],posy[i]);
            glVertex2d(posx[i]+1,posy[i]);
            glVertex2d(posx[i]+1,posy[i]+1);
            glVertex2d(posx[i],posy[i]+1);
        glEnd();
        i++;
    }
    if(length_inc)
    {
        length++;
        length_inc=0;
    }
}
int random(int _min,int _max)
{
    if(!seedflag)
    {
        srand(time(NULL));
        seedflag=1;
    }
    else
        seedflag=0;
    return _min+rand()%(_max-_min);
}

void d_food()
{
    if(!food)
    {
        fx=random(2,col-2);
        foody=random(2,row-2);
        food=1;
    }
    glBegin(GL_TRIANGLE_FAN);
       glVertex2d(foodx,foody);
       glVertex2d(foodx+1,foody);
       glVertex2d(foodx+1,foody+1);
       glVertex2d(foodx,foody+1);
    glEnd();
}



void init()
{
    glClearColor(0.6,0.6,0.8,0.8);
    initGrid(COL,ROW);
}

//Callbacks
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    d_grid();
    d_food();
    d_snake();
    glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLfloat)w,GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COL,0.0,ROW,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int t)
{
    glutPostRedisplay();
    glutTimerFunc(1000,timer_callback,1000);
}
void input_callback(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}


int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(8,8);
    glutInitWindowSize(500,500);
    glutCreateWindow("Datastructure");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(1000, timer_callback, 1000);
    init();
    glutMainLoop();
    return 0;
}
