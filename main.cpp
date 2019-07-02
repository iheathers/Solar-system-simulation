#include <GL\glut.h>
#include <math.h>

GLfloat yRotated=1;
GLfloat movement = 0;

void drawCircle(float r) { // r = radius

    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++)
        {
         double angle = 2 * 3.14 * i/300;
         double x = r*cos(angle);
         double y = r*sin(angle);
         glVertex3d(x, y, -5.5);
        }
    glEnd();
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, -8, 0, 1, 0); // 3rd coordinate - depth

    float radius1 = 6;
    float radius2 = 1;

    //first orbit
    //first orbit glColor3f(1, 1, 1); glPushMatrix(); glTranslatef(0, 0, 0); drawCircle(radius1/2);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawCircle(radius1/2);
    glPopMatrix();

    //second orbit with rotation
    glColor3f(1, 1, 1);
    glPushMatrix();
    glRotatef(yRotated, 0, 0, 1);
    glPushMatrix();
    glTranslatef(radius1/2, 0, 0);
    drawCircle(radius2);
    glPopMatrix();
    glPopMatrix();

    //Sun
    glColor3f(1, 0.2, 0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.5);
// glScalef(1.0, 1.0, 1.0);
    glRotatef(yRotated, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glutSolidSphere(1,20,20);

    //earth
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(radius1/2, 0, 0);
    glRotatef(yRotated, 0, 1, 0);
    glutSolidSphere(0.5, 20, 20);

    //moon
    glPushMatrix();
    glTranslatef(radius2, 0, 0);
    glColor3f(1, 1, 1);
    glRotatef(yRotated, 0, 1, 0);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    //second czajnik pop
    glPopMatrix();

    //first czajnik pop
    glPopMatrix();

    glFlush();
}

void idle()
 {
     yRotated += 0.1;
     Sleep(2);
     display();
}

void myReshape(int w, int h) {

    if (w == 0 || h == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, (GLdouble)w/(GLdouble)h, 0.5, 20.0);

    glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Solar system");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0, 0, 0, 1.0);
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
