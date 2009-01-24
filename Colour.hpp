#ifndef COLOUR_HPP
#define COLOUR_HPP

namespace radio {
 
    class Colour {

	public: 
	    Colour(float r_, float g_, float b_) 
		: r(r_), g(g_), b(b_)
	    {}

	    Colour()
		:r(0),g(0),b(0)
	    {}

	    inline float R() const { return r; }
	    inline float G() const { return g; }
	    inline float B() const { return b; }
	private:
	    float r;
	    float g;
	    float b;
    };

}

#endif
