#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "rendering/IRenderInterface.h"
#include <vector>
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class MeshRenderable;
class Scene;

class GLRenderer : public IRenderInterface
{
public:
	// Inherited via IRenderInterface
	virtual void Initialize(std::shared_ptr<tdogl::Camera> camera) override;
	virtual void DrawScene(std::unique_ptr<Scene>& scene) override;
	virtual void Shutdown() override;

	void AddMeshRenderable(std::shared_ptr<MeshRenderable> newMesh);
private:
	std::shared_ptr<tdogl::Camera> m_camera;
	std::vector<std::shared_ptr<MeshRenderable>> m_meshList;

};

#endif
