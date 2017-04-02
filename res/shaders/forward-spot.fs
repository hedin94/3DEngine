#version 150

#include "lighting.glh"

uniform SpotLight spotLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos)
{
  return calcSpotLight(spotLight, normal, worldPos);
}

#include "lighting.fs"

