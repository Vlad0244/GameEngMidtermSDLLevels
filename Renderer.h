#ifndef RENDERER_H
#define RENDERER_H

#include "StandardIncludes.h"
#include "Texture.h"

class Asset;

//struct Color
//{
//	Color(byte _r, byte _g, byte _b, byte _a)
//	{
//		R = _r;
//		G = _g;
//		B = _b;
//		A = _a;
//	}
//
//	byte R;
//	byte G;
//	byte B;
//	byte A;
//};

//struct Point
//{
//	Point(unsigned int _x, unsigned int _y)
//	{
//		X = _x;
//		Y = _y;
//	}
//
//	unsigned int X;
//	unsigned int Y;
//};

//struct Rect
//{
//	Rect(unsigned int _x1, unsigned int _y1, unsigned int _x2, unsigned int _y2)
//	{
//		X1 = _x1;
//		Y1 = _y1;
//		X2 = _x2;
//		Y2 = _y2;
//	}
//
//	unsigned int X1;
//	unsigned int Y1;
//	unsigned int X2;
//	unsigned int Y2;
//};

class Renderer : public Singleton<Renderer>
{
public:
	// Constructor/Destructors
	Renderer();
	virtual ~Renderer();

	//Accessors
	SDL_Window* GetWindow() { return m_window; }
	SDL_Renderer* GetRenderer() { return m_renderer; }
	SDL_Texture* GetSDLTexture(Texture* _texture);

	// Methods 
	void Initialize(int _xResolution, int _yResolution);
	Point GetWindowSize();
	void SetDrawColor(Color _color);
	void ClearScreen();
	void SetViewport(Rect _viewport);
	void RenderPoint(Point _position);
	void RenderLine(Rect _points);
	void RenderRectangle(Rect _rect);
	void RenderFillRectangle(Rect _rect);
	void RenderTexture(Texture* _texture, Point _point);
	void RenderTexture(Texture* _texture, Rect _rect);
	void RenderTexture(Texture* _texture, Rect _srcRect, Rect _destRect);
	void Shutdown();

private:
	// Members
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;
	SDL_Surface* m_surface;
	SDL_Rect m_viewPort;
	map<string, SDL_Texture*> m_textures;
};

#endif // RENDERER_H
