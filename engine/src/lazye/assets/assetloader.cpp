#include <lazye/assets/assetloader.h>

#include <lazye/backends/backenddefines.h>

#ifdef USE_ASSET_LOADER_ASSIMP
#include <lazye/backends/assimp/assimpassetloader.h>
#endif

namespace lazye
{
    AssetLoader& AssetLoader::GetInstance()
    {
#ifdef USE_ASSET_LOADER_ASSIMP
        static AssimpAssetLoader s_Instance;
#else
        static_assert(false, "No asset loader was defined during project creation");
#endif

        return s_Instance;
    }
}