//
// Created by mac on 2019-05-25.
//

#ifndef CPPLEARN_BASE_H
#define CPPLEARN_BASE_H

class Base
{
public:

    Base(int i) :baseI(i){};

    int getI(){ return baseI; }

    static void countI(){};

    virtual void print(void){ cout << "Base::print()"; }

    virtual ~Base(){}

private:

    int baseI;

    static int baseS;
};


#endif //CPPLEARN_BASE_H
