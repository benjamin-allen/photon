# Implementation
## About This Document
This document describes the internal structure of the Photon library. If you
would like to contribute you can use this document to become affiliated with how
Photon is designed. It is intended for contributors or developers wishing to
understand the implementation details.

Each section provides a brief, conceptual overview and then discusses some
specific details afterwards.


## Entities
#### Overview
1. Entites do not exist as objects
2. There is no `entity` class of any kind

#### Note
An `entity` class may be implemented in the future. It would act as an interface
to the data stored in the Entity Manager.


## Components
#### Overview
1. `photon::Component` is the Basic structure from which other components are
   derived
2. `Component` is not a pure-data class. It contains helper functions in order
   to benefit from polymorphism.
3. `Component` (and derived classes) store some metadata as `protected` values

#### Details
1. Metadata:
    * `_identifierString`: A string which identifies the Component. This string
      should be unique and must not vary between two objects of the same type, so
      for any `IDComponent` object, `_identifierString = "idcomponent"`
    * `_activityStatus`: A boolean which controls whether the component is in use for
       a given entity 
2. Helper functions:
    * `IDString()`: Returns the `_identifierString` of a Component. Note: there
      is no related function to modify name
    * `Activate()` and `Deactivate`: Functions which change the active state of
      the component
    * `ISActive()`: Returns the activity status


## The Component Registry
#### Overview
1. The `ComponentRegistry` class is used to map components to indices for use
   in the Entity Manager
2. It's not intended to be directly interacted with

#### Details
1. `ComponentRegistry` has a vector of strings corresponding to the 
   `_identifierString` of various components. A string's index in the vector
   corresponds to the index of the collection of components in an Entity Manager
2. `ComponentRegistry` is a private member of an Entity Manager
3. `Register<Component C>()` will add a component to the registry by 
   retrieving the identifier string and adding it to the vector


## Systems
#### Overview
1. Currently, systems have very little fully-defined implementation. It is 
   intended to be derived from, similar to `Component`
2. Eventually, the goal is to have systems facilitate checking of entity 
   validity

#### Details
1. Metadata:
    * `_target` is a pointer to the Entity Manager that this system will act upon
    * `_actingIndices` is a vector of integers corresponding to the indices that
      the system is intended to operate on
        * This was a holdover from early prototypes of Photon and should not be
          expected to remain in the API without major changes
2. `Run()` is a virtual method which is provided with no code. It may be useful 
   for polymorphic systems, if those are desired.
3. `TargetComponent<Component C>()` and `UntargetComponent<Component C>()`
   add or remove indices corresponding to components that the system is intended
   to operate on
    * Like `_actingIndices` it is a holdover from early prototypes and its
      implementation will likely change drastically


## Entity Managers
#### Overview
1. Again, there are no entities
2. All usable entity managers must derive from `EntityManagerBase`, which leaves
   a few methods to be implemented
    * The user is intended to implement a constructor, destructor, and data 
      expansion method. A planned update may render the first two requirements
      obsolete
3. Component data is stored as vectors of various components, accessible via 
   pointers to those vectors. The pointers are stored in a vector of `any`
   objects (you can read a bit more about C++17's `std::any` [here][1]). This
   vector of `any` objects is called the `componentCollection`
4. Because of the above, an "entity" can be considered as a single component
   from each vector, all of which share the same index. See the table below for
   an example. In Photon, an entity is only an index used to access various 
   components within the collection

| Component Collection Vectors   	| Entity "0" 	| Entity "1" 	| ...          	|
|--------------------------------	|------------	|------------	|--------------	|
| IDComponent vector `IDVec`     	| `IDVec[0]` 	| `IDVec[1]` 	| `IDVec[...]` 	|
| RenderComponent vector `RCVec` 	| RCVec[0]   	| `RCVec[1]` 	| `RCVec[...]` 	|

#### Details
1. Metadata:
    * `_entityCount`: Maintains a simple count of how many entities exist 
      within the entity manager. Modified upon addition or removal of an entity;
      the value is not calculated every frame. For this reason, one should use
      `AddEntity()` and `RemoveEntity(uint entity)` to change this value
        * Additionally, `AddEntity()` can use this value to add an entity in
          O(1) time
    * `_indexCount`: `EntityManagerBase` resizes its vectors, it does not
      reserve and rely on `push_back` to add values. `_indexCount` is one 
      greater than the highest-accessible index in the collection
    * `_componentRegistry`: The entity manager's private component registry
2. Helper Functions:
    * `GetEntityCount()`: returns `_entityCount`_
    * `GetComponentVectorIndex<Component C>()`: a function that accesses the
      component registry and retrieves position of the collection element 
      containing that vector
    * `RegisterComponent<Component C>()` adds a listing the component registry,
      creates the associated vector in heap memory, and adds a reference to the
      collection
3. Entity Management Functions:
    * `AddEntity()`: Sets the first deactivated entity it can find to activated
    * `AddEntities(uint count)`: Batch initialization of entities
    * `RemoveEntity(uint enitty)`: Deactivate the entity at that index
        * This does not change any other components
    * `SetComponentActiveState<Component C>(uint, bool)`: Sets an entity's
      component's activity status
4. Virtual Functions:
    * `Expand()`: called when the collection needs to allocate more space for
      data
    * `Grow<Component C>()`: `Expand()` should be defined in derived classes
      and called for each component in the collection
    * There is a virtual destructor
    * To simplify deletion, `Destroy<Component>()` can be called, which 
      properly deletes component data by dereferencing the pointer inside the
      any object, and then resets the `any` object in the collection so there's
      no dangling pointer


[1]: http://en.cppreference.com/w/cpp/utility/any