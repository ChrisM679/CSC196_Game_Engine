#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include <SDL3/SDL_scancode.h>

void Player::Update(float dt)
{
    float speed = 200;
	float rotationSpeed = 180;

    //Rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	m_transform.rotation += (rotate * rotationSpeed) * dt;

	//Thrust
	float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(m_transform.rotation)) * thrust * speed;
    velocity += force * dt;

	Actor::Update(dt);

    
    /*if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;*/

    /*if (direction.Length() > 0) {
        direction = direction.Normalized();
		m_transform.position += (direction * speed) * dt;
    }*/
}
