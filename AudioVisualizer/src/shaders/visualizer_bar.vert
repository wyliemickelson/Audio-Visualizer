#version 330 core 
layout (location = 0) in vec2 pos;

uniform mat3 transform; //transformation matrix for position & size

void main()
{
	gl_Position = transform * vec3(pos);
}
