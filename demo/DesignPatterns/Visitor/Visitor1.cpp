#include <iostream>
using namespace std;

class Visitor;
class Element;

class Element
{
public:
    virtual void accept(Visitor& visitor) = 0; //第一次多态辨析

    virtual ~Element(){}
};

class Visitor{
public:
    virtual void visitElementA(Element* element) = 0;
    virtual void visitElementB(Element* element) = 0;

    virtual ~Visitor(){}
};


class ElementA : public Element
{
public:
    void accept(Visitor &visitor) override {
        visitor.visitElementA(this);
    }


};

class ElementB : public Element
{
public:
    void accept(Visitor &visitor) override {
        visitor.visitElementB(this); //第二次多态辨析
    }

};

//==================================

//扩展1
class Visitor1 : public Visitor{
public:
    void visitElementA(Element* element) override{
        cout << "Visitor1 is processing ElementA" << endl;
    }

    void visitElementB(Element* element) override{
        cout << "Visitor1 is processing ElementB" << endl;
    }
};

//扩展2
class Visitor2 : public Visitor{
public:
    void visitElementA(Element* element) override{
        cout << "Visitor2 is processing ElementA" << endl;
    }

    void visitElementB(Element* element) override{
        cout << "Visitor2 is processing ElementB" << endl;
    }
};

        
int main()
{
    Visitor2 visitor;
    ElementB elementB;
    elementB.accept(visitor);// double dispatch
    
    ElementA elementA;
    elementA.accept(visitor);

    
    return 0;
}