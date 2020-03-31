#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform vec2 offset;
out vec3 ourColor;

void main()
{
  vec3 findal = position;
  findal.x = findal.x + offset.x;
  gl_Position = vec4(findal,1.0f);
  ourColor = color;
}