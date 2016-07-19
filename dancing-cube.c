/**
 * dancing-cube, an OpenGL program for animate an array of cubes.
 * Copyright (C) 2016 Juan Cruz Sosa (nirvguy@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <string.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <getopt.h>
#include "cubes.h"

const GLfloat light_ambient[]  = {0.8 , 0.8 , 0.8 , 0.0};   // RGBA color of the ambient light
const GLfloat light_diffuse[]  = {0.7 , 0.7 , 0.7 , 1.0};   // RGBA color of the diffuse light
const GLfloat light_position[] = {1.0 , 1.0 , 1.0 , 0.0};   // Position of the light

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_cubes();
	glutSwapBuffers();
}

void timer_update_cubes(int frame)
{
	update_cubes_position(frame);

	frame++;
	if(frame > FRAME_END)
		frame = FRAME_START;

	glutTimerFunc(MSEC_FRAME, timer_update_cubes, frame);
}

void window_reshape(GLint width, GLint height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,                                   // Field of view angle in degrees
		           (GLfloat) width / (GLfloat) height,   // Aspect ratio
		           0.5,                                  // Z near
		           20.0);                                // Z far
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	// Set background color to gray
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	// Set-up lights
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Set-up perspective
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0,    // Field of view angle in degrees
		           1.0,     // Aspect ratio
		           0.5,     // Z near
		           20.0);   // Z far

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(5.0, 5.0, 5.0,  // Eye position
	          0.0, 0.0, 0.0,  // Center
	          0.0, 0.0, 1.0); // Up vector
}

void usage() {
	printf("Usage: ./danzing_cube [OPENGL_OPTION]... [OPTION]...,\n");
	printf("OPENGL_OPTION:\n");
	printf("-display DISPLAY         Specify the X server to connect to. \n\
                         If not specified, the value of the DISPLAY environment variable is used.\n");
	printf("-geometry W x H + X + Y  Determines where window's should be created on the screen.\n\
                         The parameter following -geometry should be formatted as a standard X geometry specification.\n\
                         The effect of using this option is to change the GLUT initial size\n\
                         and initial position the same as if glutInitWindowSize or glutInitWindowPosition\n\
                         were called directly.\n");
	printf("-iconic                  Requests all top-level windows be created in an iconic state.\n");
	printf("-indirect                Force the use of indirect OpenGL rendering contexts.\n");
	printf("-direct                  Force the use of direct OpenGL rendering contexts\n\
                         (not all GLX implementations support direct rendering contexts).\n\
                         A fatal error is generated if direct rendering is not supported by the OpenGL implementation.\n\
                         If neither -indirect or -direct are used to force a particular behavior,\n\
                         GLUT will attempt to use direct rendering if possible and otherwise fallback to indirect rendering.\n");
	printf("-gldebug                 After processing callbacks and/or events,\n\
                         check if there are any OpenGL errors by calling glGetError.\n\
                         If an error is reported, print out a warning by looking up the error code with gluErrorString.\n\
                         Using this option is helpful in detecting   OpenGL run-time errors.\n");
	printf("-sync                    Enable synchronous X protocol transactions.\n\
                         This option makes it easier to track down potential   X protocol errors.\n");
	printf("\n");
	printf("OPTION:\n");
	printf("-h                                    Display this message\n");
	printf("-a ANIM_TYPE, --anim=ANIM_TYPE        Change the animation type.\n");
	printf("                                      Options for ANIM_TYPE are f1, f2, f3\n");
	printf("                                      (by default is f1)\n");
	printf("-m MODEL_TYPE, --model=MODEL_TYPE     Change the 3D model.\n");
	printf("                                      Options for MODEL_TYPE are solid_cube, wire_cube, solid_sphere, wire_sphere\n");
	printf("                                      (by default is solid_cube)\n");
}

int main(int argc, char** argv)
{
	cube_config_t cube_config = { SOLID_CUBE, F1 };

	static struct option long_opts[] = {
		{"help"  , no_argument       , 0 , 'h'} ,
		{"anim"  , required_argument , 0 , 'a'} ,
		{"model" , required_argument , 0 , 'm'} ,
		{0       , 0                 , 0 , 0}
	};

	glutInit(&argc, argv);

	int opt_index, opt;
	while((opt = getopt_long(argc, argv, "ha:m:",
		                     long_opts, &opt_index)) != -1) {
		switch(opt) {
			case '?':
				usage();
				return 1;
			case 'h':
				usage();
				return 0;
			case 'a':
				if(!strcmp(optarg, "f1"))
					cube_config.anim_type = F1;
				else if(!strcmp(optarg, "f2"))
					cube_config.anim_type = F2;
				else if(!strcmp(optarg, "f3"))
					cube_config.anim_type = F3;
				else {
					fprintf(stderr,"%s : Animation not recognized\n", optarg);
					return 1;
				}
				break;
			case 'm':
				if(!strcmp(optarg, "solid_cube"))
					cube_config.model_type = SOLID_CUBE;
				else if(!strcmp(optarg, "wire_cube"))
					cube_config.model_type = WIRE_CUBE;
				else if(!strcmp(optarg, "solid_sphere"))
					cube_config.model_type = SOLID_SPHERE;
				else if(!strcmp(optarg, "wire_sphere"))
					cube_config.model_type = WIRE_SPHERE;
				else {
					fprintf(stderr, "%s : Model not recognized \n", optarg);
					return 1;
				}
				break;
		}
	}

	//Set-up cubes
	init_cubes(cube_config);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("dancing-cube");

	glutDisplayFunc(display);
	glutReshapeFunc(window_reshape);

	glutDisplayFunc(display);
	glutTimerFunc(MSEC_FRAME, timer_update_cubes, FRAME_START);
	glutIdleFunc(display);

	init();
	glutMainLoop();

	destroy_cubes();

	return 0;
}
