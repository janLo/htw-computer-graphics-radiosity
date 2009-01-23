#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "BSphere.hpp"

namespace radio {

    class Polygon {
	
	inline void makeTriangle(){
	    if(3 <= vertices.size()){
		std::vector<Vertex>::reverse_iterator it = vertices.rbegin();
                
		Vertex& c = *it;
		Vertex& b = *(++it);
		Vertex& a = *(++it);

		triangles.push_back(Triangle(a,b,c));
	    }
	}

	
	public:
	Polygon()
	    : vertices()
	{}

	inline void addVertex(const Vertex& v) {
	    vertices.push_back(v);
	    makeTriangle();
	    bSphere.recalc(v);
	}

	inline bool isDrawable() const {
	    return 3 > vertices.size();
	}

	inline bool checkSphere(const Line& l) const {
	    return bSphere.hitSphere(l);
	}

        typedef std::vector<Triangle>::iterator TriangleIterator;
        
        TriangleIterator getTriangleBegin() { return triangles.begin(); }
        TriangleIterator getTriangleEnd() { return triangles.end(); }

	private:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
	BSphere bSphere;

    };
}
#endif
