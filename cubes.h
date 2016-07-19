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
#include "materials.h"

#define CUBE_SIZE     0.5
#define START_X      -6.0         // first cube x-axis origin
#define START_Y      -6.0         // first cube y-axis origin
#define START_Z       0.0         // height for all cubes by default
#define END_X         6.0         // last cube x-axis origin
#define END_Y         6.0         // last cube y-axis origin
#define EPS           0.05        // cube's separation distance
#define CUBES_X       (int) ((END_X - START_X) / (EPS + CUBE_SIZE))          // number of cubes in x-axis
#define CUBES_Y       (int) ((END_Y - START_Y) / (EPS + CUBE_SIZE))          // number of cubes in z-axis
#define FRAME_START   0
#define FRAME_END     250
#define FPS           24
#define MSEC_FRAME    1000.0/FPS  // time in millesconds of a frame

typedef enum {
	SOLID_CUBE,
	WIRE_CUBE,
	SOLID_SPHERE,
	WIRE_SPHERE,
	SOLID_PYRAMID,
	WIRE_PYRAMID,
	SOLID_TEAPOT,
	WIRE_TEAPOT
} model_t;

typedef enum {
	F1,
	F2,
	F3
} anim_t;

typedef GLfloat (*transform_callback_t) (GLfloat, GLfloat, GLfloat);
typedef rgb_color_t (*transform_color_callback_t) (GLfloat, GLfloat x, GLfloat y, GLfloat z);
typedef void (*draw_object_callback_t) (void);

typedef struct point3d_t {
	GLfloat x, y, z;
} point3d;

typedef struct {
	point3d loc;
	rgb_color_t color;
} cube_t;

void init_cubes();
void update_cubes_position(int frame);
void draw_cubes();
void destroy_cubes();

/*
 * Change material type
 *
 * \param mat_type New material type
 */
void material_base_type(material_type mat_type);

/*
 * Change animation type
 *
 * \param anim_type New animation type
 */
void animation_type(anim_t anim_type);

/*
 * Change 3d model
 *
 * \param model_type  New 3D model type
 */
void model_type(model_t model_type);

#endif /* end of include guard: CUBES_H */
