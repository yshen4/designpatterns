# A review of design patterns

In this repository, I will review several most commonly used design patterns:
- Singleton: [singleton2.py](singleton/singleton2.py)
  The singleton pattern is a software design pattern that restricts the instantiation of a class to one "single" instance.
  
  The singleton design pattern solves problems like:
  - How can it be ensured that a class has only one instance?
  - How can the sole instance of a class be accessed easily?
  - How can a class control its instantiation?
  - How can the number of instances of a class be restricted?
  - How to hide the constructor of the class.
  - Define a public static operation (getInstance()) that returns the sole instance of the class.
  
  ----
  ![Singleton](singleton/singleton.gif?raw=true "Singleton Pattern")
  ----
- Builder
- Prototype
- Adapter
- Bridge
- Decorator
- Flyweight
- Chain of Responsibility
- Command
- Mediator
- Momento
- Observer
- State
- Strategy
- Visitor

# Structure

Each of design patterns will have its own folder, which contains its own README and implementations.

I will add python and C++ implementation first. Will add other language later.

There are many books and online tutorials discussing those design patterns, i.e. [.net design patterns](https://www.dofactory.com/net/design-patterns). In order to make the example clear, they use many trivial examples. In this repository, I will try to use real use cases I encountered in my work. 
