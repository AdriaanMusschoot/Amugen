#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Texture2D.h"
#include "TransformComponent.h"

namespace amu
{

	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent(GameObject *  ownerObjectPtr, std::string_view const& fileName = "");
		virtual ~RenderComponent() override = default;
	
		RenderComponent(RenderComponent const&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator= (RenderComponent const&) = delete;
		RenderComponent& operator= (RenderComponent&&) = delete;
	
		void Render() const override;

		glm::vec2 GetSize() const;

		void SetTexture(std::string_view const& fileName);
		void SetTexture(std::unique_ptr<Texture2D> textureUPtr);
	private:
		std::unique_ptr<amu::Texture2D> m_TextureUPtr = nullptr;

		TransformComponent* m_TransformPtr = nullptr;
	};

}