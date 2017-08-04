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
    * `Name()`: Returns the `_identifierString` of a Component. Note: there is
      no related function to modify name
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