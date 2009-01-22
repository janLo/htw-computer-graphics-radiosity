#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace radio {

    class Vertex {

	public:


	    enum {
		X_VAL,
		Y_VAL,
		Z_VAL
	    };

	    Vertex(float x_, float y_, float z_) 
	    {
		x = x_; 
		y = y_; 
		z = z_;
	    }

	    float operator[](int idx) const {
		switch (idx){
		    case X_VAL: 
			return x;
		    case Y_VAL: 
			return y;
		    case Z_VAL:
			return z;
		}
	    }

	private:
	    float x;
	    float y;
	    float z;

	    friend Vertex operator + (Vertex v, Vertex w);
	    friend Vertex operator - (Vertex v, Vertex w);
	    friend Vertex operator * (Vertex v, float f);
	    friend Vertex operator * (float f, Vertex v);
	    friend Vertex operator / (Vertex v, float f);
	    
    };


    inline Vertex operator + (Vertex v, Vertex w) {
	Vertex returnVert(v.x + w.x, v.y + w.y, v.z + w.z);
	return returnVert;
    }

    inline Vertex operator - (Vertex v, Vertex w) {
	Vertex returnVert(v.x - w.x, v.y - w.y, v.z - w.z);
	return returnVert;
    }

    inline Vertex operator * (Vertex v, float f) {
	Vertex returnVert(v.x * f, v.y * f, v.z * f);
	return returnVert;
    }

    inline Vertex operator * (float f, Vertex v) {
	Vertex returnVert(v.x * f, v.y * f, v.z * f);
	return returnVert;
    }


    inline Vertex operator / (Vertex v, float f) {
	float invF = 1/f;
	Vertex returnVert(v.x * invF, v.y * invF, v.z * invF);
	return returnVert;
    }



}

#endif
