#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846

// Global variables for angles and scaling factors
float angleMoon = 0.0, angleEarth = 0.0, angleAstroid = 0.0,
      angleMars = 0.0,
      angleMercury = 0.0,
      angleVenus = 0.0,
      angleJupiter = 0.0,
      angleSaturn = 0.0,
      angleUranus = 30.0,
      angleNeptune = 60.0;
GLfloat sx = 0.2, sy = 0.2, sz = 0.2;  // Scaling factors
int planet1;

// Array definitions for colors
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat blue[] = {0.0f, 0.0f, 0.9f, 1.0f};
GLfloat er[] = {0.0f, 5.0f, 0.9f, 1.0f};
GLfloat yellow[] = {0.7f, 0.2f, 0.0f, 1.0f};

// Light properties
GLfloat qAmb[] = {0.1, 0.1, 0.1, 1.0};
GLfloat qDif[] = {1.0, 1.0, 1.0, 1.0};
GLfloat qSpec[] = {0.50, 0.50, 0.50, 0.10};
GLfloat qPos[] = {0, 0, 0, 0.1};

// Scaling factors for planets
GLfloat sc[8] = {0.295, 0.40, 0.50, 0.60, 0.80, 1.0, 1.05, 1.13};

// Angular increments for drawing
double ang = 2 * PI / 300;
double angular = 2 * PI / 50;

// Function prototypes
void initLighting();
void myinit();
void background();
void orbit();
void draw(void);
void update(int value);

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set display mode to use single buffer, RGB color, and enable depth buffering
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    // Set initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 700);

    // Create a window with the specified title
    glutCreateWindow("Solar System");

    // Initialize lighting for the scene
    initLighting();

    // Perform additional initialization (background color, shading model, etc.)
    myinit();

    // Register the display function to be called when a render is required
    glutDisplayFunc(draw);

    // Set up a timer to call the update function for animation after a specified interval (25 milliseconds)
    glutTimerFunc(25, update, 0);

    // Enter the GLUT event processing loop
    glutMainLoop();

    // Return 0 to indicate successful completion
    return 0;
}

