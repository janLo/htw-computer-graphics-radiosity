#include "Patch.hpp"

namespace radio {

    const float Patch::oneThird = 1.0f/3.0f;

    Patch::Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_)
	: Triangle(a_, b_, c_, col, p_, emit_), mid(oneThird * (a_ + b_ + c_)), 
	area(0.5f * abs(getTrianglePlane().getNormal())), 
	sphere(a_,b_,c_)
    {
	lastLight = getLight();
    }
}
