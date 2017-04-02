#version 150

#include "lighting.glh"

uniform PointLight pointLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos)
{
  return calcPointLight(pointLight, normal, worldPos);
}

#include "lighting.fs"


