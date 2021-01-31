#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>

#include "Vertex.h"

glm::vec3 normal_vector(float phi, float theta) {
	float x = sin(theta) * cos(phi);
	float y = sin(theta) * sin(phi);
	float z = cos(theta);

	return { x, y, z };
}

void DrawSphere(float radius, int longitude, int latitude, std::vector<Vertex>& vertices, std::vector<uint16_t>& indices, glm::vec3 color) {
	//Vertex
	float longitudinalResolution = glm::pi<float>() / (longitude + 1);
	float latitudinalResolution = glm::pi<float>() / (latitude + 1);
	int longitude_double = (longitude + 1) * 2;

	vertices = { 
		{{0.0f, 0.0f, 1.0f * radius}, color, {0.0f, 0.0f, 1.0f}}
	};

	float bias_factor_lat = 0;
	for (int i = 0; i < latitude; i++) {
		bias_factor_lat += latitudinalResolution;
		//float bias_factor_long = (i % 2 == 0) ? 0 : glm::pi<float>() / (longitude + 1) / 2;
		float bias_factor_long = longitudinalResolution / 2 * i;
		for (int j = 0; j < longitude_double; j++) {
			glm::vec3 ver;
			glm::vec3 norm;
			norm = normal_vector(bias_factor_long, bias_factor_lat);
			ver = radius * norm;
			bias_factor_long += longitudinalResolution;
			vertices.push_back({ ver, color, norm });
		}
	}
	vertices.push_back({ {0.0f, 0.0f, -radius}, color, {0.0f, 0.0f, -1.0f} });
	//Index
	indices = {};
	for (int i = 0; i < latitude + 1; i++) {
		for (int j = 0; j < longitude_double; j++) {
			if (i == 0) {
				indices.push_back(0);
				indices.push_back(j % longitude_double + 1);
				indices.push_back((j + 1) % longitude_double + 1);
			}
			else if (i == latitude) {
				indices.push_back(i * longitude_double + 1);
				indices.push_back((j + 1) % longitude_double + 1 + (i - 1) * longitude_double);
				indices.push_back(j % longitude_double + 1 + (i - 1) * longitude_double);
			}
			else {
				indices.push_back(j % longitude_double + 1 + (i - 1) * longitude_double);
				indices.push_back(j % longitude_double + 1 + i * longitude_double);
				indices.push_back((j + 1) % longitude_double + 1 + i * longitude_double);
				indices.push_back((j + 1) % longitude_double + 1 + i * longitude_double);
				indices.push_back((j + 1) % longitude_double + 1 + (i - 1) * longitude_double);
				indices.push_back(j % longitude_double + 1 + (i - 1) * longitude_double);
			}
		}
	}
}