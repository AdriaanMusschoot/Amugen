#ifndef AMU_RENDERER_H
#define AMU_RENDERER_H

#include <SDL.h>
#include "Singleton.h"

namespace pacman
{

	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_RendererPtr = nullptr;
		SDL_Window* m_WindowPtr = nullptr;
		SDL_Color m_ClearColor = SDL_Color{};
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }
	};

}

#endif //AMU_RENDERER_H