/************************************************************************************

File: 			main.cpp

Description:	The Hitch Hiker’s Guide to the Planets

Author:			Zihao Wu

*************************************************************************************/

/* include the library header files */
#include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

/* Variables for controlling Enterprise movement */
GLfloat enterpriseSpeed = 0.2;
GLint upEnable = 0, downEnable = 0,
leftEnable = 0, rightEnable = 0,
forwardEnable = 0, backwardEnable = 0;
GLfloat moveTheShip = 0.0, XPosition = 0.0, YPosition = 0.0, ZPosition = 0.0;
GLint forwardDirection = -1, backwardDirection = 1,
upwardDirection = 1, downwardDirection = -1,
leftwardDirection = -1, rightwardDirection = 1;

/* Data structure for the generation of Enterprise */
typedef GLfloat enterprise[1202];
typedef GLint enterprisef[1990];
typedef GLint testArray[20];
testArray tA = {};
enterprise epX = {};
enterprise epY = {};
enterprise epZ = {};
enterprisef epfX = {};
enterprisef epfY = {};
enterprisef epfZ = {};
GLint countFile = 0;
GLint countFace = 0;
GLfloat cloak = 1.0, cloakEnable = 0.0;
GLint cloakPressCount = 0;

/* Data structure for generating stars at random location */
typedef GLfloat star2[5000];
typedef GLfloat starL[400];
star2 randomX = {};
star2 randomY = {};
star2 randomZ = {};
starL lX = {};
starL lY = {};
starL lZ = {};

/* Camera position */
GLfloat cameraPosition[] = { 0.0, 0.1, 1.0 };

/* The ratio of the circumference to the diameter of a circle */
#define PI 3.14159265

/* Conversion multiplier for converting from degrees to Radians */
#define DEG_TO_RAD PI/180.0

/* Rotation parameter */
GLfloat rototating = 360.0;

/* Check if ring is enable */
GLfloat ringEnable = 1.0;
GLint ringPressCount = 0;

/* Variables related to stars */
GLfloat starX, starY, starZ, starXL, starYL, starZL, starColorR,
starColorG, starColorB, lightSpeed = 0.0;
GLint starNum = 0, starNumL = 0, starEnable = 0, starPressCount = 0,
pointSize = 0, lightSpeedEnable = 0, lightPressCount = 0, destination = 0;

/* Variables for the Corona */
GLfloat cnX, cnY, cnXM, cnYM;
GLint cnNum = 0, cnEnable = 1, cnPressCount = 0;

/* Variables for the shield */
GLfloat shieldEnable = 1.0;
GLint shieldPressCount = 0;

/* Variables for Enterprise weapons */
GLfloat laserPower;
GLint fireEnable = 0;

/************************************************************************

Function:		keyFunction

Description:	Check which key was pressed and then perform specific
functions to animate the solar system.

*************************************************************************/
void keyFunction(unsigned char key, int x, int y){
	/* Press R key to enable the rings around planets */
	if (key == 'r') {
		ringPressCount += 1;
		if (ringPressCount % 2 == 0)
			ringEnable = 1.0;
		else
			ringEnable = 0.0;
	}

	/* Press S key to enable the stars on the universe */
	if (key == 's') {
		starPressCount += 1;
		if (starPressCount % 2 == 0)
			starEnable = 0;
		else
			starEnable = 1;
	}

	/* Press S key to enable the sun's corona */
	if (key == 'c') {
		cnPressCount += 1;
		if (cnPressCount % 2 == 0)
			cnEnable = 1;
		else
			cnEnable = 0;
	}

	/* Press K key to enable the shield */
	if (key == 'k') {
		shieldPressCount += 1;
		if (shieldPressCount % 2 == 0)
			shieldEnable = 1;
		else
			shieldEnable = 0;
	}

	/* Press L key to enable lightSpeed travel */
	if (key == 'l') {
		lightPressCount += 1;
		if (lightPressCount % 2 == 0){
			lightSpeedEnable = 0;
			destination += 1;
		}
		else
			lightSpeedEnable = 1;
	}

	/* Press F key to fire on the Enterprise */
	if (key == 'f'){
		laserPower = 0.0;
		fireEnable = 1;
	}

	/* Press E key to cloak the Enterprise */
	if (key == 'e'){
		cloakPressCount += 1;
		if (cloakPressCount % 2 == 0)
			cloakEnable = 0.0;
		else
			cloakEnable = 1.0;
	}
}

