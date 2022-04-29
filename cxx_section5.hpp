#include <iostream>
#include <string>

class B
{
    std::string bs;

public:
    virtual ~B() { std::cout << "~B()" << std::endl; }
};

class D : public B
{
    std::string ds;
    ~D() { std::cout << "~D()" << std::endl; }

};

int main()
{
    B* bp = new D;
    delete bp;

    return 0;
}
