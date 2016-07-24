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
#include <math.h>
#include "transforms.h"
#include "utils.h"

#define PI           3.14159265359

GLfloat f1(GLfloat time, GLfloat x, GLfloat y)
{
	GLfloat norm = sqrt(x*x + y*y);
	return sin( norm / (cos( time * 2.0 * PI )+1) );
}

rgb_color_t f1_color(GLfloat time, GLfloat x, GLfloat y, GLfloat z) {
	rgb_color_t ret;
	GLfloat norm = sqrt(x*x + y*y);
	ret = hsv_to_rgb((norm/6.0)*360.0+(sin(time * 4 * PI)/2.0+0.5)*360.0, 0.9, sin(time * 2.0 * PI)/4.0+0.75);
	return ret;
}

GLfloat f2(GLfloat time, GLfloat x, GLfloat y)
{
	GLfloat norm = x*x + y*y;
	return time*5.0*exp(-norm/(8*(1.0-time+0.01)))/2;
}

rgb_color_t f2_color(GLfloat time, GLfloat x, GLfloat y, GLfloat z)
{
	rgb_color_t ret;
	ret.r = (x+6.0)/6.0*time;
	ret.g = (y+6.0)/6.0*time;
	ret.b = (z+6.0)/6.0*time;
	return ret;
}

GLfloat f3(GLfloat time, GLfloat x, GLfloat y)
{
	return sin(-x*x+y+time*PI*2)/4.0;
}

GLfloat f4(GLfloat time, GLfloat x, GLfloat y) {
	GLfloat norm2 = x*x + y*y;
	if(norm2 < time * time * 6.0 * 6.0)
		return norm2 / 4.0;
	else
		return 0.0;
}