// Function to initialize lighting for the scene
void initLighting() {
    // Enable OpenGL lighting
    glEnable(GL_LIGHTING);

    // Enable light source 0 (Sunlight)
    glEnable(GL_LIGHT0);

    // Enable light source 1 (Ambient light)
    glEnable(GL_LIGHT1);

    // Define properties for light source 0 (Sunlight)
    GLfloat light0_ambient[] = {0.0, 0.0, 0.0, 1.0};  // Ambient color
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};  // Diffuse color
    GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0}; // Specular color
    GLfloat light0_position[] = {0.0, 0.0, 0.0, 1.0}; // Position (directional light)

    // Set properties for light source 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    // Define properties for light source 1 (Ambient light)
    GLfloat light1_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Ambient color
    GLfloat light1_diffuse[] = {0.5, 0.5, 0.5, 1.0};  // Diffuse color
    GLfloat light1_specular[] = {0.5, 0.5, 0.5, 1.0}; // Specular color

    // Set properties for light source 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
}
// Function to initialize OpenGL settings
void myinit() {
    // Set the clear color (background) to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth testing for accurate rendering of overlapping objects
    glEnable(GL_DEPTH_TEST);

    // Set shading model to smooth for smooth color transitions
    glShadeModel(GL_SMOOTH);

    // Enable anti-aliasing for lines and polygons
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    // Set hint for the line smoothing algorithm to use the highest quality
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Set hint for the polygon smoothing algorithm to use the highest quality
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}
// Function to draw the background of the scene
void background() {
    // Begin drawing a quadrilateral (rectangle) for the background
    glBegin(GL_QUADS);

    // Set color for the first vertex (top-left)
    glColor3f(0.0, 0.00, 0.00);
    // Define the first vertex coordinates
    glVertex3f(-1.00, 1.00, 1);

    // Set color for the second vertex (top-right)
    glColor3f(0.20, 0.0, 0.70);
    // Define the second vertex coordinates
    glVertex3f(1.00, 1.00, 1);

    // Set color for the third vertex (bottom-right)
    glColor3f(0, 0.0, 0.0);
    // Define the third vertex coordinates
    glVertex3f(1.00, -1.00, 1);

    // Set color for the fourth vertex (bottom-left)
    glColor3f(0.70, 0.10, 0.20);
    // Define the fourth vertex coordinates
    glVertex3f(-1.00, -1.00, 1);

    // End the drawing of the quadrilateral
    glEnd();
}
// Function to draw orbits for celestial bodies
void orbit() {
    // Set the color for drawing orbits to light gray
    glColor3f(0.5, 0.5, 0.5);

    // Loop through orbits for different celestial bodies
    for (int i = 0; i < 8; i++) {
        // Save the current transformation state
        glPushMatrix();

        // Adjust the inclination of the orbit for specific cases
        if (i == 5) {
            glRotatef(45, 1.0, 0.0, 0.0); // Inclination for the sixth orbit
        } else {
            glRotatef(63, 1.0, 0.0, 0.0); // Default inclination for other orbits
        }

        // Scale the orbit based on the defined scaling factors
        glScalef(sc[i], sc[i], sc[i]);

        // Begin drawing points to represent the orbit
        glBegin(GL_POINTS);

        // Loop through points on the orbit
        double ang1 = 0.0;
        for (int i = 0; i < 300; i++) {
            // Calculate and draw each point on the orbit using polar coordinates
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += ang; // Increment the angle for the next point
        }

        // End drawing the points
        glEnd();

        // Restore the previous transformation state
        glPopMatrix();
    }
}
// Function to draw the entire solar system
void draw(void)
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the background and orbits
    background();
    orbit();

    // Load the identity matrix and apply transformations
    glLoadIdentity();
    glPushMatrix();

    // Enable depth testing and color material
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    // Draw the Sun
    glPushMatrix();
    glColor3f(0.7, 0.5, 0.0);
    glScalef(sx, sy, sz);
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glutSolidSphere(1, 50, 50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();

    // Draw Mercury
    glScalef(0.2, 0.2, 0.2);
    glPushMatrix();
    glRotatef(angleMercury, 0.0, 1.0, -0.5);
    glTranslatef(1.5, 0.0, 0.0);
    glColor3f(1.0, 0.9, 0.0);
    glScalef(0.08, 0.08, 0.08);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    // Draw Venus
    glPushMatrix();
    glRotatef(angleVenus, 0.0, 1.0, -0.5);
    glTranslatef(2.0, 0.0, 0.0);
    glColor3f(0.9, 0.1, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    // Draw Earth and Moon
    glPushMatrix();
    glRotatef(angleEarth, 0.0, 1.0, -0.5);
    glTranslatef(2.5, 0.0, 0.0);
    glColor3f(0.0, 0.1, 0.7);
    glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(1, 50, 50);

    // Draw the Moon
    glPushMatrix();
    glRotatef(angleMoon, 0.0, 0.1, 0.05);
    glTranslatef(1.3, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix(); // Moon made
    glPopMatrix(); // Earth made

    // Draw Mars
    glPushMatrix();
    glRotatef(angleMars, 0.0, 1.0, -0.5);
    glTranslatef(-3.0, 0.0, 0.0);
    glColor3f(0.05, 0.05, 0.01);
    glScalef(0.17, 0.17, 0.17);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    // Draw the Asteroid Belt
    glPushMatrix();
    glColor3f(3.30, 3.30, 3.30);
    glRotatef(63, 1.0, 0.0, 0.0);
    int j = 0, i = 0, div = 90;
    float siz = 2;
    float scl[4] = {3.3, 3.4, 3.35, 3.2};
    for (j = 0; j < 4; j++)
    {
        glPushMatrix();
        siz -= 0.3;
        glPointSize(siz);
        glScalef(scl[j], scl[j], scl[j]);
        glBegin(GL_POINTS);
        double ang1 = 0.0 - angleAstroid, a = (2 * PI) / div;
        for (i = 0; i < div; i++)
        {
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += a;
        }
        div += 10;
        glEnd();
        glPopMatrix();
    }
    glPopMatrix(); // Asteroid Belt made

    // Draw Jupiter and Moon
    glPushMatrix();
    glRotatef(angleJupiter, 0.0, 1.0, -0.5);
    glTranslatef(-4.0, 0.0, 0.0);
    glColor3f(0.4, 0.2, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(1, 50, 50);

    // Draw Jupiter's Moon
    glPushMatrix();
    glRotatef(angleMoon, 1.0, -0.5, 0.0);
    glTranslatef(0.0, 0, 1.1);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix(); // Moon made
    glPopMatrix(); // Jupiter made

    // Draw Saturn and Ring
    glPushMatrix();
    glRotatef(angleSaturn, 0.0, 1.0, -1.0);
    glTranslatef(-5.0, 0.0, 0.0);
    glColor3f(0.9, 0.0, 0.0);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(1, 50, 50);

    // Draw Saturn's Ring
    glPushMatrix();
    glRotatef(45, 1.0, 0.0, 0.0);
    glPointSize(3);
    glColor3f(5.0, 3.0, 1.0);
    glScalef(1.2, 1.2, 1.2);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    i = 0;
    for (i = 0; i < 50; i++)
    {
        glVertex2d(cos(ang1), sin(ang1));
        ang1 += angular;
    }
    glEnd();

    glPointSize(2);
    glPopMatrix(); // Ring made
    glPopMatrix(); // Saturn made

    // Draw Uranus
    glPushMatrix();
    glRotatef(angleUranus, 0.0, 1.0, -0.5);
    glTranslatef(5.2, 0.0, 0.0);
    glColor3f(0.0, 0.5, 0.9);
    glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    // Draw Neptune
    glPushMatrix();
    glRotatef(angleNeptune, 0.0, 1.0, -0.5);
    glTranslatef(-5.7, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.9);
    glScalef(0.2, 0.2, 0.2);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    // Restore the transformation state
    glPopMatrix();

    // Flush the rendering pipeline
    glFlush();
}
// Function to update the angles and scales for animation
void update(int value)
{
    // Update scaling factors based on the Moon's angle
    if ((angleMoon >= 0 && angleMoon < 180))
    {
        sx -= 0.0003;
        sy -= 0.0003;
        sz -= 0.0003;
    }
    else
    {
        sx += 0.0003;
        sy += 0.0003;
        sz += 0.0003;
    }

    // Increment angles for rotation of celestial bodies
    angleMoon += 2;
    if (angleMoon > 360)
    {
        angleMoon -= 360;
    }

    angleEarth += 0.7;
    if (angleEarth > 360)
    {
        angleEarth -= 360;
    }

    angleMercury += 2;
    if (angleMercury > 360)
    {
        angleMercury -= 360;
    }

    angleVenus += 0.9;
    if (angleVenus > 360)
    {
        angleVenus -= 360;
    }

    angleMars += 0.5;
    if (angleMars > 360)
    {
        angleMars -= 360;
    }

    angleJupiter += 0.2;
    if (angleJupiter > 360)
    {
        angleJupiter -= 360;
    }

    angleSaturn += 0.1;
    if (angleSaturn > 360)
    {
        angleSaturn -= 360;
    }

    angleUranus += 0.05;
    if (angleUranus > 360)
    {
        angleUranus -= 360;
    }

    angleNeptune += 0.02;
    if (angleNeptune > 360)
    {
        angleNeptune -= 360;
    }

    angleAstroid += 0.002;
    if (angleAstroid > 360)
    {
        angleAstroid -= 360;
    }

    // Request a redisplay to update the animation
    glutPostRedisplay();

    // Set up a timer to call the update function after a specified interval (20 milliseconds in this case)
    glutTimerFunc(20, update, 0);
}

