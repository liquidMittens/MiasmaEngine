#ifndef MESHRENDERABLE_H_
#define MESHRENDERABLE_H_

#include "rendering/Material.h"
#include "glm/gtc/type_ptr.hpp"
#include "objects/Component.h"
#include <vector>
#include "GUIBuilder.h"
using namespace miasma_ui;

namespace miasma_rtti
{

constexpr int xyz_rgb_st_format_size = 8; // pos,color,texcoords
constexpr int xyz_st_xyz_format_size = 8; // pos,texcoords,normals

struct MeshRenderableCreateInfo
{
	const char* filename;
	glm::mat4 preTransform;
	std::string meshName;
};


	class MeshRenderable : public Component
	{
		friend class miasma_ui::GUIBuilder;
	public:

		CLASS_DECLARATION(MeshRenderable);

		MeshRenderable(GameObject* owner, MeshRenderableCreateInfo* pCreateInfo, const Material& mat);
		~MeshRenderable();

		bool AttachMaterial(const Material& newMat);

		size_t GetVertexCount() const { return m_vertices.size() / xyz_st_xyz_format_size; }
		size_t GetIndicesCount() const { return m_indices.size(); }
		Material& GetMaterial() { return m_material; }
		const unsigned int GetVertexBufferObject() { return m_vbo; }
		const unsigned int GetVertexArrayObject() { return m_vao; }
		const unsigned int GetIndexBufferObject() { return m_ibo; }
		

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;
	private:
		std::string m_meshName;
		unsigned int m_vbo;
		unsigned int m_vao;
		unsigned int m_ibo;
		Material m_material;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}

#endif
