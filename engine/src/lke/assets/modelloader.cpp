#include <lke/assets/modelloader.h>

#include <lke/backends/backenddefines.h>

#ifdef USE_MODEL_LOADER_ASSIMP
#include <lke/backends/assimp/assimpmodelloader.h>
#endif

namespace lke
{
    ModelLoader& ModelLoader::GetInstance()
    {
#ifdef USE_MODEL_LOADER_ASSIMP
        static AssimpModelLoader s_Instance;
#else
        static_assert(false, "No asset loader was defined during project creation");
#endif

        return s_Instance;
    }
}