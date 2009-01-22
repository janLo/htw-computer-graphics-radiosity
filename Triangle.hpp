#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vertex.hpp"
#include "Plane.hpp"

namespace radio {


    class Triangle {
        public:

            enum {
                A_VERTEX = 0,
                B_BERTEX = 1,
                C_VERTEX = 2
            };

            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_)
                :a(a_), b(b_), c(c_), p(a,b,c)
            {
            }

            inline const Vertex& A() const { return a; }
            inline const Vertex& B() const { return b; }
            inline const Vertex& C() const { return c; }

            inline const Vertex& operator[](int idx) const {
                switch (idx) {
                    case A_VERTEX:
                        return a;
                    case B_BERTEX:
                        return b;
                    case C_VERTEX:
                        return c;
                }
            }

            inline const Plane& getTrianglePlane() const { return p; }

            inline bool pointInTriangle(const Vertex& v)
                const Vertex& normal = p.getNormal();
            const Vertex  temp(vertexCross(a - b, normal));

            Plane pl1(temp, a);
            if( ( (pl1.getNormal() * v) + pl1.D() ) < 0.0f) 
                return false;

            // Test mit der zweiten Ebene entlang den Punkten B und C
            temp = vertexCross(b - c, normal);
            Plane pl2(temp, b);
            if( ( (pl2.getNormal() * v) + pl2.D() ) < 0.0f)
                return false; 

            // Test mit der dritten Ebene entlang den Punkten C und A
            temp = vertexCross(c - a, normal);
            Plane pl3(temp, c);
            if( ( (pl3.getNormal() * v) + pl3.D() )  < 0.0f)
                return false;

            return true;
    }

    private:
    Vertex a;
    Vertex b;
    Vertex c;
    Plane p;
};
}

#endif
