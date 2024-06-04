#include "critical_path_method.hpp"
#include "helper/float.hpp"
#include "catch.hpp"

TEST_CASE("Test Critical Path Method for parallel job schedule", "[test]") {
    std::vector<Job> jobs;
    jobs.push_back(Job{0, 41.0, {1, 7, 9}});
    jobs.push_back(Job{1, 51.0, {2}});
    jobs.push_back(Job{2, 50.0, {}});
    jobs.push_back(Job{3, 36.0, {}});
    jobs.push_back(Job{4, 38.0, {}});
    jobs.push_back(Job{5, 45.0, {}});
    jobs.push_back(Job{6, 21.0, {3, 8}});
    jobs.push_back(Job{7, 32.0, {3, 8}});
    jobs.push_back(Job{8, 32.0, {2}});

    SECTION("CPM") {
        jobs.push_back(Job{9, 29.0, {4, 6}});
        CPM cpm(jobs);
        REQUIRE(cpm.IsDAG());
        REQUIRE(DoubleEqual(cpm.MinimumFinishTime(), 173.0));
        REQUIRE(cpm.ScheduleTime()==std::vector<double>{0.0, 41.0, 123.0, 91.0, 70.0, 0.0, 70.0, 41.0, 91.0, 41.0});
    }

    SECTION("NOT CPM") {
        jobs.push_back(Job{9, 29.0, {4, 6, 0}});
        CPM cpm(jobs);
        REQUIRE(!cpm.IsDAG());
        REQUIRE(DoubleEqual(cpm.MinimumFinishTime(), 0.0));
        REQUIRE(cpm.ScheduleTime()==std::vector<double>{});
    }
}