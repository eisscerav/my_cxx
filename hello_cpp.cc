#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <utility> //std::pair
#include <unordered_map>
#include <inttypes.h>
#include <cmath>
#include <chrono>

//#include "gtest/gtest.h"
//#include "cuda_fp16.h"
//#include "cuComplex.h"
//#include "file_operation.hpp"
//#include "cxx_section5.hpp"
//#include "cxx_section8.hpp"
//#include "cxx_section27.hpp"
#include "matrix_mul.hpp"

//int main(int argc, char *argv[])
//{
////    ::testing::InitGoogleTest(&argc, argv);
////    return RUN_ALL_TESTS();
//    std::true_type my;
//    foo(my);
//
//    std::is_same<void, void>::type non1;
//    std::is_same<void, char>::type non2;
//    foo(non1);
//    foo(non2);
//
//    int a[] = {1,2,3,4,5};
//    size_t len = sizeof(a);
//
//    foo(my);
//
//    double tol = 1e9;
//
//    std::cout << tol << std::endl;
//    return 0;
//}

// tuple example
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore



/* global function runs before main() */
//int func()
//{
//    std::cout << "a" << std::endl;
//    return 110;
//}

//int a = func();

#include "cxx_section10.hpp"
using namespace std;

void bar(const char * ss[], int n)
{
//    strlen(ss[n]);
}

int string_exer()
{
//    vector<int> a = { 2,4,6,7,1,0,8,9,6,3,2 };
//    auto maxPosition = max_element(a.begin(), a.end());
//    cout << *maxPosition << " at the postion of " << maxPosition - a.begin() <<endl;
//    //cout << a[maxPosition - a.begin()] << " at the postion of " << distance(a.begin(), maxPosition) << endl;
//    system("pause");
    std::string name1 = "cutensorTest -Pac -Pbc -Pcc -Pcompc -Pcompc  -modeCm,n -modeAm,k -modeBn,k -extentm=2048,n=2048,k=2048 -algo-101";
    std::string name2 = "-Pas";
    std::string name3 = "-Pbs";
    std::string name4 = "-Pcd";
    std::string name5 = "-Pcompd";
    std::string name6 = "-Pac";
    std::cout << name1 << std::endl;
    string::size_type pos = 0;
    string::size_type posC = 0;

    if ((pos = name1.rfind("-Pa")) != string::npos)
    {
    //resource_str.replace(pos, sub_str.length(), new_str);
//        name1.replace(pos, name2.length(), name2);
        name1.replace(pos, name2.length(), "");
    }
    if ((pos = name1.rfind("-Pb")) != string::npos)
    {
        name1.replace(pos, name3.length(), name3);
    }
    pos = name1.rfind("-Pcomp");
    posC = name1.rfind("-Pc");
    while ( posC == pos )
    {
        if ( posC == string::npos && pos == string::npos )
            break;
        pos = name1.rfind("-Pcomp", pos-1);
        posC = name1.rfind("-Pc", posC-1);
    }
    if ( posC != string::npos)
    {
        name1.replace(posC, name4.length(), name4);
    }
    if ((pos = name1.rfind("-Pcomp")) != string::npos)
    {
        name1.replace(pos, name5.length(), name5);
    }
    else
    {
        name1.insert(posC+5, name5+" ");
    }

    std::cout << name1 << std::endl;
//    section10();
    return 0;
}

class B
{
protected:
    void foo()
    {
        std::cout << "B::foo()" << std::endl;
    }
};

class D : public B
{
public:
    void bar()
    {
        foo();
    }

    static void baz() {}
};

void foo(int *x)
{
    *x = 20;
}

#define MYTEST(ts) ts();

void myTestCase()
{
    printf("running %s\n", __func__);
}


class AA{
public:
    static int n;
};

//int AA::n;


int main()
{
    typedef struct {
        int sunday:1;
        int monday:1;
        // more days
        int friday:1;
        int saturday:1;
    } weekdays;

    typedef struct {
        int sunday;
        int monday;
        // more days
        int friday;
        int saturday;
    } fuweekdays;

    weekdays week;
    fuweekdays fuweek;
    std::cout << sizeof(week) << std::endl;
    std::cout << sizeof(fuweek) << std::endl;
    bool isnan_ = std::isnan(std::sqrt(-1.0));
    if(isnan_) {
        std::cout << "nan produced: "<< std::sqrt(-1.0) << std::endl;
    }
    return 0;
}
