# To-Do
This is just a scratch list for features that are under consideration or in
development. There are no guarantees that items on this list will be completed,
and this list has no order. It is intended to be a collection of notes about
where improvements to Photon can take place.


### Component
  * masks instead of `_activityStatus`
  * integer id instead of string should make for faster comparisons
    * But might necessitate the use of a global variable for the next ID to
      use
  * maybe design a copy and/or move constructor?

### ComponentRegistry
  * if component goes to integer ids, be ready to support that
  * if possible, store types and retrieve?

### EntityManager
  * Better, streamlined interfaces
    * Easily modify an entity's component data
    * Batch modify component data
    * Batch remove
    * Batch everything
  * Multithreading?
  * Messaging service between systems?
    * How would it be done, and
    * How can it be kept lightweight
  * expand() causes performance to fall off of a cliff (.3 ms vs 19 ms)

### System
  * Use better methods to handle entities. Current one is janky and not
    guaranteed to function.
  * Systems will have a lot to implement if components get changed
  * Thread safety if multithreading becomes supported
  * Message service support if that becomes a thing
