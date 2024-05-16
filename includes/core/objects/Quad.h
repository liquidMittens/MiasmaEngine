#ifndef QUAD_H_
#define QUAD_H_
#include <vector>

namespace Quad
{
	
	static std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	};

	static std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0
	};
}

#endif