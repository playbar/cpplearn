#include <iostream>

class CaffeineBeverage {
public:
    virtual ~CaffeineBeverage(){}

    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if(customerWantsCondiments())
            addCondiments();
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    virtual bool customerWantsCondiments() {
        return true;
    }
};

class Tea : public CaffeineBeverage {
public:
    ~Tea(){}

    void brew() {
        std::cout << "Steeping the tea\n";
    }

    void addCondiments() {
        std::cout << "Adding Lemon\n";
    }

    bool customerWantsCondiments()
    {
        char c;
        std::cout << "Do you want to add condiments?\n";
        std::cin >> c;

        if (c == 'y')
            return true;
        else
            return false;
    }
};

class Coffee : public CaffeineBeverage {
public:
    ~Coffee(){}

    void brew() {
        std::cout << "Dripping Coffee through filter\n";
    }

    void addCondiments() {
        std::cout << "Adding Sugar and Milk\n";
    }

    bool customerWantsCondiments() {
        char c;
        std::cout << "Do you want to add condiments?\n";
        std::cin >> c;

        if(c == 'y')
            return true;
        else
            return false;
    }
};


int main() {
    Tea* tea = new Tea();
    Coffee* coffee = new Coffee();

    std::cout << "\nMaking tea...\n";
    tea->prepareRecipe();

    std::cout << "\nMaking coffee...\n";
    coffee->prepareRecipe();

    delete tea;
    delete coffee;
}