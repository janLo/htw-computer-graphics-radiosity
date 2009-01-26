#include "Patch.hpp"

namespace radio {

    const float Patch::oneThird = 1.0f/3.0f;

    Patch::Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_, float reflex_)
	: Triangle(a_, b_, c_, col, p_, emit_, reflex_), mid(oneThird * (a_ + b_ + c_)), 
	area(0.5f * abs(getTrianglePlane().getNormal())), 
	sphere(a_,b_,c_)
    {
	//light *= area;
	//lastLight *= area;
	 //  std::cout << "New Patch, A: " << area  << "  " << 0.5f * abs(getTrianglePlane().getNormal())  << "    " << mid.toString() << std::endl;
	/* TODO Fläche und Mittelpunkt */
    }
}
