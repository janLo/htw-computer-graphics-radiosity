#ifndef PATCH_HPP
#define PATCH_HPP

#include "BSphere.hpp"
#include "Triangle.hpp"

namespace radio {

    class Triangle;
    class Patch : public Triangle {

	public:
	    Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_, float reflex_)
		: Triangle(a_, b_, c_, col, p_, emit_, reflex_), mid(oneThird * (a_ + b_ + c_)), 
                  area(0.5f * abs(getTrianglePlane().getNormal())), 
                  sphere(a_,b_,c_)
		{
		 //   std::cout << "New Patch, A: " << area  << "  " << 0.5f * abs(getTrianglePlane().getNormal()) << std::endl;
		/* TODO Fläche und Mittelpunkt */
		}

	    inline bool inBSphere(const Vertex x){
		return sphere.inSphere(x);
	    }

            inline const Vertex& getMid() const { return mid; }
            inline float getArea() const { return area; }

	private:

            static const float oneThird;

	    Vertex mid;
	    float area;
	    BSphere sphere;

    };
}

#endif
