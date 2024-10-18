#include "TTFont.h"
#include "Renderer.h"

TTFont::TTFont()
{
	m_font = nullptr;
	destRect = { };
}

void TTFont::Initialize(int _pointSize)
{
	M_ASSERT((TTF_Init() >= 0), "Unable to initialize SDLL TTF.");
	M_ASSERT((m_font = TTF_OpenFont("Assets/Fonts/arial.ttf", _pointSize)) != nullptr, "Failed to load font.");
}

void TTFont::Shutdown()
{
	TTF_Quit();
}

void TTFont::Write(SDL_Renderer* _renderer, const char* _text, SDL_Color _color, SDL_Point _pos)
{
	SDL_Surface* surface;
	surface = TTF_RenderUTF8_Blended(m_font, _text, _color);

	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(_renderer, surface);

	SDL_Rect destRect{ _pos.x, _pos.y, surface->w, surface->h };
	M_ASSERT(((SDL_RenderCopyEx(_renderer, texture, nullptr, &destRect, 0,
								nullptr, SDL_FLIP_NONE)) >= 0), "Could not render texture");

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}