/************************************************************************

Function:		keyForEnterprise

Description:	Key event for enterprise movement using arrow keys

*************************************************************************/
void keyForEnterprise(int key, int x, int y) {
	if (lightSpeedEnable == 0){
		if (key == GLUT_KEY_PAGE_UP){
			forwardEnable = 1;
			backwardDirection = 0;
			forwardDirection = -1;
		}
		if (key == GLUT_KEY_PAGE_DOWN){
			backwardEnable = 1;
			forwardDirection = 0;
			backwardDirection = 1;
		}
		if (key == GLUT_KEY_UP){
			upEnable = 1;
			downwardDirection = 0;
			upwardDirection = 1;
		}
		if (key == GLUT_KEY_DOWN){
			downEnable = 1;
			upwardDirection = 0;
			downwardDirection = -1;
		}
		if (key == GLUT_KEY_LEFT){
			leftEnable = 1;
			rightwardDirection = 0;
			leftwardDirection = -1;
		}
		if (key == GLUT_KEY_RIGHT){
			rightEnable = 1;
			leftwardDirection = 0;
			rightwardDirection = 1;
		}
	}
}

/************************************************************************

Function:		keyUpEnterprise

Description:	Key release event for enterprise movement using arrow keys

*************************************************************************/
void keyUpEnterprise(int key, int x, int y){
	if (lightSpeedEnable == 0){
		if (key == GLUT_KEY_PAGE_UP){
			forwardEnable = 0;
			forwardDirection = 0;

		}
		if (key == GLUT_KEY_PAGE_DOWN){
			backwardEnable = 0;
			backwardDirection = 0;
		}
		if (key == GLUT_KEY_UP){
			upEnable = 0;
			upwardDirection = 0;

		}
		if (key == GLUT_KEY_DOWN){
			downEnable = 0;
			downwardDirection = 0;
		}
		if (key == GLUT_KEY_LEFT){
			leftEnable = 0;
			leftwardDirection = 0;

		}
		if (key == GLUT_KEY_RIGHT){
			rightEnable = 0;
			rightwardDirection = 0;
		}
	}
}

/************************************************************************

Function:		spinPlanet

Description:	Rotate the planet around the sun

*************************************************************************/
void spinPlanet(void)
{
	/* Control weapon system */
	laserPower += 1.0;

	/* Control lightspeed travel */
	lightSpeed += 0.01;
	if (lightSpeed > 1.0)
		lightSpeed -= 1.0;

	/* To control cloak of the ship */
	if (cloakEnable == 1.0)
		cloak -= 0.01;
	else
		cloak += 0.01;

	if (cloak < 0.05)
		cloak = 0.05;

	if (cloak > 1.0)
		cloak = 1.0;

	/* Move the starship */
	if (forwardEnable == 1 || backwardEnable == 1 || upEnable == 1 || downEnable == 1 || leftEnable == 1 || rightEnable == 1){
		moveTheShip = 0.5;
	}

	/* Rotate the planet around the sun */
	rototating -= 0.12;

	/* If we reach 0, rotate from 360 again */
	if (rototating < 0.0)
		rototating += 360;

	/* Random colors for the stars */
	starColorR = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));
	starColorG = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));
	starColorB = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));

	/* Now force OpenGL to redraw the change */
	glutPostRedisplay();
}

