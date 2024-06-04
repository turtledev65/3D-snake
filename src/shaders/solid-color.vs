#version 330 core

layout (location = 0) in vec3 aPos;
out vec3 vertColor;

uniform vec3 uColor = vec3(1.0f, 1.0f, 1.0f);

uniform mat4 uModel = mat4(1.0f);
uniform mat4 uView = mat4(1.0f);
uniform mat4 uProjection = mat4(1.0f);

void main()
{
  gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
  vertColor = uColor;
}
