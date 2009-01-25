#include "Scene.hpp"
#include "Colour.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "Plane.hpp"


namespace radio {
    void Scene::defScene() {
        Polygon p1(Colour(1,0,0));
        p1.addVertex(Vertex(  0,  0,  8));
        p1.addVertex(Vertex(  0,100,  8));
        p1.addVertex(Vertex(100,  0,  8));
        p1.addVertex(Vertex( 60, 60,  8));
        polygons.push_back(p1);

        Polygon p2(Colour(0,1,0));
        p2.addVertex(Vertex( 10, 10, 4));
        p2.addVertex(Vertex( 10, 20, 4));
        p2.addVertex(Vertex( 20, 10, 4));
        p2.addVertex(Vertex( 20, 20, 4));
        polygons.push_back(p2);

        Polygon p3(Colour(0,0,1));
        p3.addVertex(Vertex( 20, 20, 20));
        p3.addVertex(Vertex( 20, 30, 2));
        p3.addVertex(Vertex( 30, 20, 2));
        p3.addVertex(Vertex( 30, 30, 20));
        polygons.push_back(p3);
    }

    void Scene::define() {
        if (!defined){
            defScene();
            defined = true;
        }
    }

    void Scene::render(){
        ViewPlane::PointIterator pit = viewPlane.getPointBegin();

        // Points
        for (pit = viewPlane.getPointBegin(); pit != viewPlane.getPointEnd(); pit++){
            ViewPlane::ViewPlanePoint& pt = *pit;
            std::vector<std::pair<PolygonTriangle*, Plane::Intersect> > intersects;

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
                        intersects.push_back(std::pair<PolygonTriangle*,Plane::Intersect>(&t, inter));

                    } catch (Plane::NoIntersectException e) {
                    }
                }
            }

            std::sort(intersects.begin(), intersects.end(), IntersectDistanceComparator<PolygonTriangle*>());

            for (std::vector<std::pair<PolygonTriangle*, Plane::Intersect> >::iterator iit = intersects.begin();
                    iit != intersects.end(); iit++) {
                PolygonTriangle&                              t   = *((*iit).first);
                Plane::Intersect&                      inter = (*iit).second;
                if (t.pointInTriangle(inter.getPoint())){
                    // PatchTriangle
                    for (PolygonTriangle::PatchTriangleIterator ptIt = t.getTriangleBegin(); ptIt != t.getTriangleEnd(); ptIt++) {

                        PatchTriangle& pTri = *ptIt;
                        if(
                                pTri.inBSphere(inter.getPoint()) &&
                                pTri.pointInTriangle(inter.getPoint())
                          ) {


                            // find Patch
                            for (PatchTriangle::PatchIterator paIt = pTri.getPatchBegin(); paIt != pTri.getPatchEnd(); paIt++) {

                                Patch& patch = *paIt;
                                if ( 
                                        patch.inBSphere(inter.getPoint()) &&
                                        patch.pointInTriangle(inter.getPoint()) 
                                   ) { 
                                    view.setPixel(pt.getX(), pt.getY(), patch.getColour());
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }

            }
        }
    }
}
