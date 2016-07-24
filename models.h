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
#ifndef MODELS_H
#define MODELS_H

#include <GL/glu.h>
#include <GL/glut.h>

void drawSolidSphere(GLfloat size);

void drawWireSphere(GLfloat size);

void drawSolidCube(GLfloat size);

void drawWireCube(GLfloat size);

void drawSolidTeapot(GLfloat size);

void drawWireTeapot(GLfloat size);

void drawSolidPyramid(GLfloat size);

void drawWirePyramid(GLfloat size);

#endif /* end of include guard: MODELS_H */
