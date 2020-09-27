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

    void ModelComponent::Render(RenderingContext& context)
    {
        if (m_Model != nullptr)
        {
            const auto [view, projection] = context.GetViewProjectionMatrices();
            m_Model->Draw(GetOwner()->GetTransform().GetMatrix(), view, projection);
        }
    }

}