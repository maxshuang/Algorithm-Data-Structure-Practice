#pragma once
#include "directed_graph/digraph.hpp"
#include "acyclicLP.hpp"

// CPM(Critical Path Method) for Parallel job scheduling in DAG(Directed Acyclic Graph)

struct Job
{
    Job(int id, double d, std::vector<int> dds) : index(id), duration(d), dependees(dds) {}
    // assume index is [0, N)
    int index;
    double duration;
    std::vector<int> dependees;
};

// Critical Path Method
class CPM
{
public:
    CPM(const std::vector<Job> &jobs) : jobs_size_(jobs.size()), minimum_finished_time_(0.0), isDAG_(true)
    {
        Digraph g(vertices());
        buildGraph(jobs, g);

        // check if DAG
        Topological tp(g);
        isDAG_ = tp.IsDAG();
        if (!isDAG_)
            return;

        // get critical path
        AcyclicLP alp(g, source());
        minimum_finished_time_ = alp.DistTo(sink());
        for (int i = 0; i < jobs_size_; ++i)
            schedule_time_.push_back(alp.DistTo(vertice_st(i)));
    }

    bool IsDAG() const { return isDAG_; }

    // minimum finished time for all vertices
    double MinimumFinishTime() const { return minimum_finished_time_; }

    // schedule time for all vertices
    std::vector<double> ScheduleTime() const { return schedule_time_; }

private:
    void buildGraph(const std::vector<Job> &jobs, Digraph &g)
    {
        // every job has three base edges: <source, vertice_st, 0>, <vertice_st, vertice_ed, dist>, <vertice_ed, sink, 0>
        // for all dependees: <vertice_ed, dependee, 0>
        for (const Job &j : jobs)
        {
            g.AddEdge(source(), vertice_st(j.index));
            g.AddEdge(vertice_st(j.index), vertice_ed(j.index), j.duration);
            g.AddEdge(vertice_ed(j.index), sink());
            for (int i : j.dependees)
            {
                g.AddEdge(vertice_ed(j.index), vertice_st(i));
            }
        }
    }

    // [vertice0_st, vertice1_st,..., verticeN_st, vertice0_ed, vertice1_ed, ..., verticeN_ed, source, sink]
    int vertice_st(int index) const { return index; }
    int vertice_ed(int index) const { return jobs_size_ + index; }
    int source() const { return jobs_size_ << 1; }
    int sink() const { return (jobs_size_ << 1) + 1; }
    int vertices() const { return (jobs_size_ << 1) + 2; }

private:
    int jobs_size_;
    double minimum_finished_time_;
    std::vector<double> schedule_time_;
    bool isDAG_;
};