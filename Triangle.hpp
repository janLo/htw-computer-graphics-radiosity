#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vertex.hpp"

namespace radio {


    class Triangle {
	public:

	    enum {
		A_VERTEX = 0,
		B_BERTEX = 1,
		C_VERTEX = 2
	    };

	    Triangle(const Vertex& a, const Vertex& b, const Vertex& c)
	        :a_(a), b_(b), c_(c)
	    {
	    }

	    inline const Vertex& a() const { return a_; }
	    inline const Vertex& b() const { return b_; }
	    inline const Vertex& c() const { return c_; }

	    inline const Vertex& operator[](int idx) const {
		switch (idx) {
		    case A_VERTEX:
			return a_;
		    case B_BERTEX:
			return b_;
		    case C_VERTEX:
			return c_;
		}
	    }

	private:
	    Vertex a_;
	    Vertex b_;
	    Vertex c_;
    };
}

#endif
