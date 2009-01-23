#include "Vertex.hpp"
#include "Line.hpp"


namespace radio {


    class BSphere {

	public: 
	    BSphere()
		:xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0), center(0,0,0), rad(0)
	    {}

	    inline void recalc(const Vertex& last) {

		if (last.X() < xMin)
		    xMin = last.X();
		if (last.Y() < yMin)
		    yMin = last.Y();
		if (last.Z() < zMin)
		    zMin = last.Z();

		if (last.X() < xMax)
		    xMax = last.X();
		if (last.Y() < yMax)
		    yMax = last.Y();
		if (last.Z() < zMax)
		    zMax = last.Z();

		calc();
	    }
	    
	    inline bool hitSphere(const Line& l) const {
		const Vertex& d = l.getDir();
		const Vertex& o = l.getStart();
		const Vertex& c = center;

		float a = 2 * (d.X() * (o.X() - c.X()) + 
			       d.Y() * (o.Y() - c.Y()) + 
			       d.Z() * (o.Z() - c.Z()));
		float b = pow(o.X() - c.X(), 2) +
		          pow(o.Y() - c.Y(), 2) +
			  pow(o.Z() - c.Z(), 2) - 
			  pow(rad, 2);

		float tmp = (pow(a, 2) / 4) - b ;

		if (tmp < 0)
		    return false;

		return true;
	    }

	private:


	    inline void calc(){
		float radX = ((xMax - xMin) / 2);
                float centerX = xMin + radX;

		float radY = ((yMax - yMin) / 2);
		float centerY = yMin + radY;

		float radZ = ((zMax - zMin) / 2);
		float centerZ = zMin + radZ;

		center = Vertex(centerX, centerY, centerZ);

		rad = ((radX < radY) ? radY : radX );
		rad = ((rad  < radZ) ? radZ : rad  );
	    }

	    float xMin;
	    float xMax;
	    float yMin;
	    float yMax;
	    float zMin;
	    float zMax;

	    Vertex center;
	    float rad;
    };
}
