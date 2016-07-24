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
#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <GL/gl.h>
#include "materials.h"

GLfloat f1(GLfloat time, GLfloat x, GLfloat y);
rgb_color_t f1_color(GLfloat time, GLfloat x, GLfloat y, GLfloat z);
GLfloat f2(GLfloat time, GLfloat x, GLfloat y);
rgb_color_t f2_color(GLfloat time, GLfloat x, GLfloat y, GLfloat z);
GLfloat f3(GLfloat time, GLfloat x, GLfloat y);
GLfloat f4(GLfloat time, GLfloat x, GLfloat y);

#endif /* end of include guard: TRANSFORMS_H */
