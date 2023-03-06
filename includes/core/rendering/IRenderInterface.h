#ifndef IRenderInterface_H_
#define IRenderInterface_H_
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class Scene;

class IRenderInterface
{
	virtual void Initialize(std::shared_ptr<tdogl::Camera> camera) = 0;
	virtual void DrawScene(std::unique_ptr<Scene>& scene) = 0;
	virtual void Shutdown() = 0;
};

#endif
