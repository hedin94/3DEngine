#version 150

#include "lighting.glh"

uniform DirectionalLight directionalLight;

vec4 calcLightingEffect(vec3 normal)
{
  return calcDirectionalLight(directionalLight, normal);
}

#include "lighting.fs"
