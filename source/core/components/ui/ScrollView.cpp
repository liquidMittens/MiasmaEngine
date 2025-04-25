#include "ui/ScrollView.h"
using namespace Miasma::Component;

CLASS_DEFINITION(Component, ScrollView);


ScrollView::ScrollView(GameObject* owner, glm::vec2 size) : 
	m_scrollviewSize(size),
	Component(owner, TO_STRING("ScrollView"))
{

}

ScrollView::~ScrollView()
{

}

void ScrollView::Start()
{

}

void ScrollView::Update(float dt)
{

}

void ScrollView::Shutdown()
{

}