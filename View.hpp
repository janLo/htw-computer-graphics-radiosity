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
	    View(int w_, int h_, int argc, char** argv)
		:buffer(new GLfloat[w_ * h_ * 3]), w(w_), h(h_)
	    {
		::memset(buffer, 0, (sizeof(GLfloat) * w_ * h_ * 3));
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
		glutInitWindowPosition (1, 1);
		glutInitWindowSize(w, h);
		glutInit(&argc, argv);
		name = argv[0];
	    }

	    inline void setPixel(int x, int y, const Colour& c){

	        //std::cout << "write Pixel: (" << x << "," << y << ")" << std::endl;

		int offset = 3 * (w*y + x) ;

		buffer[offset]   = c.R();
		buffer[++offset] = c.G();
		buffer[++offset] = c.B();


	    }

	    void display(){
		glutCreateWindow (name.c_str());

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor (0.0, 0.0, 0.0, 1.0);

		instance = this;
		glutReshapeFunc(resizeHelper);
		glutDisplayFunc(dispHelper);

		glutMainLoop();

	    }

	    inline int getWidth() const {return w;}
	    inline int getHeight() const {return h;}


	    ~View() {
		delete[] buffer;
	    }


	private:
	    void glDisplayFunc(){
		glClear(GL_COLOR_BUFFER_BIT);
		glRasterPos2i(0,0);
		glDrawPixels(w,h,GL_RGB,GL_FLOAT,buffer);
		glFlush ();
	    }

	    void glResizeFunc(int x, int y){
		glViewport(0, 0, x, y);
		glMatrixMode(GL_PROJECTION);        /* specifies the current matrix */
		glLoadIdentity();                   /* Sets the currant matrix to identity */
		gluOrtho2D(0,x,0,y);
	    }

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
