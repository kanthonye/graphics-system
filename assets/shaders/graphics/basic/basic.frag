#version 450
layout(location = 0) in vec3 _normal;
layout(location = 1) in vec2 _texcoord;
layout(location = 2) in vec4 _color;


layout(location = 0) out vec4 frag_Color;
void main()
{
    frag_Color = vec4( 1.0 );
}
