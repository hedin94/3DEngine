
void main()
{
  vec4 totalLight = vec4(0,0,0,1);
  vec3 normal = normalize(tbnMatrix * (255.0f/128.0f * texture2D(normalMap, texCoord0.xy).xyz - 1));
  vec4 color = texture2D(diffuse, texCoord0.xy);
  totalLight += calcLightingEffect(normal);

  gl_FragColor =  color * totalLight; 
}
