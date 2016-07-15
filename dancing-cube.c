/**
 * dancing-cube, an OpenGL program for animate an array of cubes.
 * Copyright (C) 2016 Juan Cruz Sosa (nirvguy@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "cubes.h"

const GLfloat light_ambient[]  = {0.5  , 0.5   , 0.5 , 0.0};   // RGBA color of the ambient light
const GLfloat light_diffuse[]  = {0.01 , 0.689 , 0.8 , 1.0};   // RGBA color of the diffuse light
const GLfloat light_position[] = {1.0  , 1.0   , 1.0 , 0.0};   // Position of the light

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_cubes();
	glutSwapBuffers();
}


void window_reshape(GLint width, GLint height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,                                   // Field of view angle in degrees
		           (GLfloat) width / (GLfloat) height,   // Aspect ratio
		           0.5,                                  // Z near
		           20.0);                                // Z far
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	// Set background color to gray
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	// Set-up lights
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Set-up perspective
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0,    // Field of view angle in degrees
		           1.0,     // Aspect ratio
		           0.5,     // Z near
		           20.0);   // Z far

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(5.0, 5.0, 5.0,  // Eye position
	          0.0, 0.0, 0.0,  // Center
	          0.0, 0.0, 1.0); // Up vector
}

int main(int argc, char** argv)
{
	//Set-up cubes
	init_cubes();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("dancing-cube");

	glutDisplayFunc(display);
	glutReshapeFunc(window_reshape);

	glutDisplayFunc(display);
	glutTimerFunc(MSEC_FRAME, timer_update_cubes, FRAME_START);
	glutIdleFunc(display);

	init();
	glutMainLoop();

	destroy_cubes();

	return 0;
}
