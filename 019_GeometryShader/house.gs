#version 330 core
layout (points) in;
layout (triangle_strip,max_vertices = 5) out;

in VS_OUT
{
 vec3 color;
} gs_in[];
out vec3 fColor;
void build_house(vec4 position)
{
   fColor = gs_in[0].color;
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:����
    EmitVertex();   

    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:����
    EmitVertex();
	fColor = vec3(0.1f,0.3f,0.7f);
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:����
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:����
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:����
    EmitVertex();
	fColor = vec3(1,1,1);
    EndPrimitive();

}
void main()
{
	 build_house(gl_in[0].gl_Position);
}