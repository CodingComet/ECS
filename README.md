# ECS - Entity Component System

This is a basic header only entity component system library, that uses C++20 ranges, views.

<!-- ## Description -->

<!-- An in-depth paragraph about your project and overview of use. -->

### Usage

- Download and include header files

Create ComponentManager with components as template arguments:

```
ComponentManager<Base, Transform> component_manager
```

A System is an object that holds entities and a function that takes components and a shared state.

```
void name_system_callback(SharedState state&, Base &b, Transform &t)
{
	std::cout << b.name << std::endl;
}

System<decltype(component_manager), SharedState, Base, Transform> name_system(name_system_callback);
```

EntityManager requires no initialization:

```
EntityManager entity_manager;
```

Create an Entity and add components:

```
Entity player(entity_manager);

player.add_component<Base>(component_manager);
player.add_component<Transform>(component_manager);

player.get_component<Base>(component_manager).value()->name = "Stephane Legar";
```

Filter entities for a system and then execute it:
```
name_system.filter_entities(entity_manager);

name_system.execute(component_manager, state);
```
