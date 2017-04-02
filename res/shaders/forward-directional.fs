#version 150

#include "lighting.glh"

uniform DirectionalLight directionalLight;

vec4 calcLightingEffect(vec3 normal, vec3 worldPos)
{
  return calcDirectionalLight(directionalLight, normal, worldPos);
}

#include "lighting.fs"
