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

typedef GLfloat (*transform_callback_t) (GLfloat, GLfloat, GLfloat);
typedef rgb_color_t (*transform_color_callback_t) (GLfloat, GLfloat x, GLfloat y, GLfloat z);

typedef struct point3d_t {
	GLfloat x, y, z;
} point3d;

typedef struct point2d_t {
	GLfloat x, y;
} point2d;

typedef struct {
	point3d loc;
	rgb_color_t color;
} cube_t;

typedef struct {
	GLfloat start_x, start_y, start_z;
	GLfloat end_x, end_y;
	GLfloat cube_size;
	GLfloat eps;
} cube_config_t;

static inline GLfloat cube_get_x(cube_config_t* config, int i)
{
	return config->start_x + (config->cube_size + config->eps) * i;
}

static inline GLfloat cube_get_y(cube_config_t* config, int j)
{
	return config->start_y + (config->cube_size + config->eps) * j;
}

static inline int get_cubes_x(cube_config_t* config)
{
	return (int) (config->end_x - config->start_x) / (config->cube_size + config->eps);
}
static inline int get_cubes_y(cube_config_t* config)
{
	return (int) (config->end_x - config->start_x) / (config->cube_size + config->eps);
}

void init_cubes(cube_config_t config);
void update_cubes(GLfloat time, transform_callback_t anim, transform_color_callback_t color_anim);
void draw_cubes();
void destroy_cubes();

/*
 * Change material type
 *
 * \param mat_type New material type
 */
void material_base_type(material_type mat_type);

/*
 * Change 3d model
 *
 * \param model_type  New 3D model type
 */
void model_type(model_t model_type);

#endif /* end of include guard: CUBES_H */
