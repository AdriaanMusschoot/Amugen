#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void amu::Renderer::Init(SDL_Window* window)
{
	m_WindowPtr = window;
	m_RendererPtr = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_RendererPtr == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	SDL_RenderSetVSync(m_RendererPtr, true);
}

void amu::Renderer::Render() const
{

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_RendererPtr, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_RendererPtr);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_RendererPtr);
}

void amu::Renderer::Destroy()
{
	if (m_RendererPtr != nullptr)
	{
		SDL_DestroyRenderer(m_RendererPtr);
		m_RendererPtr = nullptr;
	}
}

void amu::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, SDL_Rect const& sourceRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = sourceRect.w;
	dst.h = sourceRect.h;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &sourceRect, &dst);
}

SDL_Renderer* amu::Renderer::GetSDLRenderer() const { return m_RendererPtr; }
