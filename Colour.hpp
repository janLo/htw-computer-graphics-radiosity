#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "Vertex.hpp"

namespace radio {
 
    class Colour : public Vertex {

	public: 
	    Colour(float r_, float g_, float b_) 
		: Vertex(r_, g_, b_)
	    {}

	    Colour(const Vertex& v)
		:Vertex(v)
	    {}

	    Colour()
		: Vertex(0,0,0)
	    {}

	    inline float R() const { return X(); }
	    inline float G() const { return Y(); }
	    inline float B() const { return Z(); }
	private:
    };



}

#endif
