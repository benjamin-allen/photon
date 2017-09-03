Photon
======

Photon is a WIP [entity-component-system][1] (ECS) written in C++.
Photon is designed to be fast and lightweight, staying out of the way and 
allowing the programmer create their game.

An entity-component-system is a paradigm used in game development where game
objects, or entities, are composed of data structures, or components. Functions,
called systems, are designed to operate on the entities based on thee components
they contain. This design through composition stands in contrast to the 
traditional object-oriented approach to game development. You can read more 
about the basics of an ECS [here][2] and [here][3]. Other names for ECS include
entity-system and component-entity-system.


# Design Goals
Photon attempts to do the following things for the developer:
* Provide a basic structure to create components
* Provide an abstract implementation of a class with which entities are managed
* Provide a basic structure to create systems
* Define the storage of components such that they maintain cache-coherency

Photon does not attempt to do any of the following:
* Define a fully-functional implementation of an entity manager. That is left to
  the developer
* Define any sets of components for use in games
* Define any systems
* Be purely non-object-oriented. Some developers consider a non-OO ECS to be
  a necessity, but this is not a design goal in Photon. 

# Installation
### Note
Photon uses CMake to handle build systems on different platforms. Currently the
CMakeLists assumes that you are using GCC or MSVC, and support for other
compilers is not assured. Photon only depends on the C++ standard library, but
it requires the C++17 (C++1z) version of the standard library because it makes
use of the `any` object. (Note: On older versions of GCC, use of the 
`any-experimental` header will not work)

### Dependencies
To build Photon you will need a compiler that supports C++17 (particularly the
`any` object found in the standard library for C++17). On Windows, MSVS 2017's
compiler supports C++17. On Linux, GCC > 7.0 should suffice. Clang is currently
untested. To use CMake with Photon you must use CMake 3.8 or above.

### Building
In `photon/`:
* `$ mkdir build`
* `$ cd build`
* `$ cmake ..`

On Windows, use the generated PHOTON.sln files.

On Linux, CMake generates a MakeFile. Invoke it with `make` while in `build/`.

Using `build/` isn't necessary but `build/` and `Build/` are included in the
.gitignore, so using these directories are recommended.


# Resources
### [Tutorial]

### [Contributing]

### [Implementation Help]
There is also a Doxygen file available. Simply `cd` over to `doc` and run
`doxygen doxyfile` to generate HTML/LaTeX docs.

# License
Photon is licensed under the [MIT License].


[1]: https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system "Wikipedia entry"
[2]: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/ "An article about ECS"
[3]: http://entity-systems.wikidot.com/ "Entity Systems wiki"
[MIT License]: ./LICENSE.md "License"
[Tutorial]: ./doc/Tutorial.md "Tutorial"
[Contributing]: ./doc/Contributing.md "Contributing"
[Implementation Help]: ./doc/Implementation.md "Implementation"
