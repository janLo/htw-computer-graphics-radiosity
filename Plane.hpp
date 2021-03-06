#ifndef PLANE_HPP
#define PLANE_HPP

#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "Vertex.hpp"
#include "Line.hpp"

namespace radio {

    class Plane {

	public:
	    Plane(const Vertex& v1, const Vertex& v2, const Vertex& v3)
		: normal(vertexCross(v3 - v2, v1 - v2)), normed(normal.getNormed()), d(-(v1 * normal))
	    {
               //std::cout << "Plane from" << (v3 - v2).toString() << ", " << (v1 - v2).toString() << ": " << toString() << std::endl;
            }

	    Plane(const Vertex& normal_, const Vertex point) 
		:normal(normal_), normed(normal.getNormed()), d(-(point * normal))
            {
//               std::cout << "Plane from" << (normal).toString() << " on " << point.toString() << ": " << toString() << std::endl;
	    }

	    class Intersect {
		public: 
		    Intersect(const Vertex& p_, float d_)
			:p(p_), d(d_)
		    {}
		    inline float getDistance() const {return d;}
		    inline const Vertex& getPoint() const {return p;}

		private:
		    Vertex p;
		    float d;
	    };

	    Intersect calcIntersect(const Line& l) const {
		const float denom = normal * l.getDir();

		if(fabsf(denom) < 0.01f)
		    throw NoIntersectException();

		const float t = (normal * l.getStart() + d) / -denom;

		return Intersect(l.getStart() + (t * l.getDir()), t);
	    }

            inline const Vertex& getNormal() const { return normal; }
            inline const Vertex& getNormedNormal() const { return normed; }
            inline const float D() const {return d; } 

            inline std::string toString() const { 
                std::string x_ = boost::lexical_cast<std::string, float>(normal.X());
                std::string y_ = boost::lexical_cast<std::string, float>(normal.Y());
                std::string z_ = boost::lexical_cast<std::string, float>(normal.Z());
                std::string d_ = boost::lexical_cast<std::string, float>(d);
                return std::string("("+x_+"x+"+y_+"y+"+z_+"z+"+d_+")"); 
            }

	    class NoIntersectException{};

            virtual ~Plane(){}
	protected:
	    Vertex normal;
	    Vertex normed;
	    float d;

    };

    class ViewPlane : public Plane {
	public:
	ViewPlane(const Vertex& ul_, const Vertex ur_, const Vertex ol_, float distance_, int w, int h)
	    : Plane(ol_,ul_,ur_), ul(ul_), ur(ur_), ol(ol_), distance(distance_), prp(0,0,0), width(w), height(h)
	{
	    Vertex normInv(normal * -1.0f);
	    Vertex normDir(normInv / abs(normInv));
	    Vertex start(ul + ((ur - ul) / 2.0f) + ((ol - ul) / 2.0f));

	    prp = start + (distance * normDir);
/*
            std::cout << "viewplane:" << toString() << std::endl;
            std::cout << "start:" << start.toString() << std::endl;
            std::cout << "dir:" << normDir.toString() << std::endl;
            std::cout << "prp: " << prp.toString() << std::endl;
            std::cout << "ur:" << ur.toString() << std::endl;
            std::cout << "ul:" << ul.toString() << std::endl;
            std::cout << "ol:" << ol.toString() << std::endl;
*/
            generateViewPlanePoints();
	}

        class ViewPlanePoint {
            public:
                ViewPlanePoint(int x_, int y_, const Line& line_)
                    :x(x_), y(y_), line(line_)
                {}

                const std::string toString() const {
                    std::string x_ = boost::lexical_cast<std::string, int>(x);
                    std::string y_ = boost::lexical_cast<std::string, int>(y);
                    return std::string("("+x_+","+y_+") .. Line: " + line.getStart().toString() + "+t*" + line.getDir().toString()  + "");
                }

                inline const Line& getLine() const { return line; }
		inline int getX() {return x;}
		inline int getY() {return y;}

            private:
                int x;
                int y;
                Line line;
        };

        typedef std::vector<ViewPlanePoint>::iterator PointIterator;

        inline PointIterator getPointBegin() { return points.begin(); };
        inline PointIterator getPointEnd() { return points.end(); };
	inline int numPoints() const { return points.size(); }

            virtual ~ViewPlane(){}
	private:

        inline void generateViewPlanePoints(){
            Vertex x(ur - ul);
            Vertex y(ol - ul);

            Vertex nX(x/width);
            Vertex nY(y/height);

            int i;
            int j;
            for(i = 0; i < width; i++) {
                Vertex pos1(ul + (i*nX));
                for(j = 0; j < height; j++) {
                    Vertex pos2(pos1 + (j * nY));
                    //std::cout << "p1" << pos2.toString() << std::endl;
                    points.push_back(
                            ViewPlanePoint(
                               // i, j, Line::fromPointsNormed( prp, pos2 )
                                i, j, Line::fromPoints( prp,pos2 )
                                )
                            );
                }
            }
        }



	Vertex ul;
	Vertex ur;
	Vertex ol;
	float distance;

	Vertex prp;
        std::vector<ViewPlanePoint> points;
        int width;
        int height;
    };

    
}

#endif
