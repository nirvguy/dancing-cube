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

#define SPHERE_SLICES    16
#define SPHERE_STACKS    8

void drawSolidSphere(void)
{
	glutSolidSphere(CUBE_SIZE, SPHERE_SLICES, SPHERE_STACKS);
}

void drawWireSphere(void)
{
	glutWireSphere(CUBE_SIZE, SPHERE_SLICES, SPHERE_STACKS);
}

void drawSolidCube(void)
{
	glutSolidCube(CUBE_SIZE);
}

void drawWireCube(void)
{
	glutWireCube(CUBE_SIZE);
}

void init_cubes(cube_config_t cube_config)
{
	switch(cube_config.model_type) {
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
	}

	switch(cube_config.anim_type) {
		case F1:
			anim_callback = f1;
			break;
		case F2:
			anim_callback = f2;
			break;
		case F3:
			anim_callback = f3;
			break;
	}

	cube_position = (point3d**) malloc(CUBES_X * sizeof(point3d*));

	// Initialize cube start positions
	for(int i=0; i<CUBES_X; i++) {
		cube_position[i] = (point3d*) malloc(CUBES_Y * sizeof(point3d));

		for(int j=0; j<CUBES_X; j++) {
			cube_position[i][j].x = START_X + (CUBE_SIZE + EPS) * i;
			cube_position[i][j].y = START_Y + (CUBE_SIZE + EPS) * j;
			cube_position[i][j].z = START_Z;
		}
	}
}

void destroy_cubes()
{
	for(int i=0; i<CUBES_X; i++)
		free(cube_position[i]);
	free(cube_position);
}

void update_cubes_position(int frame)
{
	GLfloat t = (GLfloat) frame / ((GLfloat) (FRAME_END-FRAME_START));

	for(int i=0; i<CUBES_X; i++)
		for(int j=0; j<CUBES_Y; j++)
			cube_position[i][j].z = anim_callback(t, cube_position[i][j].x, cube_position[i][j].y);
}

void draw_cubes()
{
	for(int i=0; i<CUBES_X; i++) {
		for(int j=0; j<CUBES_Y; j++) {
			glPushMatrix();
			glTranslatef(cube_position[i][j].x,
			             cube_position[i][j].y,
			             cube_position[i][j].z);
			draw_object_callback();
			glPopMatrix();
		}
	}
}

void timer_update_cubes(int frame)
{
	update_cubes_position(frame);

	frame++;
	if(frame > FRAME_END)
		frame = FRAME_START;

	glutTimerFunc(MSEC_FRAME, timer_update_cubes, frame);
}
