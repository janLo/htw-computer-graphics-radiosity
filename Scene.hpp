#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

#include "Vertex.hpp"
#include "Plane.hpp"
#include "Polygon.hpp"
#include "Triangle.hpp"
#include "View.hpp"
#include "Colour.hpp"


namespace radio {

    class Scene {

        public:
            Scene(View& view_, float ptr_dist_,const Vertex& ul_, const Vertex ur_, const Vertex ol_)
                :width(view_.getWidth()), 
		 height(view_.getHeight()), 
		 ptr_dist(ptr_dist_), 
		 viewPlane(ul_, ur_, ol_, ptr_dist_, view_.getWidth(), view_.getHeight()), 
		 view(view_),
		 defined(false)
            {
	    }

	    class IntersectDistanceComparator {
		public:
		inline bool operator()(const std::pair<Triangle, Plane::Intersect>& a, 
			               const std::pair<Triangle, Plane::Intersect>& b) {
		    return (a.second.getDistance() < b.second.getDistance());
		}
	    };

            void render(){

		if (!defined){
                    defScene();
		    defined = true;
		}


                ViewPlane::PointIterator pit = viewPlane.getPointBegin();

		// Points
		/*int i;
                #pragma omp parallel for schedule(dynamic,2) private(i)
                for (int i = 0; i < viewPlane.numPoints(); i++){
                    ViewPlane::ViewPlanePoint& pt = pit[i];*/
                for (pit = viewPlane.getPointBegin(); pit != viewPlane.getPointEnd(); pit++){
                    ViewPlane::ViewPlanePoint& pt = *pit;
	            std::vector<std::pair<Triangle, Plane::Intersect> > intersects;

		    // Polygons
                    for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
                        Polygon& p = *polIt;

			if (!p.checkSphere(pt.getLine())){
			    continue;
			}

			// PolygonTriangles
                        for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
			    PolygonTriangle& t = *tit;
			    const Plane& p = t.getTrianglePlane();

			    try {

				Plane::Intersect inter(p.calcIntersect(pt.getLine()));

				// PatchTriangle
				for (PolygonTriangle::PatchTriangleIterator ptIt = t.getTriangleBegin(); ptIt != t.getTriangleEnd(); ptIt++) {

				    PatchTriangle& pTri = *ptIt;
				    if(pTri.inBSphere(inter.getPoint()) ) {

					// find Patch
					for (PatchTriangle::PatchIterator paIt = pTri.getPatchBegin(); paIt != pTri.getPatchEnd(); paIt++) {

					    Patch& patch = *paIt;
					    if ( patch.inBSphere(inter.getPoint()) ) { 
						intersects.push_back( 
							std::pair<Triangle,Plane::Intersect>(patch, inter) 
							);
					    }
					}
				    }
				}

				} catch (Plane::NoIntersectException e) {
                            }
                        }
		    }

		    std::sort(intersects.begin(), intersects.end(), IntersectDistanceComparator());

		    for (std::vector<std::pair<Triangle, Plane::Intersect> >::iterator iit = intersects.begin();
			    iit != intersects.end(); iit++) {

			Triangle&                              tri   = (*iit).first;
			Plane::Intersect&                      inter = (*iit).second;

			if (tri.pointInTriangle(inter.getPoint())) {
			    view.setPixel(pt.getX(), pt.getY(), tri.getColour());
			    break;
			}
		    }
                }
            }

        protected:
            virtual void defScene() {
/*                Polygon p1(Colour(1,0,0));
                p1.addVertex(Vertex(  0,  0,  8));
                p1.addVertex(Vertex(100,  0,  8));
                p1.addVertex(Vertex(  0,100,  8));
                p1.addVertex(Vertex( 60, 60,  8));
                polygons.push_back(p1);
*/
		Polygon p2(Colour(0,1,0));
		p2.addVertex(Vertex( 10, 10, 4));
		p2.addVertex(Vertex( 10, 20, 4));
		p2.addVertex(Vertex( 20, 10, 4));
		p2.addVertex(Vertex( 20, 20, 4));
		polygons.push_back(p2);
/*
		Polygon p3(Colour(0,0,1));
		p3.addVertex(Vertex( 20, 20, 20));
		p3.addVertex(Vertex( 20, 30, 2));
		p3.addVertex(Vertex( 30, 20, 2));
		p3.addVertex(Vertex( 30, 30, 20));
		polygons.push_back(p3);
*/            }
            std::vector<Polygon> polygons;
        private:

            int width;
            int height;
            float ptr_dist;
            ViewPlane viewPlane;
	    View& view;
	    bool defined;

    };

    class RoomScene : public Scene {

	public:
            RoomScene(View& view_, float ptr_dist_,const Vertex& ul_, const Vertex ur_, const Vertex ol_)
		:Scene(view_,ptr_dist_,ul_,ur_,ol_)
	    {}

	protected:
	    void defScene() {

		// Room
		{
		    Polygon top(Colour(1,0,0));
		    top.addVertex(Vertex(0,100,0));
		    top.addVertex(Vertex(100,100,0));
		    top.addVertex(Vertex(0,100,200));
		    top.addVertex(Vertex(100,100,200));
		    polygons.push_back(top);

		    Polygon right(Colour(0,1,0));
		    right.addVertex(Vertex(100,100,0));
		    right.addVertex(Vertex(100,100,200));
		    right.addVertex(Vertex(100,0,0));
		    right.addVertex(Vertex(100,0,200));
		    polygons.push_back(right);

		    Polygon bottom(Colour(0.5,0.5,0.5));
		    bottom.addVertex(Vertex(0,0,0));
		    bottom.addVertex(Vertex(100,0,0));
		    bottom.addVertex(Vertex(0,0,200));
		    bottom.addVertex(Vertex(100,0,200));
		    polygons.push_back(bottom);

		    Polygon left(Colour(0,0,1));
		    left.addVertex(Vertex(0,100,0));
		    left.addVertex(Vertex(0,100,200));
		    left.addVertex(Vertex(0,0,0));
		    left.addVertex(Vertex(0,0,200));
		    polygons.push_back(left);

		    Polygon back(Colour(0.7,0.7,0.3));
		    back.addVertex(Vertex(0,100,200));
		    back.addVertex(Vertex(100,100,200));
		    back.addVertex(Vertex(0,0,200));
		    back.addVertex(Vertex(100,0,200));
		    polygons.push_back(back);
		}

		// Block 1
		{
		    Polygon top(Colour(1,0,0));
		    top.addVertex(Vertex(35,20,35));
		    top.addVertex(Vertex(65,20,35));
		    top.addVertex(Vertex(35,20,65));
		    top.addVertex(Vertex(65,20,65));
		    polygons.push_back(top);

		    Polygon right(Colour(0,1,0));
		    right.addVertex(Vertex(65,20,35));
		    right.addVertex(Vertex(65,20,65));
		    right.addVertex(Vertex(65, 0,35));
		    right.addVertex(Vertex(65, 0,65));
		    polygons.push_back(right);

		    Polygon left(Colour(0,0,1));
		    left.addVertex(Vertex(35,20,35));
		    left.addVertex(Vertex(35,20,65));
		    left.addVertex(Vertex(35, 0,35));
		    left.addVertex(Vertex(35, 0,65));
		    polygons.push_back(left);

		    Polygon back(Colour(0.7,0.7,0.3));
		    back.addVertex(Vertex(35,20,65));
		    back.addVertex(Vertex(65,20,65));
		    back.addVertex(Vertex(35, 0,65));
		    back.addVertex(Vertex(65, 0,65));
		    polygons.push_back(back);
		}
	    }
    };

}

#endif
