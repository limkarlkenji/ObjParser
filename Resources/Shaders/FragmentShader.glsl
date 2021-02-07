#version 330 core

out vec4 FragColor;

in vec3 fragmentPos;
in vec2 texCoord;
in vec3 normal;

uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
	vec3 color = vec3(1.0f, 0.5f, 0.31f);
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragmentPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	FragColor = vec4(color * (ambient + diffuse), 1.0f);
	//FragColor = vec4(color * lightColor, 1.0f);

	//FragColor = vec4(fragVert.x, fragVert.y, fragVert.z, 1.0f);
	//FragColor = texture(ourTexture, texCoord);
	
	//FragColor = texture(ourTexture, texCoord) * vertexColor;
	//FragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, vec2(texCoord.x, texCoord.y)), 0.5f) * vertexColor;
};