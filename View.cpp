#include "View.hpp"

namespace radio {
    
    View * View::instance = 0;

    void dispHelper(){
	View::instance->glDisplayFunc();
    }
    void resizeHelper(int x, int y){
	View::instance->glResizeFunc(x,y);
    }

    View::View(int w_, int h_, int argc, char** argv)
        :buffer(new GLfloat[w_ * h_ * 3]), w(w_), h(h_)
    {
        ::memset(buffer, 0, (sizeof(GLfloat) * w_ * h_ * 3));
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
        glutInitWindowPosition (1, 1);
        glutInitWindowSize(w, h);
        glutInit(&argc, argv);
        name = argv[0];
    }

    void View::display(){
        glutCreateWindow (name.c_str());

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor (0.0, 0.0, 0.0, 1.0);

        instance = this;
        glutReshapeFunc(resizeHelper);
        glutDisplayFunc(dispHelper);

        glutMainLoop();

    }

    void View::glDisplayFunc(){
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2i(0,0);
        glDrawPixels(w,h,GL_RGB,GL_FLOAT,buffer);
        glFlush ();
    }

    void View::glResizeFunc(int x, int y){
        glViewport(0, 0, x, y);
        glMatrixMode(GL_PROJECTION);        /* specifies the current matrix */
        glLoadIdentity();                   /* Sets the currant matrix to identity */
        gluOrtho2D(0,x,0,y);
    }

    View::~View() {
        delete[] buffer;
    }
}
