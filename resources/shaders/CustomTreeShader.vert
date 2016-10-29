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

uniform     mat4    modelview;
uniform     mat4    modelviewprojection;

out vec3    position;
out vec3    normal;
out vec2    texture_coords;
out vec3    tangent;
out vec3    binormal;

void    main()
{
    vec4 position4 = modelview * gl_Vertex;
    position = position4.xyz / position4.w;
    normal = mat3(modelview) * gl_Normal.xyz;
    texture_coords = gl_MultiTexCoord0.xy;
    tangent = mat3(modelview) * gl_MultiTexCoord1.xyz;
    binormal = mat3(modelview) * gl_MultiTexCoord2.xyz;
    gl_Position = modelviewprojection * gl_Vertex;
}