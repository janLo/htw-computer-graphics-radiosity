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
		: normal(vertexCross(v3 - v2, v1 - v2)), d(-1*(v1 * normal))
	    {
               std::cout << "Plane from" << (v3 - v2).toString() << ", " << (v1 - v2).toString() << ": " << toString() << std::endl;
            }

	    Plane(const Vertex& normal_, const Vertex point) 
		:normal(normal_), d(point * normal)
            {}

	    Vertex calcIntersect(const Line& l) const {
		const float denom = normal * l.getDir();

		if(fabsf(denom) < 0.01f)
		    throw NoIntersectException();

		const float t = (normal * l.getStart() + d) / -1 *denom;

		return l.getStart() + (t * l.getDir());
	    }

            inline const Vertex& getNormal() const { return normal; }
            inline const float D() const {return d; } 

            inline std::string toString() { 
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
	    float d;

    };

    class ViewPlane : public Plane {
	public:
	ViewPlane(const Vertex& ul_, const Vertex ur_, const Vertex ol_, float distance_, int w, int h)
	    : Plane(ol_,ul_,ur_), ul(ul_), ur(ur_), ol(ol_), distance(distance_), prp(0,0,0), width(w), height(h)
	{
	    Vertex normInv(normal * -1);
	    Vertex normDir(normInv.norm());
	    Vertex start(ul + ((ur - ul) / 2) + ((ol - ul) / 2));

	    prp = start + (distance * normDir);

            std::cout << "viewplane:" << toString() << std::endl;
            std::cout << "start:" << start.toString() << std::endl;
            std::cout << "dir:" << normDir.toString() << std::endl;
            std::cout << "prp: " << prp.toString() << std::endl;
            std::cout << "ur:" << ur.toString() << std::endl;
            std::cout << "ul:" << ul.toString() << std::endl;
            std::cout << "ol:" << ol.toString() << std::endl;

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

                const Line& getLine() const { return line; }
            private:
                int x;
                int y;
                Line line;
        };

        typedef std::vector<ViewPlanePoint>::iterator PointIterator;

        inline PointIterator getPointBegin() { return points.begin(); };
        inline PointIterator getPointEnd() { return points.end(); };

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
                                i, j, Line::fromPointsNormed( prp, pos2 )
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
