# demo



set(SOURCE_DESIGNPATTERN
        DesignPatternsTest.cpp
        common/product_2.cpp
        Visitor/Visitor.cpp

        )

add_executable(DesignPatterns ${SOURCE_DESIGNPATTERN})

target_include_directories(DesignPatterns PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Builder
        ${CMAKE_CURRENT_SOURCE_DIR}/AbstractFactory
        ${CMAKE_CURRENT_SOURCE_DIR}/Adapter
        ${CMAKE_CURRENT_SOURCE_DIR}/Bridge
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ${CMAKE_CURRENT_SOURCE_DIR}/ChainofResposibility
        ${CMAKE_CURRENT_SOURCE_DIR}/Command
        ${CMAKE_CURRENT_SOURCE_DIR}/Composite
        ${CMAKE_CURRENT_SOURCE_DIR}/Decorator
        ${CMAKE_CURRENT_SOURCE_DIR}/Facade
        ${CMAKE_CURRENT_SOURCE_DIR}/FactoryMethod
        ${CMAKE_CURRENT_SOURCE_DIR}/Flyweight
        ${CMAKE_CURRENT_SOURCE_DIR}/Interpreter
        ${CMAKE_CURRENT_SOURCE_DIR}/Iterator
        ${CMAKE_CURRENT_SOURCE_DIR}/Mediator
        ${CMAKE_CURRENT_SOURCE_DIR}/Memento
        ${CMAKE_CURRENT_SOURCE_DIR}/Observer
        ${CMAKE_CURRENT_SOURCE_DIR}/Prototype
        ${CMAKE_CURRENT_SOURCE_DIR}/Proxy
        ${CMAKE_CURRENT_SOURCE_DIR}/Singleton
        ${CMAKE_CURRENT_SOURCE_DIR}/State
        ${CMAKE_CURRENT_SOURCE_DIR}/Strategy
        ${CMAKE_CURRENT_SOURCE_DIR}/TemplateMethod
        ${CMAKE_CURRENT_SOURCE_DIR}/Visitor
        )

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
add_executable(Singleton        Singleton/main.cpp)
add_executable(Prototype        Prototype/main.cpp Prototype/Prototype.cpp)

## Struct
add_executable(Adapter          Adapter/main.cpp Adapter/Adapter.cpp)
add_executable(Bridge           Bridge/main.cpp)
add_executable(Composite        Composite/main.cpp)
add_executable(Decorator        Decorator/main.cpp)
add_executable(Facade           Facade/main.cpp)
add_executable(Flyweight        Flyweight/main.cpp)
add_executable(Proxy            Proxy/main.cpp)


### Behavior
add_executable(ChainofResposibility ChainofResposibility/main.cpp)
add_executable(Command          Command/main.cpp)
add_executable(Interpreter      Interpreter/main.cpp)
add_executable(Iterator         Iterator/main.cpp)
add_executable(Mediator         Mediator/main.cpp)
add_executable(Memento          Memento/main.cpp)
add_executable(Observer         Observer/main.cpp)
add_executable(State            State/main.cpp)
add_executable(Strategy         Strategy/main.cpp)
add_executable(TemplateMethod   TemplateMethod/main.cpp)
add_executable(Visitor          Visitor/main.cpp Visitor/Visitor.cpp Visitor/Element.cpp)
add_executable(Visitor1          Visitor/Visitor1.cpp)

## other
add_executable(Simplefactory    Simplefactory/main.cpp Simplefactory/SimplyFactory.cpp)
