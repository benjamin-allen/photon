# Introduction to Photon
This document can get you up to speed on how to use Photon in your games.
Remember that Photon is still very early in its development and the API subject
to rapid change.

## Creating Components
Components are data structures which contain relevant data as well as some
metadata. A new component can be defined by inheriting from `photon::Component`.

```
struct PositionComponent : public Component {
    PositionComponent() : Component("positioncomponent") { }
    int x = 0;
    int y = 0;
};
```

The constructor simply needs to call the `Component` constructor with a string
which will be the identifier for all objects of type `PositionComponent`.


## Entity Manager
#### Implementing the entity manager
`photon::EntityManagerBase` is an class from which you can derive and implement
variations of the entity manager. `EntityManagerBase` contains
code to handle `IDComponent`, which is used to give entities `id` strings.
Additionally, entities whose IDComponents are not active are said to be inactive
themselves, so it is the standard check for whether an entity exists at that
index.

To just use `EntityManagerBase` for some quick experimentation you can implement

```
class EntityManager : public EntityManagerBase<> {
public:
    EntityManager() : EntityManagerBase()<> { }
};
```

However you're not going to make a very interesting game with just some strings.
Let's define an EntityManager that also has our `PositionComponent` from above.

```
class EntityManager : public EntityManagerBase<PositionComponent> {
public:
    EntityManager() : EntityManagerBase<PositionComponent>() { }
};
```

This class will have an `IDComponent` and a `PositionComponent`. These are
vectors of component data allocated on the heap and accessed via pointers found
in the `componentCollection`, a member variable of an entity manager.


#### Adding and modifying an entity
The following code creates an instance of our entity manager from before and 
adds an entity to it. Then it accesses the ID of the newly-created entity and
changes it to "foo."

```
EntityManager em;

unsigned int entity1 = em.addEntity();

auto idVec = em.getVectorReference<IDComponent>();
idVec->at(entity1).id = "foo";
```

Note that when you write systems the speed-optimized version will be slightly
different, but the principle is the same. Entities are activated when they are
added, so they will be processed by any subsequent calls to systems that rely
on their activated components.


#### Removing an entity
```
// Do stuff with PositionComponent...
// ...
em.removeEntity(entity1);
``` 

This function deactivates the entity's IDComponent, marking it as fully
deactivated, but no other data in the entity has been modified.

## Systems
Systems perform logic by iterating over the data within an entity manager and
modifying it or using it. Since the EntityManagerBase class is abstract but
systems still need to be able to access an entity manager, a system derived
from `photon::system` must have a template argument specifying what class of
entity manager it operates on. An instance of that entity manager class is
called the system's target.

Below is an example of a system that alter's a PositionComponent.

```
class MoveSystem : public System<EntityManager> {
public:
	MoveSystem(EntityManager* target) : System<EntityManager>(target) { }

	void run() {
		auto idPointer = &target()->getVectorReference<IDComponent>()->get(0);
		auto posPointer = &target()->getVectorReference<PositionComponent>()->get(0);
		int entities = target()->getEntityCount();
		int i = 0;
		while(i < entities) {
			if(idPointer->isActive() && posPointer->isActive()) {
				posPointer->x += 1;
				posPointer->y += 1;
			}
			// Instead of dereferencing a pointer to a component in a vector,
			// increment the pointer itself, which is safer since the components
			// are contiguous in memory anyways.
			++i; ++posPointer; ++idPointer;
		}
	}
```

The important part to note about systems is that their constructors accept an
argument to an entity manager. This is the "target", which allows the system
access to a given entity manager. The system's `run()` method performs logic.

To use a system:
```
MoveSystem ms(&em);
ms.run();
```

## Note
Photon is still early in its development and much of this API can and will 
change. Hopefully the changes will be fully documented when pushed onto the
master branch, but if you try to use an unstable branch there's no guarantee
any of the code laid out here will work. Or that Photon will even compile.

Particularly, expect Systems to change in 0.3. Making them easier to use is the
next goal.