/************************************************************************

Function:		planet

Description:	Draw a planet and its orbit

*************************************************************************/
void planet(GLfloat planetSize, GLfloat orbit, GLfloat redC, GLfloat greenC, GLfloat blueC, GLfloat orbitSpeed){
	/* Convert hexidecimal colors to floats */
	redC = redC / 255.0;
	greenC = greenC / 255.0;
	blueC = blueC / 255.0;

	/* Draw the orbit */
	if (ringEnable == 0){
		glLineWidth(1.0f);
		glBegin(GL_LINE_LOOP);
		glColor4f(1.0, 1.0, 1.0, 1.0 - ringEnable);
		for (GLdouble i = 0; i <= 360; i++){
			GLfloat degInRad = i * DEG_TO_RAD;
			glVertex3f(cos(degInRad)*orbit, 0.0, sin(degInRad)*orbit);
		}
		glEnd();
	}

	/* Draw the planet */
	GLUquadric *quad;
	quad = gluNewQuadric();
	glColor3f(redC, greenC, blueC);
	glTranslatef(cos(DEG_TO_RAD * rototating * orbitSpeed)*orbit, 0.0, sin(DEG_TO_RAD * rototating * orbitSpeed)*orbit);
	gluSphere(quad, planetSize, 100, 20);
}

/************************************************************************

Function:		stars

Description:	Create a single star

*************************************************************************/
void stars(GLfloat x, GLfloat y, GLfloat z, GLint currentS){
	/* Flashing effect for a star */
	GLfloat line_1_x = 0.0, line_2_x = 0.0,
		line_3_x = 0.0, line_4_x = 0.0,
		line_1_y = 0.0, line_2_y = 0.0,
		line_3_y = 0.0, line_4_y = 0.0,
		line_1_z = 0.0, line_2_z = 0.0,
		line_3_z = 0.0, line_4_z = 0.0;
	GLfloat starLength = 0.0;

	starLength = 0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.2));
	if (currentS % 25 == 0){
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		line_1_x = x + starLength;
		line_1_y = y + starLength;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(x, y, z);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glVertex3f(line_1_x, line_1_y, z);
		glEnd();

		glBegin(GL_LINES);
		line_2_x = x + starLength;
		line_2_y = y - starLength;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(x, y, z);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glVertex3f(line_2_x, line_2_y, z);
		glEnd();

		glBegin(GL_LINES);
		line_3_x = x - starLength;
		line_3_y = y + starLength;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(x, y, z);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glVertex3f(line_3_x, line_3_y, z);
		glEnd();

		glBegin(GL_LINES);
		line_4_x = x - starLength;
		line_4_y = y - starLength;
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(x, y, z);
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glVertex3f(line_4_x, line_4_y, z);
		glEnd();
	}

	/* Generate a star */
	pointSize = 1 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / 2));
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glColor4f(0.0 + starColorR, 0.0 + starColorG, 0.0 + starColorB, 0.0 + starEnable);
	glVertex3f(x, y, z);
	glEnd();
}

/************************************************************************

Function:		lightSpeedTravel

Description:	Create lightspeed travel effect

*************************************************************************/
void lightSpeedTravel(){
	if (lightSpeedEnable == 1){
		if (starNumL < 400){
			for (starNumL = 0; starNumL < 400; starNumL++) {
				starXL = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));
				starYL = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));
				starZL = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));
				lX[starNumL] = { starXL };
				lY[starNumL] = { starYL };
				lZ[starNumL] = { starZL };
			}
		}
		else{
			for (int i = 0; i < starNumL; i++){
				glPushMatrix();
				/* Lightspeed travel */
				glLineWidth(3.0f);
				glBegin(GL_LINES);
				glColor4f(173.0 / 255.0, 235.0 / 255.0, 235.0 / 255.0, 1.0 - lightSpeed);
				glVertex3f(lX[i], lY[i], lZ[i] - 10.0);
				glColor4f(173.0 / 255.0, 235.0 / 255.0, 235.0 / 255.0, 0.0 + lightSpeed);
				glVertex3f(0.0, 0.0, 0.0);
				glEnd();
				glPopMatrix();
			}
		}
	}
}

/************************************************************************

Function:		drawStars

Description:	Draw stars on the screen.

*************************************************************************/
void drawStars(){
	if (starEnable == 1){
		if (starNum < 5000){
			for (starNum = 0; starNum < 5000; starNum++) {
				/* Compute star position randomly */
				starX = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));
				starY = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));
				starZ = -30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0));

				randomX[starNum] = { starX };
				randomY[starNum] = { starY };
				randomZ[starNum] = { starZ };
			}
		}
		else{
			for (int i = 0; i < starNum; i++){
				glPushMatrix();
				stars(randomX[i], randomY[i], randomZ[i] - 20.0, i);
				glPopMatrix();
			}
		}
	}
}

