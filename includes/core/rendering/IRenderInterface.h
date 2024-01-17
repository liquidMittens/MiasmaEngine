#ifndef IRenderInterface_H_
#define IRenderInterface_H_
#include <memory>
#include "camera/Camera.h"
#include "Text.h"
using namespace tdogl;

class IScene;
class GLWindow;
class Text;
namespace Miasma::Renderer
{
	class IRenderInterface
	{
		virtual void Initialize(GLWindow* pWindow) = 0;
		virtual void DrawTextObjects(Miasma::Component::Text* textComponent) = 0;
		virtual bool DrawScene(std::unique_ptr<IScene>& scene) = 0;
		virtual void Shutdown() = 0;
	};

}

#endif
