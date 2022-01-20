#version 330 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec2 aTextCoord;

out vec2 textCoord;
uniform float dt;
void main() {
  vec3 pos = mix(aPos, vec3(aPos.x, -1.0+log(exp(1.0)), 0), dt);
  gl_Position = vec4(pos, 1.0);
  textCoord = aTextCoord;
}