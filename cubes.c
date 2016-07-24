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
#include "cubes.h"
#include "transforms.h"
#include "models.h"

typedef void (*draw_object_callback_t) (GLfloat);

cube_t** cubes;
material_type mat_base_type = PLASTIC;
draw_object_callback_t draw_object_callback = drawSolidCube;

void init_cubes()
{
	cubes = (cube_t**) malloc(CUBES_X * sizeof(cube_t*));

	// Initialize cube start positions
	for(int i=0; i<CUBES_X; i++) {
		cubes[i] = (cube_t*) malloc(CUBES_Y * sizeof(cube_t));

		for(int j=0; j<CUBES_X; j++) {
			cubes[i][j].loc.x = cube_get_x(i);
			cubes[i][j].loc.y = cube_get_y(j);
			cubes[i][j].loc.z = START_Z;
		}
	}
}

void destroy_cubes()
{
	for(int i=0; i<CUBES_X; i++)
		free(cubes[i]);
	free(cubes);
}

void material_base_type(material_type mat_type) {
	mat_base_type = mat_type;
}

void model_type(model_t m_type)
{
	switch(m_type) {
		case SOLID_CUBE:
			draw_object_callback = drawSolidCube;
			break;
		case WIRE_CUBE:
			draw_object_callback = drawWireCube;
			break;
		case SOLID_SPHERE:
			draw_object_callback = drawSolidSphere;
			break;
		case WIRE_SPHERE:
			draw_object_callback = drawWireSphere;
			break;
		case SOLID_PYRAMID:
			draw_object_callback = drawSolidPyramid;
			break;
		case WIRE_PYRAMID:
			draw_object_callback = drawWirePyramid;
			break;
		case SOLID_TEAPOT:
			draw_object_callback = drawSolidTeapot;
			break;
		case WIRE_TEAPOT:
			draw_object_callback = drawWireTeapot;
			break;
	}
}

void update_cubes(GLfloat time, transform_callback_t anim_callback, transform_color_callback_t color_callback)
{
	for(int i=0; i<CUBES_X; i++)
		for(int j=0; j<CUBES_Y; j++) {
			if(anim_callback)
				cubes[i][j].loc.z = anim_callback(time, cubes[i][j].loc.x, cubes[i][j].loc.y);
			if(color_callback)
				cubes[i][j].color = color_callback(time, cubes[i][j].loc.x,
				                                      cubes[i][j].loc.y,
				                                      cubes[i][j].loc.z);
		}
}

void draw_cubes()
{
	for(int i=0; i<CUBES_X; i++) {
		for(int j=0; j<CUBES_Y; j++) {
			glPushMatrix();
			glTranslatef(cubes[i][j].loc.x,
			             cubes[i][j].loc.y,
			             cubes[i][j].loc.z);
			apply_material_by_type(mat_base_type, cubes[i][j].color);
			draw_object_callback(CUBE_SIZE);
			glPopMatrix();
		}
	}
}
