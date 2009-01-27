#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Vertex.hpp"
#include "PolygonTriangle.hpp"
#include "BSphere.hpp"
#include "Colour.hpp"

namespace radio {

    class Polygon {
	
	inline void makeTriangle(){
	    if(3 <= vertices.size()){
		std::vector<Vertex>::reverse_iterator it = vertices.rbegin();
                
		if (0 == (vertices.size() % 2)){
		    Vertex& a = *it;
		    Vertex& b = *(++it);
		    Vertex& c = *(++it);
		    triangles.push_back(PolygonTriangle(a,b,c, colour, light));
		} else {
		    Vertex& c = *it;
		    Vertex& b = *(++it);
		    Vertex& a = *(++it);
		    triangles.push_back(PolygonTriangle(a,b,c, colour, light));
		}
	    }
	}

	
	public:
	Polygon(const Colour& c, float light_)
	    : vertices(), colour(c), light(light_), enabled(true)
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

	inline bool isEnabled() const { return enabled; }
	inline void disable() { enabled = false; }


#ifdef USE_OMP_2
        inline std::vector<PolygonTriangle>& getTriangleVec() {return triangles;}
#endif

        typedef std::vector<PolygonTriangle>::iterator TriangleIterator;
        
        TriangleIterator getTriangleBegin() { return triangles.begin(); }
        TriangleIterator getTriangleEnd() { return triangles.end(); }

	private:
	std::vector<Vertex> vertices;
	std::vector<PolygonTriangle> triangles;
	BSphere bSphere;
	Colour colour;
        float light;
	bool enabled;

    };
}
#endif
