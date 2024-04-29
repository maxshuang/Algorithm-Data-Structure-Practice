#pragma once

struct EdgeComp
{
    bool operator()(const Edge &l, const Edge &r) const { return l.Weight() > r.Weight(); }
};