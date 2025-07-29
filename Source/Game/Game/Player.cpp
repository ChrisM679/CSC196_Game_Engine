#include "Player.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

void Player::Update(float dt)
{
    //Rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	m_transform.rotation += (rotate * rotationRate) * dt;

	//Thrust
	float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(m_transform.rotation)) * thrust * speed;
    velocity += force * dt;

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt);
}
