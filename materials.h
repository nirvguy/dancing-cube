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
#ifndef MATERIALS_H
#define MATERIALS_H
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct {
	GLfloat ambient[4];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat shiness;
} material_t;

typedef struct {
	GLfloat r, g, b;
} rgb_color_t;

typedef enum {
	PLASTIC=0,
	RUBBER,
	METAL
} material_type;


void apply_material(material_t mat);
void apply_material_by_type(material_type mat_type, rgb_color_t material_color);

#endif /* end of include guard: MATERIALS_H */
