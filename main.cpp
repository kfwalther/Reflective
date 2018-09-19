#include <boost/fusion/adapted/struct.hpp>
// #include <boost/fusion/include/for_each.hpp>
// #include <boost/phoenix/phoenix.hpp>
// using boost::phoenix::arg_names::arg1;

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp> 
#include <string>
#include <iostream>


// #define DUMPSTR_WNAME(os, name, a) do { (os) << (name) << " has value " << (a) << std::endl; } while(false)
#define DUMPSTR_WNAME(os, name, a) (os) << (name) << " has value " << (a) << std::endl

#define DUMP(a)     DUMPSTR_WNAME(std::cout, #a, (a))
#define DUMPSTR(os, a) DUMPSTR_WNAME((os), #a, (a))


enum Platform {
    UNKNOWN,
    SHIP,
    CAR,
    AIRCRAFT
};

struct A
{
    int a;
    int b;
    std::string c;
};


struct B : public A
{
    B(int a, int b, std::string c, double y, Platform plat) :
            A{a, b, c},
            y(y),
            plat(plat)
    {
        return;
    }
    
    double y;
    Platform plat;
};

enum EnumA {
    a,
    b,
    c
};

// struct Printer {
//     Printer() {};
    
//     template <class T>
//     void operator()(T & t) const {
//         auto fieldName = boost::fusion::extension::struct_member_name<T, 0>::call();
//         std::cout << fieldName << ": " << boost::lexical_cast<std::string>(t) << std::endl;
//         counter++;
//     }
    
//     unsigned int counter = 0;
// };

// template <typename T, int N = 0> void print(T const& obj) {
//     namespace fus = boost::fusion;
//     if (fus::traits::is_sequence<T>::value) {
//         if (N==0)
//             std::cout << "{";

//         if (N < fus::size(obj).value) {
//             auto name = boost::fusion::extension::struct_member_name<T, N>::call();
//             std::cout << ' ' << name << '=';
//             print(fus::at_c<N>(obj));
//             std::cout << ';';
//             print<T, N+1>(obj);
//         } else {
//             std::cout << " }";
//         }
//     } else {
//         std::cout << boost::lexical_cast<std::string>(obj);
//     }
// }

struct print_visitor {
    template<class Index, class C>
    void operator()(Index, C & c) {
        std::cout << boost::fusion::extension::struct_member_name<C, Index::value>::call() 
                  << "=" 
                  << boost::fusion::at<Index>(c) 
                  << std::endl;
    }
};


template<class C>
void print_fields(C & c)
{
    typedef boost::mpl::range_c<int, 0, boost::fusion::result_of::size<C>::type::value> range;
    boost::mpl::for_each<range>(boost::bind<void>(print_visitor(), _1, boost::ref(c)));
}


BOOST_FUSION_ADAPT_STRUCT(A, (int,a)(int,b)(std::string,c))
BOOST_FUSION_ADAPT_STRUCT(B, (int,a)(int,b)(std::string,c)(double,y)(Platform,plat))

int main()
{
    
    A objA = { 1, 42, "The Answer To LtUaE" };
    B objB = { 1, 42, "The Answer To LtUaE", 3.14, Platform::CAR };

    //unsigned int counter = 0;
    //boost::fusion::for_each(objA, Printer(arg1));

    print_fields(objA);
    print_fields(objB);
    
    // boost::fusion::for_each(objB, std::cout << arg1 << "\n");
    //boost::fusion::for_each(objB, std::cout << arg1 << "\n");
    std::cout << "Successful completion!" << std::endl;
}






