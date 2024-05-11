#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Texture2D.h"
#include "TransformComponent.h"

namespace pacman
{

	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent(GameObject *  ownerObjectPtr, const std::string_view& fileName = "");
		virtual ~RenderComponent() override = default;
	
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator= (const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator= (const RenderComponent&&) = delete;
	
		void Render() const override;

		glm::ivec2 GetSize() const;

		void SetTexture(std::string_view const& fileName);
		void SetTexture(std::unique_ptr<Texture2D> textureUPtr);
	private:
		std::unique_ptr<pacman::Texture2D> m_TextureUPtr = nullptr;

		TransformComponent* m_TransformPtr = nullptr;
	};

}