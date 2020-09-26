#include <lazye/backends/sdl/sdlgraphicsfactory.h>

#include <lazye/graphics/mesh.h>
#include <lazye/graphics/texture.h>

#include <lazye/backends/sdl/sdlwindow.h>

namespace lazye
{
    std::unique_ptr<Window> SDLGraphicsFactory::CreateWindow() const
    {
        return std::make_unique<SDLWindow>();
    }

    std::unique_ptr<Mesh> SDLGraphicsFactory::CreateMesh(std::size_t vertexCount) const
    {
        return nullptr;
    }

    std::unique_ptr<Texture> SDLGraphicsFactory::CreateTexture() const
    {
        return nullptr;
    }

}