

#version 330 core
out vec4 FragColor;

in vec2 textCoord;

// texture sampler

uniform sampler2D texture1;
uniform float dt;
void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

