#include "Vertex.hpp"
namespace radio {
    /*Vertex::Vertex(float x_, float y_, float z_) 
	: x(x_), y(y_), z(z_), normed(false)
    {}*/


    void Vertex::norm(){
	if (!normed){
	    this->operator/=(radio::abs(*this));
	    normed = true;
	}
    }

    Vertex Vertex::getNormed() const {
        if (normed)
    	   return Vertex(*this);
        return Vertex((*this)/radio::abs(*this));
    }


}
