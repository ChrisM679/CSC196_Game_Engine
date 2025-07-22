#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper
{
	void Actor::Update(float dt)
	{
		m_transform.position += velocity * dt;
	}

	void Actor::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}

}
