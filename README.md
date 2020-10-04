# Lazy Knight Engine

I wanted to make a Game Engine, that's pretty much all there is to it. The features are very barren, take it more as a framework or a starting point for doing your own things or as an inspiration.

I'm obsessed with dependency isolation so you will see a bazillion of interfaces hiding backends all over the place. Also I like to tinker with edge-new C++ features, so you will see a lot of C++17 (and C++20 soon-ish) features being spammed here and there just because.

# Features

* It can render a mesh with OpenGL. Yai.

# List of requirements

* Git
* Python3
* CMake

# List of library dependencies

* SDL2
* SDL2_image
* OpenAssimp
* GLAD

For the tests:

* Catch2

See `dependencies.json` for an always up-to-date list.

# Managing dependencies

You have two options: using the provided helper scripts, or DIY.

## With the helper scripts

I included VCPKG as a Git Submodule and an helper script in Python for automatically fetching all dependencies.

Start by initializing VCPKG:

```
git submodule update --init
```

Then run the helper script:

```
python fetch-dependencies.py
```

Using this method gives (supposedly) less headaches and is more straighforward, but also less flexible

### Pros

* One single command to update all dependencies.
* The VCPKG submodule is versioned and will always download the same library versions (unless you update it manually), which are the same with which the Engine has been developed.
* VCPKG is integrated in CMake and will automatically feed all required informations into the build system.
* On Dll platforms (i.e. Windows) VCPKG takes care of copying the depending .dlls into the runtime directories.
* The installed libraries are isolated from the rest of the system so they won't conflict with existing installations.

### Cons

* Since the dependencies are local to the instance of VCPKG, any project linking against LazyKnight is not guaranteed to work unless it links against the exact same library versions, which might not be the case if you use a different dependency management system. Fortunately I added an automated script to cover this case as well (see `Linking against LazyKnight` below).

## Do It Yourself

In this case, you're on your own: welcome to the magic wonderland of C++ dependency management. You don't need to initialize VCPKG, but in this case you also need to turn off the CMake option `USE_VCPKG_TOOLCHAIN` (see `Generating project files`).

The build system uses CMake's `find_package` to search for all required files; you can find all the setup under `engine/Dependencies.cmake`. Under Linux, most of the times, you can just use `apt-get` or whatever package manager your distribution comes with to download the development version of the required libraries. Under Windows you will likely use something like NuGet or VCPKG installed on a user level to get your requirements.

### Pros

* You can reuse the dependencies already installed on your system.
* You're free to manage said dependencies in whichever way you prefer.

### Cons

* The library versions you will link against might have not been tested to work with LazyKnight.
* Getting CMake to do your bidding in this case is 99% of the times a huge pain.

# Generating project files

You can generating project files for your working environment (be it Make/GCC, Visual Studio or whatever) using CMake.

```
cmake -B build
```

Will generate the project files under the `build` directory. You can then fire up your IDE (or run `make`) and run/install the generated targets.

## LazyKnight options

Turn each option to on/off from Command Line with the parameter `-D<OPTION_NAME>=[ON|OFF]`

* `USE_VCPKG_TOOLCHAIN`: Use VCPKG for managing dependencies. Default: `ON`
* `BUILD_LAZYKNIGHT_SHARED`: Build the `Engine` target as a shared library. Default: `ON`
* `BUILD_LAZYKNIGHT_TESTS`: Include in the project files the Catch2 unit tests. Default: `ON`
* `BUILD_LAZYKNIGHT_SAMPLES`: Include in the project files some usage samples for the library. Default: `OFF`

## Installing the library

Run the `Install` target created by CMake to compile all of the Engine targets and install the library files in your system. Under Unix, these should go under `/usr/local/lib`. Under Windows, the default directory is usually under `Program Files (x86)`, which is discouraged because it contains spaces and is usually unaccessible unless the installation command is run with admin privileges (which, on Windows, is a tad more annoying than typing `sudo make install`). In this case I suggest to set `CMAKE_INSTALL_PREFIX` during project generation in order to specify where you want the files to be installed.

## Linking against LazyKnight

The `Install` command compiles and installs a lookup file named `LazyKnightConfig.cmake`, which will instruct CMake on how to link against LazyKnight. On your end, add the following instructions to your CMake file:

```
# Look for LazyKnight and configure installation variables
find_package(LazyKnight CONFIG REQUIRED COMPONENTS Engine)

# Link MyTarget against LazyKnight
target_link_libraries(MyTarget LazyKnight::Engine)
```

If all goes well CMake will locate `LazyKnightConfig.cmake` and prepare everything for you. Under Unix, this is usually the case with the default install location, as CMake looks under `/usr/local/lib` for the `*Config.cmake` files. Under Windows, you might want to instruct CMake on where to look at. Either append the root installation directory to `CMAKE_PREFIX_PATH` to add it to the lookup folders, or define `LazyKnight_DIR` to point at the directory where `LazyKnightConfig.cmake` has been installed.

The Config file will also define the following variables for your convenience

* `LazyKnightEngine_LIBRARIES`: alias for LazyKnight::Engine
* `LazyKnightEngine_Shared`: set to `ON` if the library was built as a shared library, `OFF` otherwise.
* `LazyKnightEngine_CMAKE_DIR`: The directory where `LazyKnightConfig.cmake` has been installed
* `LazyKnightEngine_BINDIR`: The directory where the runtime library files (.dll), if available, have been installed. 

### Automatically generating from template

If you're using the VCPKG integration and don't want to risk linking against the wrong library, and you're also lazy like me and don't want to setup the basic files every time, I've got you covered.

The following script:

```
python generate-project.py <target-directory>
```

will run VCPKG's `export` command and create a copy of your installed libraries. Then it will initialize `<target-directory>` with the following content:

* The exported VCPKG setup, under the `vcpkg` directory.
* A copy of the contents of the `project_template` directory, which includes some boilerplate code.

With that done you should be able to initialize your CMake project from under `<target-directory>` and everything will work out of the box.

# Q&A

__Q: Why making another Game Engine when there are industry-standard alternatives?__

A: Yes.

__Q: Is this actually anywhere viable to make a game?__

A: Well yes, but actually not. Right now I have barely basic mesh loading functionality and an update loop, take your considerations.

__Q: What's up with the name?__

A: Well the original intent was to make a sandbox framework for learning game programming, with a "Lazy" implementation based on snatching as many libraries as humanly possible. It turned out I prefer to do most things manually just for fun.

As for the "Knight" I used a free asset of a Knight sprite as a sample thing to render. "Lazy Engine" sounded lame, so I kinda stuck the "Knight" in it.