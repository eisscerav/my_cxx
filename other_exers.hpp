#include <iostream>
#include <list>
#include <algorithm>
#include <chrono>
#include "gtest/gtest.h"

typedef enum {
    AA,
    BB,
    CC,
} T1_t;

class CPUTimer
{
public:
    void record()
    {
        start = std::chrono::steady_clock::now();
    }

    void stop()
    {
        end = std::chrono::steady_clock::now();
    }

    double duration()
    {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        elapseds = std::chrono::duration_cast<std::chrono::seconds>(end-start);

        return elapsed.count();
    }

    void print_result(std::string name)
    {
        printf("%s duration: %e\n", name.c_str(), duration());
    }

private:
    typedef std::chrono::steady_clock::time_point tp;
    tp start;
    tp end;
    std::chrono::milliseconds elapsed;
    std::chrono::seconds elapseds;

    //  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
//    std::chrono::duration<double> elapsed;
};

//Initialize static member in source, otherwise hitting undefined reference issue


class Base
{
public:
    Base()
    {
        std::cout << "Base constructor" << std::endl;
    }

    virtual void SetUp(int n)
    {
        std::cout << "Base SetUp()" << std::endl;
    }

    void foo(int n){}
};

class Derived : public Base, public testing::Test
{
public:
    Derived()
    {
        std::cout << "Derived constructor" << std::endl;
    }
protected:
    virtual void SetUp()
    {
        std::cout << "Derived SetUp" << std::endl;
        Base::SetUp(1);
    }
};


TEST_F(Derived, test1)
{
    EXPECT_EQ(1,1);
}

class Derived_P : public Base/*, public testing::TestWithParam< std::tuple<
                                                    std::vector<int>,
                                                    std::vector<int> > > */
{
public:
    Derived_P()
    {
        std::cout << "Derived constructor" << std::endl;
    }
protected:
    virtual void SetUp()
    {
        std::cout << "Derived SetUp" << std::endl;
        Base::SetUp(1);
    }

    int n_;
};

class Derived_PD: public Derived_P, public testing::TestWithParam< std::tuple<
                                                    std::vector<int>,
                                                    std::vector<int> > >
{
public:
    virtual void SetUp()
    {
        std::vector<int> vec = std::get<0>(GetParam());
        Derived_P::SetUp();
    }
};

TEST_P(Derived_PD, test2)
{
//    int n1 = std::get<0>(GetParam());
    std::vector<int> vec = std::get<0>(GetParam());
    int n11 = vec[0];
    int n12 = vec[1];
    std::vector<int> vec2 = std::get<1>(GetParam());

    int n2 = vec2[0];

    std::cout << "n11 = " << n11 << "; n12 = " << n12 << "; n2 = " << n2 << std::endl;
    std::cout << "derived_PD::n_ = " << n_ << std::endl;
}

std::vector<int> v1 = {1,3};
std::vector<int> v2 = {5,7};

std::vector<int> vv1 = {5};
std::vector<int> vv2 = {7};

INSTANTIATE_TEST_CASE_P(
    CUTENSOR_TEST,
    Derived_PD,
    ::testing::Combine(
        ::testing::Values(v1, v2),
        ::testing::Values(vv1, vv2)
    ));

//INSTANTIATE_TEST_CASE_P(m_images_dir
//        CUTENSOR_TEST,
//        Derived_P,
//        ::testing::Values(
//            std::make_tuple(1,2),
//            std::make_tuple(3,4)
//        ));

class AA
{
public:
    static void setDir(int n) { age = n;}

protected:
    static std::string name;
    static int age;
};


int AA::age;

void try_list()
{
    std::list<int> lst;
    std::list<int> l2;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    l2.push_back(100);

    std::list<int>::iterator it = std::find(lst.begin(), lst.end(), 10); // 查找list中是否有元素“10”
}

typedef struct Handle{
    int fields[4];
} handle_t;

typedef struct mystruct
{
    int age;
    int income;
    short pay;
    char x;
    char y;

    void setAge(int n)
    {
        this->age = n;
    }
} mystruct_t;

void demo_reinterpret_case()
{
    handle_t h;
    mystruct_t *ff = reinterpret_cast<mystruct_t *>(&h);
//    mystruct_t *sp = static_cast<mystruct_t *>(&h); compile error
    ff->setAge(20);
    ff->income = 3000;
    ff->pay = 20;
    ff->x = 'x';
    ff->y = 'y';
    for(int i = 0; i < 4; i++)
    {
        std::cout << h.fields[i] << std::endl;
    }
}


class Person
{
public:
    static void setAge(int n )
    {
        age_ = n;
    }
//protected:
    static int age_;
private:
    void foo()
    {
        std::cout << "Person::foo()" << std::endl;
    }
};

void foo(std::true_type t)
{
    std::cout << "true_type" << std::endl;
}

void foo(std::false_type f)
{
    std::cout << "false_type" << std::endl;
}

typedef struct student{
    int age;
} student_t;

class foo{
    student_t s;
};
