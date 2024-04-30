#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <algorithm>
#include <iostream>
#include "catch.hpp"
#include "iterator.hpp"
#include "iterator2.hpp"

TEST_CASE("iterator", "[iterator]"){
    std::forward_list<int> fl;
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    fl.push_front(4);

    SECTION("Test copy and assignment")
    {
        Iterator<int> iter(fl.begin());
        REQUIRE(*iter==4);
        auto iter2=iter;
        REQUIRE(*iter2==4);
        ++iter;
        REQUIRE(*iter==3);
        REQUIRE(*iter2==4);
        ++iter2;
        REQUIRE(*iter2==3);
        auto iter3(iter);
        REQUIRE(*iter3==3);
        auto iter4(iter2);
        REQUIRE(*iter4==3);
    }

    SECTION("Test increment")
    {
        Iterator<int> iter(fl.begin());
        Iterator<int> iter_end(fl.end());
        int i=4;
        for(; iter!=iter_end; ++iter, --i){
            REQUIRE(*iter==i);
        }
        REQUIRE(i==0);
    }

    SECTION("Test common algorithm")
    {
        Iterator<int> iter(fl.begin());
        Iterator<int> iter_end(fl.end());
        std::for_each(iter, iter_end, [](int& a){ std::cout << a << std::endl; });
    }
 }

 TEST_CASE("iterator2", "[iterator]"){
    std::forward_list<int> fl;
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    fl.push_front(4);

    SECTION("Test copy and assignment")
    {
        ConstIterator2<int> iter(fl.begin());
        REQUIRE(*iter==4);
        auto iter2=iter;
        REQUIRE(*iter2==4);
        ++iter;
        REQUIRE(*iter==3);
        REQUIRE(*iter2==4);
        ++iter2;
        REQUIRE(*iter2==3);
        auto iter3(iter);
        REQUIRE(*iter3==3);
        auto iter4(iter2);
        REQUIRE(*iter4==3);
    }

    SECTION("Test increment")
    {
        ConstIterator2<int> iter(fl.begin());
        ConstIterator2<int> iter_end(fl.end());
        int i=4;
        for(; iter!=iter_end; ++iter, --i){
            REQUIRE(*iter==i);
        }
        REQUIRE(i==0);
    }


    SECTION("Test common algorithm")
    {
        ConstIterator2<int> iter(fl.begin());
        ConstIterator2<int> iter_end(fl.end());
        std::for_each(iter, iter_end, [](const int& a){ std::cout << a << std::endl; });
    }
 }