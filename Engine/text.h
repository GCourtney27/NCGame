#pragma once
#include "SDL_ttf.h"
#include <string>
#include "color.h"
#include "vector2D.h"

class ENGINE_API Text
{
public:
	Text(const std::string& text, const std::string& fontname, int size, const Color& color);
	~Text();

	void Draw(const Vector2D& position, float angle);

	void SetText(const std::string& text);
	void SetText(const std::string& text, Color& color);
	void SetColor(const Color& color);

protected:
	void Create();

protected:
	SDL_Texture * m_texture = nullptr;
	TTF_Font* m_font = nullptr;
	std::string m_text;
	Color m_color;
};