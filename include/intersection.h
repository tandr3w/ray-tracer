#ifndef H_INTERSECTION
#define H_INTERSECTION

class Intersection {
    public:
        Intersection(float _t, const void* _object);
        float t;
        const void* object;
};

#endif