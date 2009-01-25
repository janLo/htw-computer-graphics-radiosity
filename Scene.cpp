#include <cmath>

#include "Scene.hpp"
#include "Colour.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "Plane.hpp"


namespace radio {
    void Scene::defScene() {
/*        Polygon p1(Colour(1,0,0));
        p1.addVertex(Vertex(  0,  0,  8));
        p1.addVertex(Vertex(  0,100,  8));
        p1.addVertex(Vertex(100,  0,  8));
        p1.addVertex(Vertex( 60, 60,  8));
        polygons.push_back(p1);
*/
        Polygon p2(Colour(0,1,0), 0, 0.5);
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
        polygons.push_back(p3);*/
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
                                    view.setPixel(pt.getX(), pt.getY(), patch.getColour() *(patch.getLight()/ patch.getArea()));
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

    void Scene::lighten() {
        runLightPass();

        runLightPass();
    }


    void Scene::runLightPass(){
        for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
            Polygon& p = *polIt;
            for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                PolygonTriangle& t = *tit;
                const Plane& p = t.getTrianglePlane();

                std::vector<PolygonTriangle*> viewable;
                findViewables(viewable, t);

                for (PolygonTriangle::PatchTriangleIterator ptIt = t.getTriangleBegin(); ptIt != t.getTriangleEnd(); ptIt++) {
                    PatchTriangle& pTri = *ptIt;

                    for (PatchTriangle::PatchIterator paIt = pTri.getPatchBegin(); paIt != pTri.getPatchEnd(); paIt++) {
                        Patch& patch = *paIt;

                        for (std::vector<PolygonTriangle*>::iterator it = viewable.begin(); it != viewable.end(); it++){
                            for (PolygonTriangle::PatchTriangleIterator ptIt2 = (*it)->getTriangleBegin(); ptIt2 != (*it)->getTriangleEnd(); ptIt2++) {
                                for (PatchTriangle::PatchIterator paIt2 = (*ptIt2).getPatchBegin(); paIt2 != (*ptIt2).getPatchEnd(); paIt2++) {
                                    const Patch& other = *paIt2;

//                                   Vertex ray(other.getMid() - patch.getMid());
                                    Vertex ray(patch.getMid() - other.getMid());
/*
                                    if(!isReachable(patch.getMid(), other.getMid(), ray))
                                            continue;
*/
                                    Vertex i(patch.getTrianglePlane().getNormal().getNormed());
                                    Vertex j(other.getTrianglePlane().getNormal().getNormed());
                                    Vertex c(ray.getNormed());
                                    float f = patch.getArea() * ((i*c)*(j*c)) / ((ray * ray) * M_PI);
                                    //if (f > 0.0f){
                                    patch.addToLightSum(other.getLight() * f);
//                std::cout << i.toString() << " " << c.toString() << " " << (i*c) << std::endl;
                //                    std::cout << ((i*c)) << std::endl;
                                    //}
                                }
                            }
                        }
                    }
                }
            }
            std::cout << "Polygon Ready " << std::endl;
        }
        updateLight();

    }

    void Scene::updateLight() {
        for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
            Polygon& p = *polIt;
            for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                PolygonTriangle& t = *tit;
                const Plane& p = t.getTrianglePlane();
                for (PolygonTriangle::PatchTriangleIterator ptIt = t.getTriangleBegin(); ptIt != t.getTriangleEnd(); ptIt++) {
                    PatchTriangle& pTri = *ptIt;
                    for (PatchTriangle::PatchIterator paIt = pTri.getPatchBegin(); paIt != pTri.getPatchEnd(); paIt++) {
                        Patch& patch = *paIt;
                        patch.updateLight();
                    }
                }
            }
        }

    }

    bool Scene::isReachable(const Vertex& a, const Vertex& b, const Vertex& ray) {
            for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
                Polygon& p = *polIt;

                Line l(a,ray);

                std::cout << l.getDir().toString() << "  " << ray.toString() << std::endl;

                if (!p.checkSphere(l)){
                    std::cout << "BAR" << std::endl;
                    continue;
                }

                float rayLenSq = ray*ray;

                // PolygonTriangles
                for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                    PolygonTriangle& t = *tit;
                    const Plane& p = t.getTrianglePlane();

                    try {
                        Plane::Intersect inter(p.calcIntersect(l));

                        Vertex v(inter.getPoint() - a);

                        if(
                                (rayLenSq > (v*v)) &&
                                t.pointInTriangle(inter.getPoint())
                                )
                            return false;

                    } catch (Plane::NoIntersectException e) {
                        std::cout << "FOO" << std::endl;
                    }
                }
            }
            return true;
        
    }


    bool Scene::findViewables(std::vector<PolygonTriangle*>& store, const PolygonTriangle& ref){
        const Plane& p = ref.getTrianglePlane();
        Vertex refN = p.getNormal().getNormed();

        for(std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
            Polygon& po = *polIt;
            for (Polygon::TriangleIterator tit = po.getTriangleBegin(); tit != po.getTriangleEnd(); tit++){
                const Plane& pl = (*tit).getTrianglePlane();
                Vertex testN = pl.getNormal().getNormed();

                if ( refN.equal(testN) )
                    continue;

                if( ( (p.getNormal() * tit->A()) + p.D() ) < 0.0f)
                    continue;

                store.push_back(&(*tit));
            }
        }
    }
}
