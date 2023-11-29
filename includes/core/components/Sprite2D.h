#ifndef SPRITE2D_H_
#define SPRITE2D_H_
#include <vector>
#include <string>
#include "rendering/Material.h"
#include "Component.h"
#include "GUIBuilder.h"
using namespace Miasma::UI;

namespace Miasma::Component
{
	constexpr int xyz_st_format = 5;

	class Sprite2D : public Miasma::Component::Component
	{
		friend class Miasma::UI::GUIBuilder;
	public: 

		CLASS_DECLARATION(Sprite2D);

		Sprite2D(GameObject* owner, const Material& mat);
		//Sprite2D(GameObject* owner, const std::string& spriteName, const Material& mat);
		~Sprite2D();

		size_t GetVertexCount() const { return m_vertices.size() / xyz_st_format; }
		size_t GetIndicesCount() const { return m_indices.size(); }
		Material& GetMaterial() { return m_material; }
		const unsigned int GetVertexBufferObject() { return m_vbo; }
		const unsigned int GetVertexArrayObject() { return m_vao; }
		const unsigned int GetIndexBufferObject() { return m_ibo; }
		const glm::vec2 GetSpriteSize() { return m_spriteSize; }
		void SetSpriteSize(const glm::vec2& size) { m_spriteSize = size; }

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:
		std::string m_spriteName;
		unsigned int m_vbo;
		unsigned int m_vao;
		unsigned int m_ibo;
		Material m_material;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
		glm::vec2 m_spriteSize;
	};


	//std::vector<float> quadVertices = {
	//	//-5.0f, -5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	// bottom
	//	//5.0f, -5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	//5.0f, 5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

	//	//5.0f, 5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	//	//-5.0f, 5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	//-5.0f, -5.0f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f

	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	/*1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f*/
	//};

	//std::vector<int> quadIndices = {
	//	0, 1, 2, 2, 3, 0
	//};

	//size_t quadVertexCount = quadVertices.size() / 8;
}

#endif
