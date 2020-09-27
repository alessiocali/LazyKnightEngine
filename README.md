# Lazy Knight Engine

I wanted to make a Game Engine, that's pretty much all there is to it. The features are very barren, take it more as a framework or a starting point for doing your own things or as an inspiration.

I'm obsessed with dependency isolation so you will see a bazillion of interfaces hiding backends all over the place. Also I like to tinker with edge-new C++ features, so you will see a lot of C++17 (and C++20 soon-ish) features being spammed here and there just because.

# Features

* It can render a mesh with OpenGL. Yai.

# List of dependencies

* Git
* Python3

# How to build

Start by running.

```
python fetch-dependencies.py
```

It will initialize and run VCPKG to grab and install the required libraries. After that create the cmake project by running

```
cmake -B build
```

And you should have your project ready for compilation inside the build directory. There are some crude samples in the samples directory for trying out how the entire thing works.

# Q&A

__Q: Why making another Game Engine when there are industry-standard alternatives?__

A: Yes.

__Q: *Is this actually anywhere viable to make a game?__

A: Well yes, but actually not. Right now I have barely basic mesh loading functionality and an update loop, take your considerations.

__Q: *What's up with the name?__

A: Well the original intent was to make a sandbox framework for learning game programming, with a "Lazy" implementation based on snatching as many libraries as humanly possible. It turned out I prefer to do most things manually just for fun.

As for the "Knight" I used a free asset of a Knight sprite as a sample thing to render. "Lazy Engine" sounded lame, so I kinda stuck the "Knight" in it.