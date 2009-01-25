#ifndef VIEW_HPP
#define VIEW_HPP
#include <boost/utility.hpp>
#include <GL/glut.h>
#include <string>
#include <string.h>
#include <iostream>

#include "Colour.hpp"

namespace radio {

    void dispHelper();
    void resizeHelper(int x, int y);

    class View : public boost::noncopyable {

	public:
	    View(int w_, int h_, int argc, char** argv);

	    inline void setPixel(int x, int y, const Colour& c) {

		int offset = 3 * (w*y + x) ;

		buffer[offset]   = c.R();
		buffer[++offset] = c.G();
		buffer[++offset] = c.B();
	    }

	    void display();

	    inline int getWidth() const {return w;}
	    inline int getHeight() const {return h;}


	    ~View();


	private:
	    void glDisplayFunc();
	    void glResizeFunc(int x, int y);

	    GLfloat* buffer;
	    int w;
	    int h;
	    std::string name;
	    static View *instance;

	    friend void dispHelper();
	    friend void resizeHelper(int, int);
    };




}
#endif
