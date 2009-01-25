#ifndef BSPHERE_HPP
#define BSPHERE_HPP

#include <iostream>

#include "Vertex.hpp"
#include "Line.hpp"


namespace radio {


    class BSphere {

	public: 
	    BSphere()
		:xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0), center(0,0,0), rad(0), initialized(false)
	    {}

	    BSphere(const Vertex& a, const Vertex& b, const Vertex& c)
		:xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0), center(0,0,0), rad(0), initialized(false)
	    {
		check(a);
		check(b);
		check(c);
		calc();
	    }

	    inline void recalc(const Vertex& last) {
		check(last);
		calc();
	    }
	    
	    inline bool hitSphere(const Line& l) const {
		      Vertex  d = l.getDir();
		const Vertex& o = l.getStart();
		const Vertex& c = center;
		const Vertex diff = o - c;

                d.norm();

//		std::cout << abs(d)  << " " << d.toString()<< std::endl;

		float a = 2.0f * (d.X() * diff.X() + 
			          d.Y() * diff.Y() + 
			          d.Z() * diff.Z());
		float b = diff * diff - rad * rad;

		float tmp = ((a * a) *0.25f) - b ;
	//	std::cout << "tmp:"<<tmp<<std::endl;

		if (tmp < 0.0f)
		    return false;

		return true;
	    }

	    inline bool inSphere(const Vertex v){
		Vertex ve(v - center);
		if ( ve*ve <= radSquare )
		    return true;
		return false;
	    }


	private:

	    inline void check(const Vertex& last){
		if (!initialized){
		    xMin = last.X();
		    yMin = last.Y();
		    zMin = last.Z();
		    xMax = last.X();
                    yMax = last.Y();
		    zMax = last.Z();
		    initialized = true;
		} else {
		    if (last.X() < xMin)
			xMin = last.X();
		    if (last.Y() < yMin)
			yMin = last.Y();
		    if (last.Z() < zMin)
			zMin = last.Z();

		    if (last.X() > xMax)
			xMax = last.X();
		    if (last.Y() > yMax)
			yMax = last.Y();
		    if (last.Z() > zMax)
			zMax = last.Z();
		}
	    }

	    inline void calc(){
		Vertex maxV(xMax,yMax,zMax);
		Vertex minV(xMin,yMin,zMin);
                Vertex dist((maxV - minV) / 2.0f);

		center = minV + dist;

		rad = abs((maxV - minV) / 2.0f);
		radSquare = rad*rad;

		/*std::cout << "x: " << xMin << "-" << xMax;
		std::cout << " y: " << yMin << "-" << yMax;
		std::cout << " z: " << zMin << "-" << zMax << std::endl;*/
		//std::cout << "Sphere at " << center.toString() << "with rad: "<< rad << std::endl;
	    }

	    float xMin;
	    float xMax;
	    float yMin;
	    float yMax;
	    float zMin;
	    float zMax;

	    Vertex center;
	    float rad;
	    float radSquare;
            bool initialized;
    };
}
#endif
