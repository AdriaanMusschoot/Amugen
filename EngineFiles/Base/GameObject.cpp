#include "GameObject.h"
#include <algorithm>
#include "TransformComponent.h"
void amu::GameObject::Update()
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

void amu::GameObject::Render() const
{
    for(const auto & component: m_ComponentUPtrVec)
    {
        component->Render();
    }
}

void amu::GameObject::EnableToBeDestroyed()
{
    m_ToBeDestroyed = true;
    for (const auto& childPtr : m_ChildObjectPtrVec)
    {
        childPtr->EnableToBeDestroyed();
    }
}

bool amu::GameObject::GetToBeDestroyed() const 
{
    return m_ToBeDestroyed; 
}

amu::GameObject* amu::GameObject::GetParent() const 
{
    return m_ParentObjectPtr;
}

void amu::GameObject::SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition)
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

std::int64_t amu::GameObject::GetChildCount() const 
{
    return std::ssize(m_ChildObjectPtrVec);
}

amu::GameObject* amu::GameObject::GetChildAt(std::int64_t idx) const 
{
    return m_ChildObjectPtrVec.at(idx);
}

void amu::GameObject::SetTag(std::string_view const& tag)
{
    m_Tag = tag;
}

std::string_view amu::GameObject::GetTag() const
{
    return m_Tag;
}

bool amu::GameObject::IsChild(GameObject const* parentObjectPtr) const
{
    return std::ranges::any_of(m_ChildObjectPtrVec,
        [&](GameObject const* childObjectPtr)
        {
        	return childObjectPtr->IsChild(parentObjectPtr);
        });
}

void amu::GameObject::RemoveChild(GameObject* gameObject)
{
    std::erase(m_ChildObjectPtrVec, gameObject);
}

void amu::GameObject::AddChild(GameObject* gameObjectPtr)
{
    m_ChildObjectPtrVec.emplace_back(gameObjectPtr);
}