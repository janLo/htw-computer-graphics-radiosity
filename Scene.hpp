#include "Vertex.hpp"
#include "Plane.hpp"
#include "Polygon.hpp"
#include "Triangle.hpp"
#include "View.hpp"
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

namespace radio {

    class Scene {

        public:
            Scene(View& view_, float ptr_dist_,const Vertex& ul_, const Vertex ur_, const Vertex ol_)
                :width(view_.getWidth()), 
		 height(view_.getHeight()), 
		 ptr_dist(ptr_dist_), 
		 viewPlane(ul_, ur_, ol_, ptr_dist_, width, height), 
		 view(view_)
            {
               defScene();
	    }

	    class IntersectDistanceComparator {
		public:
		inline bool operator()(const std::pair<Triangle, Plane::Intersect>& a, 
			               const std::pair<Triangle, Plane::Intersect>& b) {
		    return (a.second.getDistance() > b.second.getDistance());
		}
	    };

            void render(){

	        std::vector<std::pair<Triangle, Plane::Intersect> > intersects;

                ViewPlane::PointIterator pit;

                for (pit = viewPlane.getPointBegin(); pit != viewPlane.getPointEnd(); pit++){
                    ViewPlane::ViewPlanePoint& pt = *pit;
                    for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
                        Polygon& p = *polIt;

			if (!p.checkSphere(pt.getLine())){
			    continue;
			}

                        for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                            Triangle& t = *tit;
                            const Plane& p = t.getTrianglePlane();

                            try {
                                intersects.push_back( 
					std::pair<Triangle,Plane::Intersect>(
					    t, p.calcIntersect(pt.getLine())
					    ) 
					);
                            } catch (Plane::NoIntersectException e) {
                                std::cout << "No Intersect" << std::endl;
                            }
                        }
		    }

		    std::sort(intersects.begin(), intersects.end(), IntersectDistanceComparator());

		    for (std::vector<std::pair<Triangle, Plane::Intersect> >::iterator iit = intersects.begin();
			    iit != intersects.end(); iit++) {

			Triangle&                              tri   = (*iit).first;
			Plane::Intersect&                      inter = (*iit).second;
			if (tri.pointInTriangle(inter.getPoint())) {
			    view.setPixel(pt.getX(), pt.getY());
			    //draw()
			    //std::cout << "In Triangle" << std::endl;
			    break;
			}
		    }
		    intersects.clear();
                }
            }

        protected:
            virtual void defScene() {
                Polygon p1;
                p1.addVertex(Vertex(  0,  0,  1));
                p1.addVertex(Vertex(100,  0,  1));
                p1.addVertex(Vertex(  0,100,  1));
                p1.addVertex(Vertex( 60, 60,  1));
                polygons.push_back(p1);

		Polygon p2;
		p2.addVertex(Vertex( 20, 10, 2));
		p2.addVertex(Vertex( 10, 10, 2));
		p2.addVertex(Vertex( 10, 20, 2));
		p2.addVertex(Vertex( 20, 20, 2));
		polygons.push_back(p2);

		Polygon p3;
		p3.addVertex(Vertex( 30, 20, 3));
		p3.addVertex(Vertex( 20, 20, 5));
		p3.addVertex(Vertex( 20, 30, 2));
		p3.addVertex(Vertex( 30, 30, 3));
		polygons.push_back(p3);
            }
        private:

            

            int width;
            int height;
            float ptr_dist;
            ViewPlane viewPlane;
            std::vector<Polygon> polygons;
	    View& view;

    };

}
