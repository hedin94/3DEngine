#version 150

#include "lighting.glh"

uniform PointLight pointLight;

vec4 calcLightingEffect(vec3 normal)
{
  return calcPointLight(pointLight, normal);
}

#include "lighting.fs"


