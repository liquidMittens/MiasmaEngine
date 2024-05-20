#ifndef	QUAD3D_H_
#define QUAD3D_H_
#include "Component.h"
#include "Material.h"
using namespace Miasma::Component;

// forward declaration
class GameObject;


class Quad3d : public Component
{
public: 
	CLASS_DECLARATION(Quad3d);

	Quad3d(GameObject* owner, const Material& mat);
	~Quad3d();

	void Resize(float x0, float x1);
	Material& GetMaterial() { return m_material; }

	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Shutdown() override;

private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ibo;
	Material m_material;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	float m_defaultScale;
};

#endif
