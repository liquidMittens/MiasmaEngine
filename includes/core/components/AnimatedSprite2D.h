#ifndef ANIMATEDSPRITE2D_H_
#define ANIMATEDSPRITE2D_H_
#include "Sprite2D.h"

namespace Miasma::Component
{
	struct AnimationCreateInfo2D
	{
	public:
		int frameSizeX;
		int frameSizeY;
		float animationTime;
		bool loopAnimation;
		int totalFrames;
		Material material;

		AnimationCreateInfo2D() :
			totalFrames(0),
			frameSizeX(0),
			frameSizeY(0),
			animationTime(0.0f),
			loopAnimation(false)
		{

		}
	};

	class AnimatedSprite2D : public Sprite2D
	{
	public: 

		CLASS_DECLARATION(AnimatedSprite2D);

		AnimatedSprite2D(GameObject* owner, AnimationCreateInfo2D& creationInfo);
		~AnimatedSprite2D();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		AnimationCreateInfo2D& GetAnimationInfo() { return m_animationInfo; }
		int GetCurrentFrameIndex() const { return m_currentFrame; }
		bool IsAnimationFinished() const { return m_animationFinished; }

	private:
		AnimationCreateInfo2D m_animationInfo;
		int m_currentFrame;
		float m_currentAnimationTime;
		bool m_animationFinished;
	};
}
#endif
