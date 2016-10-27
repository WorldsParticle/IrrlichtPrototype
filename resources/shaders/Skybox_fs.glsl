in vec2 TexCoord;

uniform sampler2D	texture_skybox1;
uniform sampler2D	texture_skybox2;
uniform float		mixFactor;

void	main()
{
	vec4 skybox1 = texture(texture_skybox1, TexCoord);
	vec4 skybox2 = texture(texture_skybox2, TexCoord);
	gl_FragColor = mix(skybox1, skybox2, mixFactor);
}