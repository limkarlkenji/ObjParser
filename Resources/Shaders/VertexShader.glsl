#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 atexCoord;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoord = atexCoord;

	gl_Position = (projection * view * model) * position;
};