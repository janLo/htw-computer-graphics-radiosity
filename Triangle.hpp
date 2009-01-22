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

	    Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_)
	        :a(a_), b(b_), c(c_)
	    {
	    }

	    inline const Vertex& A() const { return a; }
	    inline const Vertex& B() const { return b; }
	    inline const Vertex& C() const { return c; }

	    inline const Vertex& operator[](int idx) const {
		switch (idx) {
		    case A_VERTEX:
			return a;
		    case B_BERTEX:
			return b;
		    case C_VERTEX:
			return c;
		}
	    }

	private:
	    Vertex a;
	    Vertex b;
	    Vertex c;
    };
}

#endif
