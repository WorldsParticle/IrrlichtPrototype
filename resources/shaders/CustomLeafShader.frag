//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2016 Martin-Pierrat Louis (louismartinpierrat@gmail.com)
//

#version    130

struct Light {
    vec3    position;
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
};

in vec3 position;
in vec3 normal;
in vec2 texture_coords;
in vec3 tangent;
in vec3 binormal;

uniform sampler2D   diffuse_texture;
uniform sampler2D   normal_texture;
uniform sampler2D   alpha_texture;
uniform Light       light;
uniform float       specular_hardness;

void    main()
{
    vec4    fragment_color = pow(texture(diffuse_texture, texture_coords), vec4(2.2f));
    vec4    alpha = texture(alpha_texture, texture_coords);
//    normal = texture(normal_texture, texture_coords);

    vec3 light_direction = normalize(light.position - position);
    float lambertian = max(dot(light_direction, normal), 0.0);
    float specular = 0.0;
    if (lambertian > 0.0)
    {
        vec3 view_direction = normalize(-position);
        vec3 half_direction = normalize(light_direction + view_direction);
        float specular_angle = max(dot(half_direction, normal), 0.0);
        specular = pow(specular_angle, specular_hardness);

//        fragment_color = vec4(1.0f);
    }
    fragment_color += vec4(light.ambient + lambertian * light.diffuse + specular * light.specular, 0.0f);
    gl_FragColor = vec4(fragment_color.x, fragment_color.y, fragment_color.z, alpha.x + alpha.y + alpha.z);
}