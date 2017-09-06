# Changelog

All notable changes between releases can be found here.

## 2017-09-06 - Version 0.2.1
#### Fixed
* Adding entities should no longer cause crashes after enough expansion on
  entity managers using more than a single component.

## 2017-09-03 - Version 0.2.0
#### Added
* A method, `getVectorReference()` to EntityManagerBase which retrieves a 
  memory reference to the relevant vector in componentCollection

#### Changed
* Entity managers now use `shared_ptr` instead of raw pointers
* Entity managers now accept a list of variadic templates during construction
* Systems are now a template class which require the typename parameter of the
  entity manager which will be their target
* Photon updated to use CMake for build system generation
* .gitignore file works with `build/` and `Build/` directories

#### Removed
* EntityManagerBase's `registerComponent<>()`, `destroyComponent<>()`, and
  `growComponent<>() have become private methods. They are not to be used
  outside of class methods because of their variadic template arguments.
    * As such there is no need to write a custom constructor, destructor, and
	  expander for derived entity managers.

#### Deprecated
* Most of system's features, including `targetComponent<>()` and 
  `untargetComponent<>()` will be rewritten soon. 
