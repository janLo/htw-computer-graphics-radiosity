#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <boost/lexical_cast.hpp>

#include "math.h"

namespace radio {

    class Vertex {

	public:


	    enum {
		X_VAL,
		Y_VAL,
		Z_VAL
	    };

	    Vertex(float x_, float y_, float z_);

	    Vertex& norm();
	    Vertex getNormed() const;

	    float X() const { return x; }
	    float Y() const { return y; }
	    float Z() const { return z; }

	    inline float operator[](int idx) const {
		switch (idx){
		    case X_VAL: 
			return x;
		    case Y_VAL: 
			return y;
		    case Z_VAL:
			return z;
		}
		return x;
	    }

	    inline float operator*(const Vertex& rhs) const {
		const Vertex& lhs = *this;
		return rhs.x * lhs.x + rhs.y * lhs.y + rhs.z * lhs.z;
	    }

	    inline std::string toString() const { 
		std::string x_ = boost::lexical_cast<std::string, float>(x);
		std::string y_ = boost::lexical_cast<std::string, float>(y);
		std::string z_ = boost::lexical_cast<std::string, float>(z);
		return std::string("("+x_+","+y_+","+z_+")"); 
	    }

	private:
	    float x;
	    float y;
	    float z;
	    bool normed;

	    friend Vertex operator + (const Vertex& v, const Vertex& w);
	    friend Vertex operator - (const Vertex& v, const Vertex& w);
	    friend Vertex operator * (const Vertex& v, float f);
	    friend Vertex operator * (float f, const Vertex& v);
	    friend Vertex operator / (const Vertex& v, float f);
            friend Vertex vertexCross(const Vertex& lhs, const Vertex& rhs);
	    
    };


    inline Vertex operator + (const Vertex& v, const Vertex& w) {
	Vertex returnVert(v.x + w.x, v.y + w.y, v.z + w.z);
	return returnVert;
    }

    inline Vertex operator - (const Vertex& v, const Vertex& w) {
	Vertex returnVert(v.x - w.x, v.y - w.y, v.z - w.z);
	return returnVert;
    }

    inline Vertex operator * (const Vertex& v, float f) {
	Vertex returnVert(v.x * f, v.y * f, v.z * f);
	return returnVert;
    }

    inline Vertex operator * (float f, const Vertex& v) {
	Vertex returnVert(v.x * f, v.y * f, v.z * f);
	return returnVert;
    }


    inline Vertex operator / (const Vertex& v, float f) {
	float invF = 1/f;
	Vertex returnVert(v.x * invF, v.y * invF, v.z * invF);
	return returnVert;
    }

    inline Vertex vertexCross(const Vertex& lhs, const Vertex& rhs) {
	return Vertex( lhs.y * rhs.z - lhs.z * rhs.y,
	               lhs.z * rhs.x - lhs.x * rhs.z,
	               lhs.x * rhs.y - lhs.y * rhs.x);
    }

    inline float abs(const Vertex& v){
	return sqrt(v*v);
    }

}

#endif
