#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>

using namespace std;

float ballX = -0.3f; //set circle position
float ballY = 0.0f; //set circle position
float ballZ = -1.0f;    //set circle position

static int flag=1;

void drawBall(void) { //function to set the circle colour and define the circle size

        glColor3f(0.0, 1.0, 0.0); //set circle color
        glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (0.1, 10, 10); //create circle.

}

void keyPress(int key, int x, int y) // function to call whenever a key is pressed
{
      if(key==GLUT_KEY_RIGHT) //for right arrow key the circle will move behind x axis
        ballX -= 0.05f;
    if(key==GLUT_KEY_LEFT)
        ballX  += 0.05f; //for left arrow key the circle will move forward x axis

    glutPostRedisplay();
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void drawScene() //the function that draws the circle
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear the screen and depth buffer

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    drawBall();
    //drawBall2();

    glutSwapBuffers();
}

void update(int value) { // this function sets the circle speed
    if(flag)
    {
    ballX += 0.001f;
       if(ballX>0.3)
       {
           flag=0;

       }
    }
    if (!flag)
    {
        ballX -= 0.001f;
        if(ballX<-0.3)
       {
           flag=1;

       }
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}

int main(int argc,char** argv) //this function sets the window size window position and addresses all the functions used in the program
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(400,400);

    glutCreateWindow("Moving Circle");

    glutDisplayFunc(drawScene);

    glutSpecialFunc(keyPress);
    glutReshapeFunc(handleResize);
    //autorot();

    glutTimerFunc(25, update, 0);

    glutMainLoop();

    return(0);
}
//End of the project
