#pragma once
class Renderable;
class RenderableObject;
class Collider;

enum class ESortingPriority {
    EPIC = 16,
    LOW = 8,
    AVERAGE = 4,
    HIGH = 2,
    HIGHEST = 1
};

struct DrawCall {
    SDL_Texture* texture;
    int16_t sortingPriority;
    double rotation;
    Vector2d size;
    SDL_Rect srcRect;
    Transform wTransform;
    SDL_Point rotationPivot;

    DrawCall(Renderable* rEl, Transform wTrans);
};

struct DrawCallComparator {
    using _FIRST_ARGUMENT_TYPE_NAME = DrawCall;
    using _SECOND_ARGUMENT_TYPE_NAME = DrawCall;
    using _RESULT_TYPE_NAME = bool;
    bool operator()( DrawCall& lho,  DrawCall& rho) const;
};

////temporary collider utils
//struct ColliderComparator
//{
//    using _FIRST_ARGUMENT_TYPE_NAME = Collider;
//    using _SECOND_ARGUMENT_TYPE_NAME = Collider;
//    using _RESULT_TYPE_NAME = bool;
//    bool operator() (Collider* lhc, Collider* rhc) const;
//};

typedef std::priority_queue<DrawCall, std::vector<DrawCall>, DrawCallComparator> DrawQueue_t;
