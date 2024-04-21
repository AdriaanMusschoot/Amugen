#pragma once
#include <memory>
#include <string>

#include "Base/Component.h"
#include "Wrappers/Texture2D.h"
#include "TransformComponent.h"

namespace amu
{

	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent(GameObject *  ownerObjectPtr, const std::string& fileName = "");
		virtual ~RenderComponent() override = default;
	
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator= (const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator= (const RenderComponent&&) = delete;
	
		void Render() const override;

		void SetTexture(const std::string& fileName);
		void SetTexture(std::unique_ptr<Texture2D> textureUPtr);
	private:
		std::unique_ptr<amu::Texture2D> m_TextureUPtr = nullptr;

		TransformComponent* m_TransformPtr = nullptr;
	};

}