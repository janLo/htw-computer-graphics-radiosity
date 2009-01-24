#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>

#include "Vertex.hpp"
#include "Plane.hpp"
#include "Colour.hpp"

namespace radio {


    class Triangle {
        public:

            enum {
                A_VERTEX = 0,
                B_BERTEX = 1,
                C_VERTEX = 2
            };

            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_)
                :a(a_), b(b_), c(c_), p(b,a,c)
            {
                std::cout << p.toString() << std::endl;
            }

            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col)
                :a(a_), b(b_), c(c_), p(b,a,c), colour(col)
            {
                std::cout << p.toString() << std::endl;
            }

	    inline const Colour& getColour() const { return colour; }

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

            inline bool pointInTriangle(const Vertex& v) {
                const Vertex& normal = p.getNormal();

//		std::cout << "Normal:" << normal.toString() << std::endl;
                //Vertex  temp(vertexCross(a - b, normal));
                Vertex  temp(vertexCross(b - a, normal));
                Plane pl1(temp, a);
//		std::cout << "Check:" << pl1.toString() << " .. " << v.toString() << std::endl;
                if( ( (pl1.getNormal() * v) + pl1.D() ) < 0.0f) 
                    return false;

                // Test mit der zweiten Ebene entlang den Punkten B und C
                //temp = vertexCross(b - c, normal);
                temp = vertexCross(c - b, normal);
                Plane pl2(temp, b);
//		std::cout << "Check:" << pl2.toString() << " .. " << v.toString() << std::endl;
                if( ( (pl2.getNormal() * v) + pl2.D() ) < 0.0f)
                    return false; 

                // Test mit der dritten Ebene entlang den Punkten C und A
                //temp = vertexCross(c - a, normal);
                temp = vertexCross(a - c, normal);
                Plane pl3(temp, c);
//		std::cout << "Check:" << pl3.toString() << " .. " << v.toString() << std::endl;
                if( ( (pl3.getNormal() * v) + pl3.D() )  < 0.0f)
                    return false;

                return true;
            }

        private:
            Vertex a;
            Vertex b;
            Vertex c;
            Plane p;
	    Colour colour;
    };
}

#endif
