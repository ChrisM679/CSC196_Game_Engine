#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include <SDL3/SDL_scancode.h>

void Player::Update(float dt)
{
    float speed = 200;

    viper::vec2 direction{ 0, 0 };
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1; //speed * time.GetDeltaTime();
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1; //speed * time.GetDeltaTime();
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; //speed * time.GetDeltaTime();
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; //speed * time.GetDeltaTime();

    if (direction.Length() > 0) {
        direction = direction.Normalized();
		m_transform.position += (direction * speed) * dt;
    }
}
