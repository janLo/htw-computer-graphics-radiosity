#include "Vertex.hpp"
#include "Scene.hpp"
#include <GL/glut.h>

namespace radio {


}



int main(int argc, char * argv[]) {
    
    using namespace radio;

    View view(100,100, argc, argv);
    Scene test(view,2000,Vertex(0,0,0), Vertex(100,0,0), Vertex(0,100,0));
    test.render();
    view.display();
    
    

}
