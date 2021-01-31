#pragma once

#include <glm/glm.hpp>

struct UniformBufferObject
{
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 lightPos;
	glm::vec3 viewPos;
};

struct UniformBufferDynamics {
	//glm::mat4* model = nullptr;
	glm::mat4 model;
};

