#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragPos;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject{
    mat4 view;
    mat4 proj;
    vec3 lightPos;
    vec3 viewPos;
} ubo;

float ambient = 0.1;
float specularStrength = 0.5;

void main(){

    vec3 viewDir = normalize(ubo.viewPos - fragPos);
    vec3 lightDir = normalize(ubo.lightPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, inNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength;
    float diff = max(dot(inNormal, lightDir), 0.0);
    vec3 result = (ambient + diff + spec) * fragColor;
    outColor = vec4(result, 1.0);
}