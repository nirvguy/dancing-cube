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
#include "transforms.h"
#include <math.h>

#define PI           3.14159265359

GLfloat f1(GLfloat time, GLfloat x, GLfloat y)
{
	GLfloat norm = sqrt(x*x + y*y);
	return sin( norm / (cos( time * 2.0 * PI )+1) );
}

GLfloat f2(GLfloat time, GLfloat x, GLfloat y)
{
	GLfloat norm = x*x + y*y;
	return time*5.0*exp(-norm/(8*(1.0-time+0.01)))/2;
}

GLfloat f3(GLfloat time, GLfloat x, GLfloat y)
{
	return sin(-x*x+y+time*PI*2)/4.0;
}
