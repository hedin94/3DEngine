#version 150

varying vec2 texCoord0;

uniform sampler2D diffuse;
uniform vec3 ambientLight;

void main()
{
  vec4 color = texture2D(diffuse, texCoord0.xy);
  vec4 totalLight = vec4(ambientLight, 1);

  gl_FragColor =  color * totalLight;
}
