#ifndef PATCH_HPP
#define PATCH_HPP

#include "BSphere.hpp"
#include "Triangle.hpp"

namespace radio {

    class Triangle;
    class Patch : public Triangle {

	public:
	    Patch(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_);

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
