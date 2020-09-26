#pragma once
#include <lazye/lazye.h>

#include <memory>

namespace lazye
{
    class Model;

    class lazyedll ModelLoader
    {
    public:
        ~ModelLoader() = default;

        static ModelLoader& GetInstance();

        virtual std::unique_ptr<Model> LoadModel(const std::string& modelPath) const = 0;

    protected:
        ModelLoader() = default;
    };
}