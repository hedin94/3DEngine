#version 150

#include "lighting.glh"

uniform SpotLight spotLight;

vec4 calcLightingEffect(vec3 normal)
{
  return calcSpotLight(spotLight, normal);
}

#include "lighting.fs"

