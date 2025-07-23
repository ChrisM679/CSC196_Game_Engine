#pragma once
#include "../Renderer/Renderer.h"
#include "../Renderer/Font.h"
#include "../Math/Vector3.h"

#include <string>

struct SDL_Texture;

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const viper::vec3& color);
		void Draw(Renderer& renderer, float  x, float  y);

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}