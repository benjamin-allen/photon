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
variations of the entity manager. In each derivative class, you need to
implement a destructor and expansion functions. `EntityManagerBase` contains
code to handle `IDComponent`, which is used to give entities `id` strings.
Additionally, entities whose IDComponents are not active are said to be inactive
themselves, so it is the standard check for whether an entity exists at that
index.

To just use `EntityManagerBase` for some quick experimentation you can implement

```
class EntityManager : public EntityManagerBase {
public:
    EntityManager() : EntityManagerBase() { }
    ~EntityManager() { }
};
```

However you're not going to make a very interesting game with just some strings.
Three main actions must be defined by derivatives: construction, destruction, 
and expansion. So let's define an EntityManager that also has our 
`PositionComponent` from above.

```
class AnotherEntityManager : public EntityManagerBase {
public:
    AnotherEntityManager() : EntityManagerBase() {
        RegisterComponent<PositionComponent>();
    }
    ~AnotherEntityManager() {
        Destroy<PositionComponent>();
    }
    void Expand() {
        EntityManagerBase::Expand();
        Grow<PositionComponent>();
    }
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
AnotherEntityManager aem;

unsigned int entity1 = aem.AddEntity();

unsigned int i = aem.GetComponentVectorIndex<IDComponent>();
vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(aem.componentCollection[i]);

idVec->at(entity1).id = "foo";
```

In the above example an entity is created, its index stored in `entity1`, and
that index being used to access a position in the vector. A simplified interface
is planned. The best I can say about it at the moment is that we don't have to
deal with reassignment since we're dealing with pointers.


#### Activating components and removing an entity
Following the code snippet before...

```
aem.SetComponentActiveState<PositionComponent>(entity1, true);
// Do stuff with PositionComponent...
// ...
aem.RemoveEntity(entity1);
``` 

The `PositionComponent` object is activated and can now be considered as part of
the entity. Using the same process as above to retrieve the vector you can
modify the data at `PositionComponent`.


## Systems
Systems perform logic on entities. An implementation of one which hashes entity
ID strings is below.

```
class IDHashingSystem : public photon::System {
public:
	IDHashingSystem(EntityManager* e) : photon::System(e) { };

	void Run() {
		unsigned int cIndex = Target()->GetComponentVectorIndex<photon::IDComponent>();
		std::vector<photon::IDComponent>* idVec = std::any_cast<std::vector<photon::IDComponent>*>(Target()->componentCollection[cIndex]);
		for(int i = 0; i < idVec->size(); ++i) {
			if(idVec->at(i).IsActive()) {
				idVec->at(i).id = std::hash<std::string>{}(idVec->at(i).id);
			}
		}
	}
};
```

The important part to note about systems is that their constructors accept an
argument to an entity manager. This is the "target", which allows the system
access to a given entity manager. The system's `Run()` method loops through all
of the `IDComponents` and hashes the ID string of any active entity.

The following code shows the use of a system, where `aem` is the entity manager
implemented previously.

```
IDHashingSystem idhs(&aem);
idhs.Run();
```

## Note
Photon is still early in its development and much of this API can and will 
change. Hopefully the changes will be fully documented when pushed onto the
master branch, but if you try to use an unstable branch there's no guarantee
any of the code laid out here will work. Or that Photon will even compile.