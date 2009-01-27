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
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, float emit_);
            Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_);

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
            inline void addToLightSum(const Colour& add) { 
	        sum += add; 
	    }
            inline void updateLight() { 
	        Colour old = getLight();
	        allSum += sum;
                sum = Colour(0.0f, 0.0f, 0.0f);
		lastLight = getLight() - old;
            }
            inline Colour getLastLight() const { return lastLight ; }
            inline const Colour getLight() const { return ((colour * emit) + (colour.mul(allSum))); }

	    inline bool buildCorner(const Triangle& other) {
		if ((getTrianglePlane().getNormedNormal() * other.getTrianglePlane().getNormedNormal()) != 0.0f)
		    return false;

		const Vertex* t[3] = {&a,&b,&c};
		const Vertex* o[3] = { &(other.a), &(other.b), &(other.c) };

		int match = 0;

		for (int i = 0; i < 3; i++){
		    for (int j = 0; j < 3; j++){
			if(t[i]->equal(*o[j])){
			    match++;
			    //std::cout << t[i]->toString() << o[j]->toString() << std::endl;
			}
		    }
		}

		return (match >= 2);
	    }


        private:

	    static inline Vertex splitEdge(const Vertex& a, const Vertex& b){
		return a + ((b-a) / 2.0f);
	    }

            Vertex a;
            Vertex b;
            Vertex c;
            Plane p;
	    Colour colour;

	protected:
            float emit;
            Colour lastLight;

	private:
            Colour sum;
	    Colour allSum;
    };


    class PatchTriangle : public Triangle{
	public:
	    PatchTriangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_)
		:Triangle(a_, b_,  c_, col, p_, emit_), sphere(a_,b_,c_)
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
