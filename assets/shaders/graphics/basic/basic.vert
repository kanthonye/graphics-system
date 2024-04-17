#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

layout(set = 0, binding = 0) uniform ShaderCameraParams
{
    mat4 proj;
    mat4 view;
    vec4 projview;
} global;

layout( push_constant ) uniform ObjectMatrices
{
    mat4 transform;
    mat3 rotation;
} model;

layout(location = 0) out vec3 _normal;
layout(location = 1) out vec2 _texcoord;
layout(location = 2) out vec4 _color;

void main()
{
    vec4 position = vec4( in_position, 1.0 );
    gl_Position = global.proj * global.view * model.transform * position;
    gl_Position.y = -gl_Position.y;
    gl_Position.x = -gl_Position.x;
}
