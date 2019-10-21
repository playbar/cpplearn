#include <iostream>
#include "Facade.hpp"

class scanner
{
public:
    void scan()
    {
        std::cout << "词法分析" << std::endl;
    }
};

class parser
{
public:
    void parse()
    {
        std::cout << "语法分析" << std::endl;
    }
};

class gen_mid_code
{
public:
    void gen_code()
    {
        std::cout << "产生中间代码" << std::endl;
    }
};

class gen_machine_code
{
public:
    void gen_code()
    {
        std::cout << "产生机器码" << std::endl;
    }
};

class compiler
{
public:
    void run()
    {
        scanner s;
        s.scan();

        parser p;
        p.parse();

        gen_mid_code min_code;
        min_code.gen_code();

        gen_machine_code machine_code;
        machine_code.gen_code();
    }
};

void testFacade()
{
    compiler c;
    c.run();
}

int main()
{
    testFacade();
    test_Facade1();
    return 0;
}
