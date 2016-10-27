uniform mat4 ModViewProj;

out vec2 TexCoord;

void	main()
{
	// Need to clamp or we get an awful tearing even though CLAMP_TO_EDGE is enabled
	TexCoord = clamp(gl_MultiTexCoord0.xy, 0.002, 0.998);

	vec4 vertexPos = ModViewProj * gl_Vertex;
	gl_Position = vertexPos;
}