/************************************************************************

Function:		corona

Description:	Sun's corona function

*************************************************************************/
void corona(){
	for (cnNum = 0; cnNum < 360; cnNum++) {

		GLfloat degInRadC = cnNum * DEG_TO_RAD;
		glVertex3f(cos(degInRadC), 0.0, sin(degInRadC));

		/* Compute random direction of sun's corona*/
		cnX = -0.25 * cos(degInRadC) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 * cos(degInRadC))));
		cnY = -0.25 * sin(degInRadC) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.5 * sin(degInRadC))));
		cnXM = -0.4 * cos(degInRadC) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8 * cos(degInRadC))));
		cnYM = -0.4 * sin(degInRadC) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8 * sin(degInRadC))));

		/* Draw corona effect*/
		if (cnEnable == 0){
			glPushMatrix();
			glLineWidth(3.0f);
			glBegin(GL_LINES);
			glColor4f(244.0 / 255.0, 241.0 / 255.0, 66.0 / 255.0, 1.0);
			glVertex3f(cnX, cnY, 0);
			glColor4f(244.0 / 255.0, 241.0 / 255.0, 66.0 / 255.0, 0.0);
			glVertex3f(cnXM, cnYM, 0);
			glEnd();
			glPopMatrix();
		}
	}
}

/*****************************************************************************

Function:		ussEnterprise

Description:	USS Enterprise NCC-1701 form Star Trek, Captain Kirk on board.

******************************************************************************/
void ussEnterprise(){
	int countThis = 0;
	GLfloat eC = 0.0, enColor = 0.0;
	for (int i = 1; i < ((sizeof(epfX) / sizeof(*epfX))); i = i + 1){
		countThis += 1;

		/* Change color of each triangle */
		eC += 1.0;
		enColor = eC / 1989.0;

		/* Generate triangles*/
		glPushMatrix();
		glBegin(GL_POLYGON);
		glColor4f(enColor, enColor, enColor, cloak);
		glVertex3f(epX[epfX[i]], epY[epfX[i]], epZ[epfX[i]]);
		glColor4f(enColor, enColor, enColor, cloak);
		glVertex3f(epX[epfY[i]], epY[epfY[i]], epZ[epfY[i]]);
		glColor4f(enColor, enColor, enColor, cloak);
		glVertex3f(epX[epfZ[i]], epY[epfZ[i]], epZ[epfZ[i]]);
		glEnd();
		glPopMatrix();
	}
}

/************************************************************************

Function:		Shield

Description:	Shield generation for the Enterprise.

*************************************************************************/
void shield(){
	if (shieldEnable == 0){
		glPushMatrix();
		GLUquadric *quad;
		quad = gluNewQuadric();
		glColor4f(0.0 + starColorR, 0.0 + starColorG, 0.0 + starColorB, 0.3);
		glTranslatef(epX[epfX[500]], epY[epfX[500]] + 0.1, epZ[epfX[500]]);
		glScalef(1.5, 1.5, 2.5);
		gluSphere(quad, 0.3, 100, 20);
		glPopMatrix();
	}
}

/************************************************************************

Function:		planetRing

Description:	to constrcut planet rings in details.

*************************************************************************/
void planetRing(GLfloat redC, GLfloat greenC, GLfloat blueC, GLfloat lineW, GLfloat ringW){
	redC = redC / 255.0;
	greenC = greenC / 255.0;
	blueC = blueC / 255.0;

	glPushMatrix();
	glLineWidth(lineW);
	glBegin(GL_LINE_LOOP);
	glColor4f(redC, greenC, blueC, 0.6);
	for (GLdouble i = 0; i <= 360; i++){
		GLfloat degInRad = i * DEG_TO_RAD;
		glVertex3f(cos(degInRad)*ringW, 0.0, sin(degInRad)*ringW);
	}
	glEnd();
	glPopMatrix();
}

