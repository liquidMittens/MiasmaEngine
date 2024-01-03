#include "components/AnimatedSprite2D.h"
#include "Sprite2D.h"
using namespace Miasma::Component;

CLASS_DEFINITION(Sprite2D, AnimatedSprite2D);

AnimatedSprite2D::AnimatedSprite2D(GameObject* owner, AnimationCreateInfo2D& creationInfo) :
	Sprite2D(owner, creationInfo.material, TO_STRING(AnimatedSprite2D)),
	m_currentFrame(0),
	m_currentAnimationTime(0.0f),
	m_animationFinished(false)
{
	m_animationInfo.animationTime = creationInfo.animationTime;
	m_animationInfo.frameSizeX = creationInfo.frameSizeX;
	m_animationInfo.frameSizeY = creationInfo.frameSizeY;
	m_animationInfo.loopAnimation = creationInfo.loopAnimation;
	m_animationInfo.material = creationInfo.material;
	m_animationInfo.totalFrames = creationInfo.frameSizeX * creationInfo.frameSizeY;
}

AnimatedSprite2D::~AnimatedSprite2D()
{

}

// behavior functions
void AnimatedSprite2D::Start()
{

}

void AnimatedSprite2D::Update(float dt)
{
	if (!m_animationFinished) {
		m_currentAnimationTime += dt;
		if (m_currentAnimationTime >= m_animationInfo.animationTime) {
			m_currentAnimationTime = 0.0f;
			++m_currentFrame;
			// check if we've reached the end of the animation
			if (!m_animationInfo.loopAnimation && m_currentFrame == (m_animationInfo.totalFrames)) {
				m_animationFinished = true;
				m_currentAnimationTime = 0.0f;
				//m_currentFrame = 0;
			}
			else if (m_animationInfo.loopAnimation && m_currentFrame == (m_animationInfo.totalFrames)) {
				m_animationFinished = false;
				m_currentAnimationTime = 0.0f;
				m_currentFrame = 0;
			}
		}
	}
}

void AnimatedSprite2D::Shutdown()
{

}