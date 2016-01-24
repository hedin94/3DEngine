#version 150

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 tangent;

varying vec2 texCoord0;
varying vec3 worldPos0;
varying mat3 tbnMatrix;

uniform mat4 transform;
uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(position, 1.0);
  texCoord0 = texCoord;
  worldPos0 = (transform * vec4(position, 1.0)).xyz;
  vec3 n = normalize((transform * vec4(normal, 0.0)).xyz);
  vec3 t = normalize((transform * vec4(tangent, 0.0)).xyz);
  t = normalize(t - dot(t, n) * n);

  vec3 biTangent = cross(t, n);

  tbnMatrix = mat3(t, biTangent, n);
}
