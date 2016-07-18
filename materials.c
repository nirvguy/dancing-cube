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

const material_t materials_type_default_values[] = {
	{{0.0  , 0.0  , 0.0  , 1.0} , {0.7 , 0.6 , 0.6} , {0.0      , 0.0      , 0.0}      , 0.25}         , //PLASTIC
	{{0.05 , 0.0  , 0.0  , 1.0} , {0.5 , 0.4 , 0.4} , {0.7      , 0.04     , 0.04}     , .078125}      , //RUBBER
	{{0.25 , 0.25 , 0.25 , 1.0} , {0.4 , 0.4 , 0.4} , {0.774597 , 0.774597 , 0.774597} , 0.6}            //CHROME
};

void apply_material(material_t mat) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shiness * 128.0);
}

void apply_material_by_type(material_type mat_type, rgb_color_t material_color) {
	material_t mat = materials_type_default_values[(unsigned short int) mat_type];
	mat.diffuse[0] = material_color.r;
	mat.diffuse[1] = material_color.g;
	mat.diffuse[2] = material_color.b;
	apply_material(mat);
}
