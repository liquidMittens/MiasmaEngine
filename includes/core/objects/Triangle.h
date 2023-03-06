#pragma once
#include <vector>
namespace Triangle
{
// triangle vertices
// x,y,z,r,g,b,s,t
std::vector<float> vertices = {
			-0.25, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.25, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
};

int vertexCount = 3;
}
