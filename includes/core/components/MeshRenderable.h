#ifndef MESHRENDERABLE_H_
#define MESHRENDERABLE_H_

#include "rendering/Material.h"
#include "glm/gtc/type_ptr.hpp"
#include "Component.h"
#include <vector>
#include "GUIBuilder.h"
using namespace Miasma::UI;

namespace Miasma::RTTI
{

constexpr int xyz_rgb_st_format_size = 8; // pos,color,texcoords
constexpr int xyz_st_xyz_format_size = 8; // pos,texcoords,normals

enum EMeshDrawType
{
	EMESH_TYPE_TRIANGLES = 0, 
	EMESH_TYPE_TRIANGLEARRAY
};

struct MeshRenderableCreateInfo
{
	const char* filename;
	glm::mat4 preTransform;
	std::string meshName;
};


	class MeshRenderable : public Component
	{
		friend class Miasma::UI::GUIBuilder;
	public:

		CLASS_DECLARATION(MeshRenderable);

		MeshRenderable(GameObject* owner, MeshRenderableCreateInfo* pCreateInfo, const Material& mat);
		MeshRenderable(GameObject* owner, std::vector<float> vertices, std::vector<int> indices, MeshRenderableCreateInfo* pCreateInfo, const Material& mat);
		~MeshRenderable();

		bool AttachMaterial(const Material& newMat);

		size_t GetVertexCount() const { return m_vertices.size() / xyz_st_xyz_format_size; }
		size_t GetIndicesCount() const { return m_indices.size(); }
		Material& GetMaterial() { return m_material; }
		const unsigned int GetVertexBufferObject() { return m_vbo; }
		const unsigned int GetVertexArrayObject() { return m_vao; }
		const unsigned int GetIndexBufferObject() { return m_ibo; }
		const EMeshDrawType GetMeshDrawType() { return m_meshDrawType; }		

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
		EMeshDrawType m_meshDrawType;
	};
}

#endif
