#pragma once
#include <lke/lke.h>

#include <memory>

namespace lke
{
    class Model;

    class lkedll ModelLoader
    {
    public:
        ~ModelLoader() = default;

        static ModelLoader& GetInstance();

        virtual std::unique_ptr<Model> LoadModel(const std::string& modelPath) const = 0;

    protected:
        ModelLoader() = default;
    };
}