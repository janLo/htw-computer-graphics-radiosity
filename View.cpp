#include "View.hpp"

namespace radio {
    
    View * View::instance = 0;

    void dispHelper(){
	View::instance->glDisplayFunc();
    }
    void resizeHelper(int x, int y){
	View::instance->glResizeFunc(x,y);
    }
}
