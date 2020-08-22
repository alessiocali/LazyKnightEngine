This is a repository I use as a sandbox while studying game programming. My idea was to develop a project structure which would contain:

* An automated build environment based on CMake.
* A lazy implementation of a game engine based mostly on existing libraries.
* Automated tests based on Catch2.
* A set of small samples built on the above engine which showase its functionalities

The idea is to have a practice framework in place which expands with time. It's supposed to be for self learning and improvement, so I doubt you'll find anything useful for you strictly. Also it's supposed to be filled with errors and bad practice which I try to improve over time. Still, be free to browse it.

# List of dependencies

* Git
* Python3

# Usage

Start by running.

```
python fetch-dependencies.py
```

It will initialize and run VCPKG to grab and install the required libraries. After that create the cmake project by running

```
cmake -B build
```

And you should have your project ready for compilation inside the build directory