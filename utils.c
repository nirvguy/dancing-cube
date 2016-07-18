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
#include "utils.h"

rgb_color_t hsv_to_rgb(float h, float s, float v)
{
	rgb_color_t ret;
	int i = (int)floor(h/60.0f) % 6;
	float f = h/60.0f - floor(h/60.0f);
	float p = v * (float)(1 - s);
	float q = v * (float)(1 - s * f);
	float t = v * (float)(1 - (1 - f) * s);

	switch (i) {
		case 0:
			ret.r = v;
			ret.g = t;
			ret.b = p;
			break;
		case 1:
			ret.r = q;
			ret.g = v;
			ret.b = p;
			break;
		case 2:
			ret.r = p;
			ret.g = v;
			ret.b = t;
			break;
		case 3:
			ret.r = p;
			ret.g = q;
			ret.b = v;
			break;
		case 4:
			ret.r = t;
			ret.g = p;
			ret.b = v;
			break;
		case 5:
			ret.r = v;
			ret.g = p;
			ret.b = q;
			break;
	}
	return ret;
}
