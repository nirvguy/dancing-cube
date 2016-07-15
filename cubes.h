/**
 * This file is part of dancing-cube
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
#ifndef CUBES_H
#define CUBES_H

#include <GL/glu.h>
#include <GL/glut.h>

#define CUBE_SIZE     0.5
#define START_X      -6.0         // first cube x-axis origin
#define START_Y      -6.0         // first cube y-axis origin
#define START_Z       0.0         // height for all cubes by default
#define END_X         6.0         // last cube x-axis origin
#define END_Y         6.0         // last cube y-axis origin
#define EPS           0.05        // cube's separation distance
#define CUBES_X       (int) ((END_X - START_X) / (EPS + CUBE_SIZE))          // number of cubes in x-axis
#define CUBES_Y       (int) ((END_Y - START_Y) / (EPS + CUBE_SIZE))          // number of cubes in z-axis

typedef struct point3d_t {
	GLfloat x, y, z;
} point3d;

point3d** cube_position;

void init_cubes();
void draw_cubes();
void destroy_cubes();

#endif /* end of include guard: CUBES_H */