/************************************************************************

Function:		firing

Description:	to fire on the Enterprise.

*************************************************************************/
void firing(GLint pos){
	glPushMatrix();
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor4f(173.0 / 255.0, 235.0 / 255.0, 235.0 / 255.0, 1.0);
	glVertex3f(epX[epfX[pos]], epY[epfX[pos]], epZ[epfX[pos]] - laserPower);
	glColor4f(173.0 / 255.0, 235.0 / 255.0, 235.0 / 255.0, 1.0);
	glVertex3f(epX[epfX[pos]], epY[epfX[pos]], epZ[epfX[pos]] - 1.0 - laserPower);
	glEnd();
	glPopMatrix();
}

/************************************************************************

Function:		solarSystem

Description:	Display callback, clears frame buffer and depth buffer,
draw the solar systems and the USS Enterprise.

*************************************************************************/
void solarSystem(void)
{
	/* clear the screen and depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* load the identity matrix into the model view matrix */
	glLoadIdentity();

	/* Set the camera position */
	gluLookAt(0.0 + XPosition, 1.0 + YPosition, 4.0 + ZPosition,
		epX[epfX[500]] + XPosition, epY[epfX[500]] + YPosition, epZ[epfX[500]] + ZPosition,
		0.0, 1.0, 0.0);

	if (lightSpeedEnable == 0){
		if (destination % 2 == 0){
			/* Draw the Sun */
			glPushMatrix();
			planet(0.25, 0.0, 244.0, 241.0, 66.0, 0.0);
			glPopMatrix();

			/* Draw the Mercury */
			glPushMatrix();
			planet(0.03, 0.5, 244.0, 134.0, 66.0, 9.0);
			glPopMatrix();

			/* Draw the Venus */
			glPushMatrix();
			planet(0.06, 0.8, 219.0, 47.0, 13.0, 8.0);
			glPopMatrix();

			/* Draw the Earth and the Moon */
			glPushMatrix();
			planet(0.068, 1.1, 66.0, 134.0, 244.0, 7.0);
			planet(0.03, 0.2, 255.0, 255.0, 255.0, 20.0);
			glPopMatrix();

			/* Draw the Mars */
			glPushMatrix();
			planet(0.058, 1.5, 219.0, 28.0, 28.0, 6.0);
			glPopMatrix();

			/* Draw the Jupiter */
			glPushMatrix();
			planet(0.12, 2.0, 247.0, 167.0, 74.0, 5.0);
			glPopMatrix();

			/* Draw the Saturn */
			glPushMatrix();
			planet(0.10, 2.5, 237.0, 197.0, 152.0, 4.0);
			glPopMatrix();

			/* Draw the Uranus */
			glPushMatrix();
			planet(0.085, 3.0, 111.0, 188.0, 227.0, 3.0);
			glPopMatrix();

			/* Draw the Neptune */
			glPushMatrix();
			planet(0.072, 3.5, 36.0, 116.0, 156.0, 2.0);
			glPopMatrix();

			/* Draw the Pluto */
			glPushMatrix();
			planet(0.03, 4.0, 252.0, 202.0, 3.0, 1.0);
			glPopMatrix();

			/* Generate random number of stars */
			drawStars();

			/* Trigger sun's corona */
			corona();
		}
		else{
			drawStars();

			glPushMatrix();
			planet(0.45, 0.0, 205.0, 172.0, 119.0, 5.0);
			glPopMatrix();

			planetRing(22, 21, 19, 2.0, 0.60);
			planetRing(22, 21, 19, 2.0, 0.61);
			planetRing(22, 21, 19, 2.0, 0.62);
			planetRing(22, 21, 19, 2.0, 0.63);
			planetRing(22, 21, 19, 2.0, 0.64);
			planetRing(28, 27, 23, 2.0, 0.65);
			planetRing(28, 27, 23, 2.0, 0.66);
			planetRing(28, 27, 23, 2.0, 0.67);
			planetRing(28, 27, 23, 2.0, 0.68);
			planetRing(28, 27, 23, 2.0, 0.69);
			planetRing(114, 103, 86, 5.0, 0.70);
			planetRing(114, 103, 86, 5.0, 0.71);
			planetRing(114, 103, 86, 5.0, 0.72);
			planetRing(114, 103, 86, 5.0, 0.73);
			planetRing(114, 103, 86, 5.0, 0.74);
			planetRing(136, 122, 96, 5.0, 0.75);
			planetRing(136, 122, 96, 5.0, 0.76);
			planetRing(136, 122, 96, 5.0, 0.77);
			planetRing(136, 122, 96, 5.0, 0.78);
			planetRing(136, 122, 96, 5.0, 0.79);
			planetRing(154, 141, 122, 5.0, 0.80);
			planetRing(154, 141, 122, 5.0, 0.81);
			planetRing(154, 141, 122, 5.0, 0.82);
			planetRing(154, 141, 122, 5.0, 0.83);
			planetRing(154, 141, 122, 5.0, 0.84);
			planetRing(48, 41, 31, 1.0, 0.85);
			planetRing(48, 41, 31, 1.0, 0.86);
			planetRing(48, 41, 31, 1.0, 0.87);
			planetRing(48, 41, 31, 1.0, 0.88);
			planetRing(48, 41, 31, 1.0, 0.89);
			planetRing(21, 18, 13, 2.0, 0.90);
			planetRing(21, 18, 13, 2.0, 0.91);
			planetRing(21, 18, 13, 2.0, 0.92);
			planetRing(21, 18, 13, 2.0, 0.93);
			planetRing(21, 18, 13, 2.0, 0.94);
			planetRing(79, 76, 67, 3.0, 0.95);
			planetRing(79, 76, 67, 3.0, 0.96);
			planetRing(79, 76, 67, 3.0, 0.97);
			planetRing(79, 76, 67, 3.0, 0.98);
			planetRing(79, 76, 67, 3.0, 0.99);
			planetRing(91, 91, 78, 5.0, 1.0);
			planetRing(91, 91, 78, 5.0, 1.01);
			planetRing(91, 91, 78, 5.0, 1.02);
			planetRing(91, 91, 78, 5.0, 1.03);
			planetRing(91, 91, 78, 5.0, 1.04);
			planetRing(101, 93, 80, 5.0, 1.05);
			planetRing(101, 93, 80, 5.0, 1.06);
			planetRing(101, 93, 80, 5.0, 1.07);
			planetRing(101, 93, 80, 5.0, 1.08);
			planetRing(101, 93, 80, 5.0, 1.09);
			planetRing(137, 126, 109, 5.0, 1.1);
			planetRing(137, 126, 109, 5.0, 1.11);
			planetRing(137, 126, 109, 5.0, 1.12);
			planetRing(137, 126, 109, 5.0, 1.13);
			planetRing(137, 126, 109, 5.0, 1.14);
		}
	}

	/* Starship USS Enterprise NCC-1701 */
	if (ZPosition == 0.0)
		ZPosition = 8.0;
	XPosition = XPosition + enterpriseSpeed * moveTheShip * leftwardDirection + enterpriseSpeed * moveTheShip * rightwardDirection;
	YPosition = YPosition + enterpriseSpeed * moveTheShip * upwardDirection + enterpriseSpeed * moveTheShip * downwardDirection;
	ZPosition = ZPosition + enterpriseSpeed * moveTheShip * forwardDirection + enterpriseSpeed * moveTheShip * backwardDirection;
	glTranslatef(0.0 + XPosition, 0.5 + YPosition, ZPosition);
	glScalef(1.2, 1.2, 1.2);
	ussEnterprise();

	/* Enable weapon system on the Enterpise */
	if (fireEnable == 1){
		firing(186);
		firing(89);
	}

	/* Shield for the USS Enterprise NCC-1701 */
	shield();

	/* Lightspeed travel */
	lightSpeedTravel();

	/* swap the drawing buffers */
	glutSwapBuffers();
}

