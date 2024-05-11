#include "GameObject.h"
#include <algorithm>
#include "TransformComponent.h"
void pacman::GameObject::Update()
{
    for (const auto& component : m_ComponentUPtrVec)
    {
        component->Update();
    }
    std::erase_if(m_ComponentUPtrVec,
        [&](const std::unique_ptr<Component>& componentUPtr)
        {
            return componentUPtr->GetToBeDestroyed();
        });
}

void pacman::GameObject::Render() const
{
    for(const auto & component: m_ComponentUPtrVec)
    {
        component->Render();
    }
}

void pacman::GameObject::EnableToBeDestroyed()
{
    m_ToBeDestroyed = true;
    for (const auto& childPtr : m_ChildObjectPtrVec)
    {
        childPtr->EnableToBeDestroyed();
    }
}

void pacman::GameObject::SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition)
{
    if(IsChild(newParentObjectPtr) || newParentObjectPtr == this || m_ParentObjectPtr == newParentObjectPtr)
    {
        return;
    }

	TransformComponent* temp = GetComponent<TransformComponent>();
    if (newParentObjectPtr == nullptr)
    {
        temp->SetLocalPosition(temp->GetWorldPosition());
    }
    else
    {
	    if (keepWorldPosition)
	    {
            temp->SetLocalPosition(temp->GetWorldPosition() - newParentObjectPtr->GetComponent<TransformComponent>()->GetWorldPosition());
	    }
        else
        {
			temp->SetTransformDirty();
        }
    }

    if (m_ParentObjectPtr)
    {
        m_ParentObjectPtr->RemoveChild(this);
    }

    m_ParentObjectPtr = newParentObjectPtr;

    if (m_ParentObjectPtr)
    {
        m_ParentObjectPtr->AddChild(this);
    }
}

bool pacman::GameObject::IsChild(const GameObject* parentObjectPtr) const
{
    return std::ranges::any_of(m_ChildObjectPtrVec,
    [&](const GameObject* childObjectPtr)
    {
    	return childObjectPtr->IsChild(parentObjectPtr);
    });
}

void pacman::GameObject::RemoveChild(GameObject* gameObject)
{
    std::erase(m_ChildObjectPtrVec, gameObject);
}

void pacman::GameObject::AddChild(GameObject* gameObjectPtr)
{
    m_ChildObjectPtrVec.emplace_back(gameObjectPtr);
}