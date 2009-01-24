#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include <vector>

#include "Vertex.hpp"
#include "Plane.hpp"
#include "Colour.hpp"
#include "BSphere.hpp"

namespace radio {

    class Patch;

    class Triangle {
        public:

            enum {
                A_VERTEX = 0,
                B_BERTEX = 1,
                C_VERTEX = 2
            };

            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_);
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col);
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_);

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

                Vertex  temp(vertexCross(b - a, normal));
                Plane pl1(temp, a);
                if( ( (pl1.getNormal() * v) + pl1.D() ) < 0.0f) 
                    return false;

                temp = vertexCross(c - b, normal);
                Plane pl2(temp, b);
                if( ( (pl2.getNormal() * v) + pl2.D() ) < 0.0f)
                    return false; 

                temp = vertexCross(a - c, normal);
                Plane pl3(temp, c);
                if( ( (pl3.getNormal() * v) + pl3.D() )  < 0.0f)
                    return false;

                return true;
            }

	    virtual ~Triangle(){}
	    static void split(std::vector<Patch>& store, const Triangle& t);

        private:

	    static inline Vertex splitEdge(const Vertex& a, const Vertex& b){
		return a + ((b-a) / 2.0f);
	    }

            Vertex a;
            Vertex b;
            Vertex c;
            Plane p;
	    Colour colour;
    };

    class Patch : public Triangle {

	public:
	    Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_)
		:Triangle(a_, b_, c_, col, p_), mid(0,0,0), sphere(a_,b_,c_)
		{
		/* TODO Fläche und Mittelpunkt */
		}

	private:
	    Vertex mid;
	    float area;
	    BSphere sphere;

    };

    class PolygonTriangle : public Triangle {
        public:
	    PolygonTriangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col)
		:Triangle(a_, b_,  c_, col)
	    {
	        Triangle::split(patches, *this);
	    }

	    typedef std::vector<Patch>::iterator PatchIterator;

	    inline PatchIterator getPatchBegin() { return patches.begin(); }
	    inline PatchIterator getPatchEnd()   { return patches.end();   }

	private:
	    std::vector<Patch> patches;
    };


}

#endif
