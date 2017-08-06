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
  the developer due to technical reasons
* Define any sets of components for use in games
* Define any systems
* Be purely non-object-oriented. Components do have some functions defined in
  order to take advange of polymorphism


# Installation
### Note
Photon is under heavy development and few environments have support. It is being
developed as a static Windows library, although an update to use makefiles is
planned.

### Windows Prerequisites
* Microsoft Visual Studio 2017 with C++ support (Photon needs C++17 support)

### Installation
1. Download and extract Photon's source code somewhere you can find it again
2. Open the solution (.sln) file with MSVS and build it. This will generate the 
   static library which you can link into your code
3. In a project in which you wish to use Photon, include the headers 
   (`photon/include`), set the linker to search the directory containing
   `photon.lib`, and list `photon.lib` as an additional dependency. Then, simply
   `#include "photon.hpp"` and you're off.


# [Tutorial]


# Contributing
TODO: This

# License
Photon is licensed under the [MIT License]


[1]: https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system "Wikipedia entry"
[2]: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/ "An article about ECS"
[3]: http://entity-systems.wikidot.com/ "Entity Systems wiki"
[MIT License]: ./LICENSE.md "License"
[Tutorial]: ./doc/Tutorial.md "Tutorial"