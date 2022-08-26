#version 450




void main()
{
	vec4 Pos[3];
	Pos[0] = vec4(-0.5, -0.5, 0.0, 1.0);
	Pos[1] = vec4( 0.0, +0.5, 0.0, 1.0);
	Pos[2] = vec4(+0.5, -0.5, 0.0, 1.0);
	vec3 Col[3];
	Col[0] = vec3(1.0, 0.0, 0.0); // red
	Col[1] = vec3(0.0, 1.0, 0.0); // green
	Col[2] = vec3(0.0, 0.0, 1.0); // blue

	gl_Position = Pos[gl_VertexIndex];


}