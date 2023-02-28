#pragma once
class RenderObject;
class Collider;

enum class ESortingPriority {
    EPIC = 16,
    LOW = 8,
    AVERAGE = 4,
    HIGH = 2,
    HIGHEST = 1
};

struct RenderObjectComparator {
    using _FIRST_ARGUMENT_TYPE_NAME = RenderObject;
    using _SECOND_ARGUMENT_TYPE_NAME = RenderObject;
    using _RESULT_TYPE_NAME = bool;
    bool operator()( RenderObject* lho,  RenderObject* rho) const;
};

////temporary collider utils
//struct ColliderComparator
//{
//    using _FIRST_ARGUMENT_TYPE_NAME = Collider;
//    using _SECOND_ARGUMENT_TYPE_NAME = Collider;
//    using _RESULT_TYPE_NAME = bool;
//    bool operator() (Collider* lhc, Collider* rhc) const;
//};

typedef std::priority_queue<RenderObject*, std::vector<RenderObject*>, RenderObjectComparator> DrawQueue_t;
