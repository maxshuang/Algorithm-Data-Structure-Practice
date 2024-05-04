#define CATCH_CONFIG_MAIN
#include <algorithm>
#include "iterator.hpp"
#include "catch.hpp"

TEST_CASE("Test Iterator interface", "Iterator") {
    const int g_total=10;
    std::forward_list<int> fl;
    for(int i=0; i<g_total; ++i) {
        fl.push_front(i);
    }

    SECTION("test iterator") {
        SListIterator<int> sli(fl.begin());
        REQUIRE(*sli==9);
        ++sli;
        REQUIRE(*sli==8);

        // modify
        SListIterator<int> sli3(fl.begin());
        *sli3=11;
        REQUIRE(*fl.begin()==11);
    }

    SECTION("test std::algorithm") {
        SListIterator<int> sli_s(fl.begin());
        SListIterator<int> sli_e(fl.end());
        int i=9;
        std::for_each(sli_s, sli_e, [&i](const int& e){
            REQUIRE(e==i);
            --i;
        });

        std::vector<int> tmp(g_total, -1);
        std::copy(sli_s, sli_e, tmp.begin());

        std::vector<int> tmp2;
        std::copy(sli_s, sli_e, std::back_inserter(tmp2));
    }

    SECTION("test const_iterator") {
        SListIterator<const int, const int*, const  int&> sli_s(fl.cbegin());
        SListIterator<const int, const int*, const  int&> sli_e(fl.cend());
        int i=9;
        std::for_each(sli_s, sli_e, [&i](const int& e){
            REQUIRE(e==i);
            --i;
        });

        // modify
        //SListIterator<const int, const int*, const  int&> sli1(fl.cbegin());
        //*sli1=11;
        //REQUIRE(*fl.begin()==11);
    }
}