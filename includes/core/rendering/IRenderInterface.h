#ifndef IRenderInterface_H_
#define IRenderInterface_H_
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class Scene;
class GLWindow;
namespace Miasma::Renderer
{
	class IRenderInterface
	{
		virtual void Initialize(GLWindow* pWindow) = 0;
		virtual bool DrawScene(std::unique_ptr<Scene>& scene) = 0;
		virtual void Shutdown() = 0;
	};

}

#endif
