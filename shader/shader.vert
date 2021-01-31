#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragPos;
layout(location = 2) out vec3 outNormal;

layout(binding = 0) uniform UniformBufferObject{
    mat4 view;
    mat4 proj;
    vec3 lightPos;
    vec3 viewPos;
} ubo;

layout(binding = 1) uniform UniformBufferDynamics{
    mat4 model;
}ubd;

void main(){
    vec4 FragPos = ubd.model * vec4(inPosition, 1.0);
    gl_Position = ubo.proj * ubo.view * FragPos;
    fragColor = inColor;
    fragPos = vec3(FragPos);
    outNormal = normalize(mat3(transpose(inverse(ubd.model))) * inNormal);
}