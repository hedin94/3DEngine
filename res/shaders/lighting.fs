
void main()
{
  vec3 directionToEye = normalize(R_eyePos - worldPos0);
  vec2 texCoords = texCoord0.xy + (directionToEye * tbnMatrix).xy * (texture2D(dispMap, texCoord0.xy).r * dispMapScale + dispMapBias);

  vec4 totalLight = vec4(0, 0, 0, 0);
  vec3 normal = normalize(tbnMatrix * (255.0f/128.0f * texture2D(normalMap, texCoords).xyz - 1));
  vec4 color = texture2D(diffuse, texCoords);
  totalLight += calcLightingEffect(normal, worldPos0);

  gl_FragColor =  color * totalLight; 
}
