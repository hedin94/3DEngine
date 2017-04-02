#version 150

#include "lighting.glh"

uniform vec3 ambientLight;

void main()
{
  vec3 directionToEye = normalize(R_eyePos - worldPos0);
  vec2 texCoords = texCoord0.xy + (directionToEye * tbnMatrix).xy * (texture2D(dispMap, texCoord0.xy).r * dispMapScale + dispMapBias);

  vec4 color = texture2D(diffuse, texCoords);
  vec4 totalLight = vec4(ambientLight, 1);

  gl_FragColor =  color * totalLight;
}
