#ifndef H_TUPLE
#define H_TUPLE

class Tuple {
    public:
        Tuple();
        Tuple(float x, float y, float z, float w);
        bool isPoint() const;
        bool isVector() const;
        float getByIndex(int i) const;
        void setByIndex(int i, float val);

        float x, y, z, w;
};

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);
float Magnitude(Tuple& t);
Tuple Normalize(Tuple& t);

float dot(Tuple& a, Tuple& b);
Tuple cross(Tuple& a, Tuple& b);

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& t);
Tuple operator*(const Tuple& lhs, const float scale);
Tuple operator/(const Tuple& lhs, const float scale);

#endif