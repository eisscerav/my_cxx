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

class Vehicle
{
public:
    virtual double weight() const = 0;
    virtual void start() const = 0;
    virtual Vehicle *copy() const = 0;
    virtual ~Vehicle() { }
};

class Truck : public Vehicle
{
public:
    virtual double weight() const {
        std::cout << "Truck weight" << std::endl;
        return 11;
    }
    virtual void start() const {
        std::cout << "Truck start" << std::endl;
    }
    virtual Vehicle *copy() const{
        return new Truck(*this);
    }
    ~Truck() {}
};

class Bus : public Vehicle
{
public:
    virtual double weight() const {
        std::cout << "Bus weight" << std::endl;
        return 22;
    }
    virtual void start() const {
        std::cout << "Bus start" << std::endl;
    }
    virtual Vehicle *copy() const{
        return new Bus(*this);
    }
    ~Bus() {}
};

//todo: more class derived from Vehicle

class VehicleSurrogate {
public:
    VehicleSurrogate();
    VehicleSurrogate(const Vehicle &);
    ~VehicleSurrogate();
    VehicleSurrogate(const VehicleSurrogate &);
    VehicleSurrogate& operator=(const VehicleSurrogate &);

    double weight() {
        if(vp == 0) {
            throw "Empty Vehicle";
        }
        return vp->weight();
    }
    void start() {
        if(vp == 0) {
            throw "Empty Vehicle";
        }
        vp->start();
    }
private:
    Vehicle *vp;
};

VehicleSurrogate::VehicleSurrogate() : vp(0) {}
VehicleSurrogate::VehicleSurrogate(const Vehicle &v) : vp(v.copy())
{
    std::cout << "VehicleSurrogate::VehicleSurrogate(const Vehicle &v)" << std::endl;
}
VehicleSurrogate::~VehicleSurrogate() { delete vp; }
VehicleSurrogate::VehicleSurrogate(const VehicleSurrogate &v) : vp(v.vp? v.vp->copy():0)
{
    std::cout << "VehicleSurrogate::VehicleSurrogate(const VehicleSurrogate &v)" << std::endl;
}
VehicleSurrogate &
VehicleSurrogate::operator=(const VehicleSurrogate &v)
{
    std::cout << "VehicleSurrogate::operator=" << std::endl;
    if(this != &v) {
        delete vp;
        vp = (v.vp ? v.vp->copy() : 0);
    }
    return *this;
}

int main()
{
    VehicleSurrogate park[2];
    Truck tk;
    Bus bs;
    park[0] = tk;
    park[1] = bs;
    park[0].weight();
    park[0].start();
    B* bp = new D;
    delete bp;

    return 0;
}

