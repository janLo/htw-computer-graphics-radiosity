#ifndef PATCH_HPP
#define PATCH_HPP

#include "BSphere.hpp"
#include "Triangle.hpp"

namespace radio {

    class Triangle;
    class Patch : public Triangle {

	public:
	    Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_)
		:Triangle(a_, b_, c_, col, p_), mid(0,0,0), sphere(a_,b_,c_)
		{
		//    std::cout << "New Patch, Color: " + col.toString() << std::endl;
		/* TODO Fläche und Mittelpunkt */
		}

	    inline bool inBSphere(const Vertex x){
		return sphere.inSphere(x);
	    }

	private:
	    Vertex mid;
	    float area;
	    BSphere sphere;

    };
}

#endif
