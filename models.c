/**
 * This file is part of dancing-cube.
 *
 * dancing-cube is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dancing-cube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dancing-cube.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include "models.h"

#define SPHERE_SLICES    16
#define SPHERE_STACKS    8

void drawSolidSphere(GLfloat size)
{
	glutSolidSphere(size, SPHERE_SLICES, SPHERE_STACKS);
}

void drawWireSphere(GLfloat size)
{
	glutWireSphere(size, SPHERE_SLICES, SPHERE_STACKS);
}

void drawSolidCube(GLfloat size)
{
	glutSolidCube(size);
}

void drawWireCube(GLfloat size)
{
	glutWireCube(size);
}

void drawSolidTeapot(GLfloat size)
{
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidTeapot(size);
}

void drawWireTeapot(GLfloat size)
{
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutWireTeapot(size);
}

void drawPyramid(GLfloat size, GLenum mode)
{
	glScalef(size, size, size);
	
	glBegin(mode);
	glNormal3f(0.0  , 0.707 , 0.707);
	glVertex3f(1.0  , 1.0   , 0.0);
	glVertex3f(-1.0 , 1.0   , 0.0);
	glVertex3f(0.0  , 0.0   , 1.0);
	glEnd();

	glBegin(mode);
	glNormal3f(0.707 , 0.0  , 0.707);
	glVertex3f(1.0   , 1.0  , 0.0);
	glVertex3f(1.0   , -1.0 , 0.0);
	glVertex3f(0.0   , 0.0  , 1.0);
	glEnd();

	glBegin(mode);
	glNormal3f(0.0  , -0.707 , 0.707);
	glVertex3f(1.0  , -1.0   , 0.0);
	glVertex3f(-1.0 , -1.0   , 0.0);
	glVertex3f(0.0  , 0.0    , 1.0);
	glEnd();

	glBegin(mode);
	glNormal3f(-0.707 , 0.0  , 0.707);
	glVertex3f(-1.0   , -1.0 , 0.0);
	glVertex3f(-1.0   , 1.0  , 0.0);
	glVertex3f(0.0    , 0.0  , 1.0);
	glEnd();
}

void drawSolidPyramid(GLfloat size)
{
	drawPyramid(size, GL_POLYGON);
}

void drawWirePyramid(GLfloat size)
{
	drawPyramid(size, GL_LINE_LOOP);
}
