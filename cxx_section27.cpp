#include <iostream>

class Trace;

class Channel
{
    friend class Trace;
    std::ostream* trace_file;

public:
    Channel(std::ostream *o): trace_file(o) { std::cout << "Channel()" << std::endl; }
    void reset(std::ostream *o) { trace_file = 0; }
};

class Trace
{
public:
//    Trace(const char *s, Channel* c):name_(s), c_(c)
    Trace(const char *s, Channel* c)
    {
        name_ = s;
        c_ = c;
        if(c_->trace_file)
            *c_->trace_file <<  "begin##" << name_ << std::endl;
    }

    ~Trace()
    {
        if(c_->trace_file)
            *c_->trace_file << "end##" << name_ << std::endl;
    }

private:
    Channel *c_;
    const char *name_;
};


void foo()
{
    Channel c(&std::cout);
    Trace t("foo", &c);
    std::cout << "do something" << std::endl;
}
