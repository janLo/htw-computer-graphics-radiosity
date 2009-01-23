#include "Vertex.hpp"
#include "Plane.hpp"
#include "Polygon.hpp"
#include "Triangle.hpp"
#include <GL/glut.h>
#include <vector>
#include <iostream>

namespace radio {

    class Scene {

        public:
            Scene(int width_, int height_, float ptr_dist_,const Vertex& ul_, const Vertex ur_, const Vertex ol_)
                :width(width_), height(height_), ptr_dist(ptr_dist_), view(ul_, ur_, ol_, ptr_dist_, width_, height_)
            {
               defScene();
            }

            void render(){
                ViewPlane::PointIterator pit;
                    std::cout << "render" << std::endl;

                for (pit = view.getPointBegin(); pit != view.getPointEnd(); pit++){
                    ViewPlane::ViewPlanePoint& pt = *pit;
                    for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
                        Polygon& p = *polIt;
                        for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                            Triangle& t = *tit;
                            const Plane& p = t.getTrianglePlane();

                            try {
                                Vertex intersect(p.calcIntersect(pt.getLine()));
                                std::cout << "intersect on " << pt.toString() << ": (" << intersect.X() << "," << intersect.Y() << "," << intersect.Z() << ")" << std::endl;
                                if (t.pointInTriangle(intersect)) {
                                    std::cout << "In Triangle" << std::endl;
                                }
                            } catch (Plane::NoIntersectException e) {
                                std::cout << "No Intersect" << std::endl;
                            }
                        }
                    }

                }
            }

        protected:
            virtual void defScene() {
                Polygon p1;
                p1.addVertex(Vertex(1,1,1));
                p1.addVertex(Vertex(50,50,1));
                p1.addVertex(Vertex(50,1,1));
                polygons.push_back(p1);

            }
        private:
            int width;
            int height;
            float ptr_dist;
            ViewPlane view;
            std::vector<Polygon> polygons;

    };

}
