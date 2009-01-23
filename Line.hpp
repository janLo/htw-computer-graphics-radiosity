#ifndef LINE_HPP
#define LINE_HPP

#include "Vertex.hpp"

namespace radio {

    class Line {

	public:
	    Line(const Vertex& start_, const Vertex& dir_) 
		: start(start_), dir(dir_)
	    {}

	    static inline Line fromPoints(const Vertex& a, const Vertex& b) {
		return Line(b, b - a);
	    }

	    inline float startX() const { return start.X(); }
	    inline float startY() const { return start.Y(); }
	    inline float startZ() const { return start.Z(); }

	    inline const Vertex& getStart() const { return start; }

	    inline float dirX() const { return dir.X(); }
	    inline float dirY() const { return dir.Y(); }
	    inline float dirZ() const { return dir.Z(); }

	    inline const Vertex getDir() const { return dir; }

	private:
	    Vertex start;
	    Vertex dir;

    };
}

#endif
