#include "Vertex.hpp"
#include "Scene.hpp"
#include <GL/glut.h>

namespace radio {


}



int main(int argc, char * argv[]) {
    
    using namespace radio;

    Scene test(100,100,2000,Vertex(0,0,0), Vertex(100,0,0), Vertex(0,100,0));
    std::cout << "do render" << std::endl;
    test.render();
    
    

}
