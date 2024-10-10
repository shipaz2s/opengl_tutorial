#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;

void main()
{
	FragColor = mix( texture(texture1, TexCoord), texture( texture2, TexCoord ), visibility) * vec4(ourColor, 1.0f);
	// FragColor = texture(texture2, TexCoord);
}