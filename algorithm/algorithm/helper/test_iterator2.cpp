#include <algorithm>
#include "iterator3.hpp"
#include "catch.hpp"

TEST_CASE("Test Iterator interface", "Iterator") {
    std::forward_list<int> fl;
    for(int i=1; i<10; ++i) {
        fl.push_front(i);
    }

    SECTION("test iterator") {
        SListIterator<int> sli(fl.begin());
        REQUIRE(*sli==1);
        ++sli;
        REQUIRE(*sli==2);
        SListIterator<int> sli2=sli++;
        REQUIRE(*sli==3);
        REQUIRE(*sli2==2);
        REQUIRE(sli!=sli2);
        ++sli2;
        REQUIRE(sli==sli2);

        // modify
        SListIterator<int> sli3(fl.begin());
        *sli3=11;
        REQUIRE(*fl.begin()==11);
    }

    SECTION("test std::algorithm") {
        SListIterator<int> sli_s(fl.begin());
        SListIterator<int> sli_e(fl.end());
        int i=1;
        std::for_each(sli_s, sli_e, [&i](const int& e){
            REQUIRE(e==i);
            ++i;
        });
    }

    SECTION("test const_iterator") {
        SListIterator<int, const int*, const  int&> sli_s(fl.begin());
        SListIterator<int, const int*, const  int&> sli_e(fl.end());
        int i=1;
        std::for_each(sli_s, sli_e, [&i](const int& e){
            REQUIRE(e==i);
            ++i;
        });

        // modify
        SListIterator<int, const int*, const  int&> sli1(fl.begin());
        //*sli1=11;
        //REQUIRE(*fl.begin()==11);
    }
}