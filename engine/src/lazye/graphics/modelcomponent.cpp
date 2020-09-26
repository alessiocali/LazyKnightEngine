#include <lazye/graphics/modelcomponent.h>

#include <lazye/assets/ModelLoader.h>
#include <lazye/core/entity.h>
#include <lazye/graphics/model.h>

namespace lazye
{
    ModelComponent::ModelComponent(const std::string& modelPath)
    {
        m_Model = ModelLoader::GetInstance().LoadModel(modelPath);
    }

    ModelComponent::~ModelComponent() = default;

    void lazye::ModelComponent::UpdateOwnerTransform()
    {
        m_Model->SetTransform(GetOwner()->GetTransform());
    }

    void lazye::ModelComponent::Render(float dt, RenderingContext& context)
    {
        context.Render(*m_Model);
    }

}