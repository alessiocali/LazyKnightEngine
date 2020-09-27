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

    void ModelComponent::Render(Seconds dt, RenderingContext& context)
    {
        if (m_Model != nullptr)
        {
            const auto [view, projection] = context.GetViewProjectionMatrices();
            m_Model->Draw(view, projection);
        }
    }

}