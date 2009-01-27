#ifndef POLYGONTRIANGLE_HPP
#define POLYGONTRIANGLE_HPP

#include "Patch.hpp"
#include "Triangle.hpp"

namespace radio {
    class PolygonTriangle : public Triangle {
        public:
	    PolygonTriangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, float emit_)
		:Triangle(a_, b_,  c_, col, emit_)
	    {
	        Triangle::split(patches, *this);
		std::cout << "New Polygon Triangle, Normal: " << getTrianglePlane().toString() <<  std::endl;
	    }

	    typedef std::vector<PatchTriangle>::iterator PatchTriangleIterator;

	    inline PatchTriangleIterator getTriangleBegin() { return patches.begin(); }
	    inline PatchTriangleIterator getTriangleEnd()   { return patches.end();   }
            inline int triangleCount() const { return patches.size(); }

	private:
	    std::vector<PatchTriangle> patches;
    };

}

#endif
