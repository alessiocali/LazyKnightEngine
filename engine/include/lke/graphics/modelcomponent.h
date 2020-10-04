#pragma once
#include <lke/graphics/renderingcomponent.h>

#include <memory>

namespace lke
{
    class Model;

    class lkedll ModelComponent final : public RenderingComponent
    {
    public:
        ModelComponent(const std::string& modelPath);
        ~ModelComponent();

        void Render(RenderingContext& context) override;

    private:
        std::unique_ptr<Model> m_Model;
    };
}