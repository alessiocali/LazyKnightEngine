#pragma once
#include <lazye/lazye.h>

#include <memory>

namespace lazye
{
    class Model;

    class lazyedll AssetLoader
    {
    public:
        ~AssetLoader() = default;

        static AssetLoader& GetInstance();

        virtual std::unique_ptr<Model> LoadModel(const std::string& modelPath) = 0;

    protected:
        AssetLoader() = default;
    };
}