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
#include "materials.h"

/**
 * Convert HSV to RGB
 *
 * \param h Hue        (from 0.0 to 360.0)
 * \param s Saturation (from 0.0 to 1.0)
 * \param v Value      (from 0.0 to 1.0)
 *
 * \return rgb color from the hue, saturation and value
 */
rgb_color_t hsv_to_rgb( float h, float s, float v );
