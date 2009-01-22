#ifndef PLANE_HPP
#define PLANE_HPP

#include <math.h>

#include "Vertex.hpp"
#include "Line.hpp"

namespace radio {

    class Plane {

	public:
	    Plane(const Vertex& v1, const Vertex& v2, const Vertex& v3)
		: normal(vertexCross(v3 - v2, v1 - v2)), d(v1 * normal)
	    {}

	    Plane(const Vertex& normal_, const Vertex point) 
		:normal(normal_), d(point * normal)
            {}

	    Vertex calcIntersect(const Line& l){
		const float denom = normal * l.getDir();

		if(fabsf(denom) < 0.01f)
		    throw NoIntersectException();

		const float t = (normal * l.getStart() + d) / denom;

		return l.getStart() + (t * l.getDir());
	    }

            inline const Vertex& getNormal() const { return normal; }
            inline const D() const {return d; } 

	    class NoIntersectException{};

	private:
	    Vertex normal;
	    float d;

    };

    
}

#endif
