#include "Vertex.hpp"
#include "Scene.hpp"
#include <GL/glut.h>

namespace radio {


}



int main(int argc, char * argv[]) {
    
    using namespace radio;

    View view(500,500, argc, argv);
    RoomScene test(view,300,Vertex(0,0,0), Vertex(100,0,0), Vertex(0,100,0));
    //Scene test(view,300,Vertex(0,0,0), Vertex(100,0,0), Vertex(0,100,0));
    test.render();
    //view.display();
    
    

}
