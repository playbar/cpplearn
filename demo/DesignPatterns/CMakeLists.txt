##########
## Create
add_executable(FactoryMethod
        FactoryMethod/main.cpp
        FactoryMethod/FactoryMethod.cpp
        FactoryMethod/factory.cpp)
add_executable(AbstractFactory
        AbstractFactory/main.cpp
        AbstractFactory/AbstractFactory.cpp
        AbstractFactory/product.cpp)
add_executable(Builder          Builder/main.cpp Builder/Builder.cpp Builder/director.cpp)
add_executable(Singleton        Singleton/main.cpp Singleton/Singleton.cpp)
add_executable(Prototype        Prototype/main.cpp Prototype/Prototype.cpp)

## Struct
add_executable(Adapter          Adapter/main.cpp Adapter/Adapter.cpp)
add_executable(Bridge           Bridge/main.cpp Bridge/abstractionImp.cpp Bridge/Bridge.cpp)
add_executable(Composite        Composite/main.cpp Composite/Composite.cpp)
add_executable(Decorator        Decorator/main.cpp Decorator/Decorator.cpp)
add_executable(Facade           Facade/main.cpp Facade/Facade.cpp)
add_executable(Flyweight        Flyweight/main.cpp Flyweight/Flyweight.cpp)
add_executable(Proxy            Proxy/main.cpp Proxy/Proxy.cpp)


### Behavior
add_executable(ChainofResposibility
        ChainofResposibility/main.cpp
        ChainofResposibility/ChainOfResposibility.cpp
        ChainofResposibility/ChainofResposibility1.cpp
        ChainofResposibility/Handle.cpp)
add_executable(Command          Command/main.cpp Command/Command.cpp)
add_executable(Interpreter      Interpreter/main.cpp Interpreter/Interpreter.cpp Interpreter/Interpreter1.cpp)
add_executable(Iterator         Iterator/main.cpp Iterator/Iterator.cpp Iterator/Aggregate.cpp)
add_executable(Mediator         Mediator/main.cpp Mediator/Mediator.cpp Mediator/Colleague.cpp)
add_executable(Memento          Memento/main.cpp Memento/Memento.cpp Memento/Memento3.cpp Memento/Memento4.cpp)
add_executable(Observer         Observer/main.cpp Observer/Observer.cpp Observer/Subject.cpp)
add_executable(State            State/main.cpp State/State.cpp State/StateContext.cpp State/State_1.cpp)
add_executable(Strategy         Strategy/main.cpp Strategy/Strategy.cpp Strategy/StrategyContext.cpp)
add_executable(TemplateMethod   TemplateMethod/main.cpp
        TemplateMethod/TemplateMethod.cpp
        TemplateMethod/TemplateMethod1.cpp
        TemplateMethod/TemplateMethod2.cpp
        )
add_executable(Visitor          Visitor/main.cpp Visitor/Visitor.cpp Visitor/Element.cpp)
add_executable(Visitor1          Visitor/Visitor1.cpp)

## other
add_executable(Simplefactory    Simplefactory/main.cpp Simplefactory/SimplyFactory.cpp)
add_executable(TemplatePattern  TemplatePattern/main.cpp )

