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
    class PatchTriangle;

    class Triangle {
        public:

            enum {
                A_VERTEX = 0,
                B_BERTEX = 1,
                C_VERTEX = 2
            };

            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_);
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, float emit_, float reflex_);
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_, float reflex_);

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
	    static void split(std::vector<PatchTriangle>& store, const Triangle& t);
	    static void split(std::vector<Patch>& store, const Triangle& t);
            inline void addToLightSum(float add) { sum += add; }
            inline void updateLight() { 
	        allSum += sum;
                if (allSum/Triangle::scale > 1.0f)
		    Triangle::scale = allSum;
                sum = 0;
            }
            //inline float getLight() const { return emit + reflex * (allSum) ; }
            inline float getLight() const { return emit + reflex * (allSum) / Triangle::scale; }

        private:

	    static inline Vertex splitEdge(const Vertex& a, const Vertex& b){
		return a + ((b-a) / 2.0f);
	    }

            Vertex a;
            Vertex b;
            Vertex c;
            Plane p;
	    Colour colour;
            float emit;

	protected:
            float light;
//            float lastLight;

	private:
            float sum;
	    float allSum;
            float reflex;
	    float scale;
    };


    class PatchTriangle : public Triangle{
	public:
	    PatchTriangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_, float reflex_)
		:Triangle(a_, b_,  c_, col, p_, emit_, reflex_), sphere(a_,b_,c_)
	    {
		Triangle::split(patches, *this);
	    }
	    typedef std::vector<Patch>::iterator PatchIterator;

	    inline PatchIterator getPatchBegin() { return patches.begin(); }
	    inline PatchIterator getPatchEnd()   { return patches.end();   }
            inline int patchCount() const { return patches.size(); }

	    inline bool inBSphere(const Vertex x){
		return sphere.inSphere(x);
	    }
	private:
	    std::vector<Patch> patches;
	    BSphere sphere;

    };



}

#endif
