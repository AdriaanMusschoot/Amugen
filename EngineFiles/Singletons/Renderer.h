#ifndef AMU_RENDERER_H
#define AMU_RENDERER_H

#include <SDL.h>
#include "Singleton.h"

namespace amu
{

	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		virtual ~Renderer() = default;

		Renderer(Renderer const&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer const&) = delete;
		Renderer& operator=(Renderer&&) = delete;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(Texture2D const& texture, float x, float y, SDL_Rect const& sourceRect) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(SDL_Color const& color) { m_ClearColor = color; }
	private:
		friend class Singleton<Renderer>;

		Renderer() = default;

		SDL_Renderer* m_RendererPtr = nullptr;
		SDL_Window* m_WindowPtr = nullptr;
		SDL_Color m_ClearColor = SDL_Color{};
	};

}

#endif //AMU_RENDERER_H