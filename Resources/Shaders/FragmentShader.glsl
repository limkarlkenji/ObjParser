#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	//FragColor = texture(ourTexture, texCoord) * vertexColor;
	//FragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, vec2(texCoord.x, texCoord.y)), 0.5f) * vertexColor;
};