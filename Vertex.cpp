#include "Vertex.hpp"
namespace radio {
    Vertex::Vertex(float x_, float y_, float z_) 
    {
        x = x_; 
        y = y_; 
        z = z_;
    }


    Vertex& Vertex::norm(){
	if (!normed){
	    *this = (*this)/radio::abs(*this);
	    normed = true;
	}
	return *this;
    }

    Vertex Vertex::getNormed() const {
        if (!normed)
    	return *this;
        return (*this)/radio::abs(*this);
    }


}
