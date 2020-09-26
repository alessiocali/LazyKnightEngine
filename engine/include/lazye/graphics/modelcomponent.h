#pragma once
#include <lazye/graphics/renderingcomponent.h>

#include <memory>

namespace lazye
{
    class Model;

    class lazyedll ModelComponent final : public RenderingComponent
    {
    public:
        ModelComponent(const std::string& modelPath);
        ~ModelComponent();

        void Render(float dt, RenderingContext& context) override;

    private:
        void UpdateOwnerTransform() override;

        std::unique_ptr<Model> m_Model;
    };
}