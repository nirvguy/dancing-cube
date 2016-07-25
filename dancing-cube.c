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
#include "transforms.h"
#include "cubes.h"

#define CUBE_SIZE     0.5
#define START_X      -6.0         // first cube x-axis origin
#define START_Y      -6.0         // first cube y-axis origin
#define START_Z       0.0         // height for all cubes by default
#define END_X         6.0         // last cube x-axis origin
#define END_Y         6.0         // last cube y-axis origin
#define EPS           0.01        // cube's separation distance
#define FRAME_START   0
#define FRAME_END     250
#define FPS           24
#define MSEC_FRAME    1000.0/FPS  // time in millesconds of a frame

#define FULLSCREEN_OPT 256
#define START_X_OPT    257
#define START_Y_OPT    258
#define END_X_OPT      259
#define END_Y_OPT      260
#define EPS_OPT        261
#define CUBE_SIZE_OPT  262

typedef enum {
	F1,
	F2,
	F3,
	F4
} anim_t;

const GLfloat light_ambient[]  = {0.8 , 0.8 , 0.8 , 0.0};   // RGBA color of the ambient light
const GLfloat light_diffuse[]  = {0.7 , 0.7 , 0.7 , 1.0};   // RGBA color of the diffuse light
const GLfloat light_position[] = {1.0 , 1.0 , 1.0 , 0.0};   // Position of the light

int mat_index=0;
int anim_index=0;
int model_index=0;
int paused=0;
transform_callback_t anim_callback = f1;
transform_color_callback_t color_callback = f2_color;

int win_nr;

void animation_type(anim_t anim_type)
{
	switch(anim_type) {
		case F1:
			anim_callback = f1;
			break;
		case F2:
			anim_callback = f2;
			break;
		case F3:
			anim_callback = f3;
			break;
		case F4:
			anim_callback = f4;
			break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_cubes();
	glutSwapBuffers();
}

void timer_update_cubes(int frame)
{
	update_cubes((GLfloat) frame / (FRAME_END-FRAME_START), anim_callback, color_callback);

	if(!paused) {
		frame++;
		if(frame > FRAME_END)
			frame = FRAME_START;
	}

	glutPostRedisplay();
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

void keyboard_press(unsigned char key, int x, int y)
{
	switch(key) {
		case 27: //ESCAPE
			glutDestroyWindow(win_nr);
			break;
		case 'm': // Next materials
			mat_index++;
			if(mat_index > METAL)
				mat_index = PLASTIC;
			material_base_type(mat_index);
			break;
		case 'M': // Previous material
			mat_index--;
			if(mat_index < 0)
				mat_index = METAL;
			material_base_type(mat_index);
			break;
		case 'a': // Next animation function
			anim_index++;
			if(anim_index > F4)
				anim_index = F1;
			animation_type(anim_index);
			break;
		case 'A': // Previous animation function
			anim_index--;
			if(anim_index < 0)
				anim_index = F4;
			animation_type(anim_index);
			break;
		case 'n': // Next model type
			model_index++;
			if(model_index > WIRE_TEAPOT)
				model_index = SOLID_CUBE;
			model_type(model_index);
			break;
		case 'N': // Previous model type
			model_index--;
			if(model_index < 0)
				model_index = WIRE_TEAPOT;
			model_type(model_index);
			break;
		case ' ': // Toggle play/pause animation
			paused = !paused;
			break;
	}
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

void close_window()
{
	destroy_cubes();
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
	printf("--fullscreen                          Turns window to fullscreen mode\n");
	printf("--start-x                             Change the default start position in x-axis\n");
	printf("--start-y                             Change the default start position in y-axis\n");
	printf("--end-x                               Change the default last position in x-axis\n");
	printf("--end-y                               Change the default last position in y-axis\n");
	printf("--size                                Change default cube size position\n");
	printf("--eps                                 Change default cube separation\n");
}

float read_float(char* str) {
	char* ep;

	float res = strtof(str, &ep);

	if(*ep != '\0') {
		fprintf(stderr, "%s: is not a float\n", str);
		exit(1);
	}

	return res;
}

int main(int argc, char** argv)
{
	cube_config_t conf = {.start_x   = START_X,
	                      .start_y   = START_Y,
	                      .start_z   = START_Z,
	                      .end_x     = END_X,
	                      .end_y     = END_Y,
	                      .cube_size = CUBE_SIZE,
	                      .eps       = EPS};
	static int fullscreen;
	
	static struct option long_opts[] = {
		{"help"       , no_argument       , 0           , 'h'} ,
		{"anim"       , required_argument , 0           , 'a'} ,
		{"model"      , required_argument , 0           , 'm'} ,
		{"fullscreen" , no_argument       , &fullscreen , FULLSCREEN_OPT} ,
		{"start-x"    , required_argument , 0           , START_X_OPT} ,
		{"start-y"    , required_argument , 0           , START_Y_OPT} ,
		{"end-x"      , required_argument , 0           , END_X_OPT} ,
		{"end-y"      , required_argument , 0           , END_Y_OPT} ,
		{"size"       , required_argument , 0           , CUBE_SIZE_OPT} ,
		{"eps"        , required_argument , 0           , EPS_OPT} ,
		{0            , required_argument , 0           , 0}
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
					anim_index = F1;
				else if(!strcmp(optarg, "f2"))
					anim_index = F2;
				else if(!strcmp(optarg, "f3"))
					anim_index = F3;
				else if(!strcmp(optarg, "f4"))
					anim_index = F4;
				else {
					fprintf(stderr,"%s : Animation not recognized\n", optarg);
					return 1;
				}
				animation_type(anim_index);
				break;
			case START_X_OPT:
				conf.start_x = read_float(optarg);
				break;
			case START_Y_OPT:
				conf.start_y = read_float(optarg);
				break;
			case END_X_OPT:
				conf.end_x = read_float(optarg);
				break;
			case END_Y_OPT:
				conf.end_y = read_float(optarg);
				break;
			case CUBE_SIZE_OPT:
				conf.cube_size = read_float(optarg);
				break;
			case EPS_OPT:
				conf.eps = read_float(optarg);
				break;
			case 'm':
				if(!strcmp(optarg, "solid_cube"))
					model_index = SOLID_CUBE;
				else if(!strcmp(optarg, "wire_cube"))
					model_index = WIRE_CUBE;
				else if(!strcmp(optarg, "solid_sphere"))
					model_index = SOLID_SPHERE;
				else if(!strcmp(optarg, "wire_sphere"))
					model_index = WIRE_SPHERE;
				else if(!strcmp(optarg, "solid_teapot"))
					model_index = SOLID_TEAPOT;
				else if(!strcmp(optarg, "wire_teapot"))
					model_index = WIRE_TEAPOT;
				else if(!strcmp(optarg, "solid_pyramid"))
					model_index = SOLID_PYRAMID;
				else if(!strcmp(optarg, "wire_pyramid"))
					model_index = WIRE_PYRAMID;
				else {
					fprintf(stderr, "%s : Model not recognized \n", optarg);
					return 1;
				}
				model_type(model_index);
				break;
		}
	}

	//Set-up cubes
	init_cubes(conf);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	win_nr = glutCreateWindow("dancing-cube");
	glutCloseFunc(close_window);

	if(fullscreen)
		glutFullScreen();

	glutDisplayFunc(display);
	glutReshapeFunc(window_reshape);

	material_base_type(PLASTIC);

	glutKeyboardFunc(keyboard_press);

	glutDisplayFunc(display);
	glutTimerFunc(MSEC_FRAME, timer_update_cubes, FRAME_START);

	init();
	glutMainLoop();

	return 0;
}