/************************************************************************

Function:		initializeGL

Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void)
{
	/* Enable depth testing */
	glEnable(GL_DEPTH_TEST);

	/* Turn on smooth line drawing */
	glEnable(GL_LINE_SMOOTH);

	/*  Turn on transparency blending */
	glEnable(GL_BLEND);

	/* Set the blending mode */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Set background color to be black */
	glClearColor(0, 0, 0, 1.0);

	/* Change into projection mode so that we can change the camera properties */
	glMatrixMode(GL_PROJECTION);

	/* Load the identity matrix into the projection matrix */
	glLoadIdentity();

	/* gluPerspective(fovy, aspect, near, far) */
	gluPerspective(45, (float)1200 / (float)1000, 1, 100);

	/* Change into model-view mode so that we can change the object positions */
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************

Function:		reShape

Description:	Reshape function to handle window resize

*************************************************************************/
void reShape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluPerspective(45, (float)w / (float)h, 1, 100);
	else
		gluPerspective(45, (float)w / (float)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************

Function:		readFile

Description:	Read data from file. File must be placed under the same
folder as the CPP file.

*************************************************************************/
void readFile(){
	/* File initialization */
	ifstream file("enterprise.txt", ios::in);
	char vf;
	float sX, sY, sZ;

	/* Error handling for reading file */
	if (!file)
		cerr << "Cant open " << endl;

	/* Read from file and store enterprise to data structure */
	while (file >> vf >> sX >> sY >> sZ)
	{
		if (vf == 'v'){
			countFile += 1;
			epX[countFile] = { sX };
			epY[countFile] = { sY };
			epZ[countFile] = { sZ };
		}
		if (vf == 'f'){
			countFace += 1;
			epfX[countFace] = sX;
			epfY[countFace] = sY;
			epfZ[countFace] = sZ;
		}
	}
}

/************************************************************************

Function:		main

Description:	Sets up the openGL rendering context and the windowing
system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	int checkA = 0;
	tA[0] = { 1 };
	tA[1] = { 2 };
	tA[2] = { 3 };
	tA[3] = { 4 };
	tA[4] = { 5 };
	for (int i = 0; i < 20; i++){
		if (tA[i] != NULL)
			checkA += 1;
	}
	//printf("%d\n", checkA);

	int length = 10;
	int *p;
	p = new (nothrow) int[length];
	for (int i = 0; i < length; i++){
		p[i] = i;
	}

	for (int i = 0; i < length; i++){
		printf("%d\n", p[i]);
	}

	/* Read Enterprise data from file */
	readFile();

	/* Initialize the toolkit */
	glutInit(&argc, argv);

	/* Set display mode */
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	/* Set window size */
	glutInitWindowSize(1200, 1000);

	/* Set window position on screen */
	glutInitWindowPosition(100, 150);

	/* Open the screen window */
	glutCreateWindow("The Hitch Hiker’s Guide to the Planets");

	/* Reshape function */
	glutReshapeFunc(reShape);

	/* Register display function */
	glutDisplayFunc(solarSystem);

	/* Register the animation function */
	glutIdleFunc(spinPlanet);

	/* Reigster the keyboard function */
	glutKeyboardFunc(keyFunction);

	/* Register the special key function */
	glutSpecialFunc(keyForEnterprise);

	/* Register the key release function */
	glutSpecialUpFunc(keyUpEnterprise);

	/* Initialize the rendering context */
	initializeGL();

	/* Print keyboard controls */
	printf("Scene Controls\n");
	printf("------------------------------\n");
	printf("\n");
	printf("r: toggle rings\n");
	printf("s: toggle stars\n");
	printf("c: toggle the sun's corona\n");
	printf("k: toggle shields\n");
	printf("l: toggle lightspeed travel\n");
	printf("f: toggle weapon on the Enterprise \n");
	printf("e: toggle cloaking on the Enterprise \n");
	printf("\n");
	printf("Camera Controls\n");
	printf("------------------------------\n");
	printf("Up      Arrow:      move up\n");
	printf("Down    Arrow:      move down\n");
	printf("Right   Arrow:      move right\n");
	printf("Left    Arrow:      move left\n");
	printf("PAGE    UP   :      forward\n");
	printf("PAGE    DOWN :      backward\n");

	/* Go into a perpetual loop*/
	glutMainLoop();
}