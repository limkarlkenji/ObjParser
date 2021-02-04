#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

in vec3 fragVert;

void main()
{
	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f); 
	//FragColor = vec4(fragVert.x, fragVert.y, fragVert.z, 1.0f);
	//FragColor = texture(ourTexture, texCoord);
	
	//FragColor = texture(ourTexture, texCoord) * vertexColor;
	//FragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, vec2(texCoord.x, texCoord.y)), 0.5f) * vertexColor;
};