#include <lke/graphics/modelcomponent.h>

#include <lke/assets/ModelLoader.h>
#include <lke/core/entity.h>
#include <lke/graphics/model.h>

namespace lke
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