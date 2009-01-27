#include <cmath>

#ifdef USE_OMP
    #include <omp.h>
#endif

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
        Polygon p2(Colour(0,1,0), 0);
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
			if( ( (p.getNormal() * pt.getLine().getStart()) + p.D() ) > 0.0f)
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
                                    view.setPixel(pt.getX(), pt.getY(), 
					//patch.getColour() * (patch.getLight()/Triangle::scale ));
					//patch.getColour() );
					patch.getLight() );
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
        runLightPass();
        runLightPass();
    }


    void Scene::runLightPass(){

#ifndef USE_OMP
        for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
            Polygon& p = *polIt;
#else
       int max = polygons.size();
    
#pragma omp parallel for schedule(dynamic,4)
       for(int polIt = 0; polIt < max; polIt++){
            Polygon& p = polygons[polIt];
#endif
            for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                PolygonTriangle& t = *tit;
                const Plane& p = t.getTrianglePlane();

                std::vector<PolygonTriangle*> viewable;
                findViewables(viewable, t);

                for (PolygonTriangle::PatchTriangleIterator ptIt = t.getTriangleBegin(); ptIt != t.getTriangleEnd(); ptIt++) {
                    PatchTriangle& pTri = *ptIt;

                    for (PatchTriangle::PatchIterator paIt = pTri.getPatchBegin(); paIt != pTri.getPatchEnd(); paIt++) {
                        Patch& patch = *paIt;
                        Vertex ni(patch.getTrianglePlane().getNormedNormal());
			std::vector<std::pair<Patch*, float> > facts;

			if (0.0f ==  abs(patch.getLastLight()))
			    continue;

			float sum = 0.0f;
			bool corner = false;

                        for (std::vector<PolygonTriangle*>::iterator it = viewable.begin(); it != viewable.end(); it++){
                            for (PolygonTriangle::PatchTriangleIterator ptIt2 = (*it)->getTriangleBegin(); ptIt2 != (*it)->getTriangleEnd(); ptIt2++) {
                                for (PatchTriangle::PatchIterator paIt2 = (*ptIt2).getPatchBegin(); paIt2 != (*ptIt2).getPatchEnd(); paIt2++) {
                                    Patch& other = *paIt2;

                                   Vertex ray(other.getMid() - patch.getMid());
                                  //  Vertex ray(patch.getMid() - other.getMid());

				   if(
				       ((other.getTrianglePlane().getNormal() * patch.getMid()) + other.getTrianglePlane().D() < 0.0f) ||
				       ((patch.getTrianglePlane().getNormal() * other.getMid()) + patch.getTrianglePlane().D() < 0.0f)
				     )
				     continue;

				    float raylen = abs(ray);
				    
				    Vertex c(ray.getNormed());
				    if(!isReachable(patch.getMid(), other.getMid(), ray, c, raylen, t, *(*it)))
				      continue;

                                    Vertex nj(other.getTrianglePlane().getNormedNormal());

				    float phiI = (c)  * ni;
				    float phiJ = (c * -1.0f) * nj;

				    if (phiI < 0.0f)
				      phiI = 0.0f;
				    if (phiJ < 0.0f)
				      phiJ = 0.0f;

				    //if (raylen <=1.1f)
				    //    raylen = 2.0f;

				    float ff =  phiI * phiJ / ((raylen * raylen) * M_PI);

				    //std::cout << raylen << std::endl;

				    if (ff > 0.0f){
				      //  corner |= patch.buildCorner(other);
				        sum += ff;
				        if(patch.buildCorner(other))
					    ff /= 1.5;
				        facts.push_back(std::pair<Patch*, float>(&other, ff));
				    }
				}
				}
                        }
			if (corner) {
			  sum *= 1.5f;
			  std::cout << "Corner" << std::endl;

			}
			for (std::vector<std::pair<Patch*, float> >::iterator it = facts.begin(); it != facts.end(); it++){
			    (*it).first->addToLightSum(patch.getLastLight() *  ((*it).second/sum ));
			}
                    }
                }
            }
            std::cout << "Polygon Ready " << std::endl;
        }
        updateLight();
	std::cout << "pass completed" << std::endl;

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

    inline bool Scene::isReachable(const Vertex& a, const Vertex& b, const Vertex& ray, const Vertex& normedRay, float len, const Triangle& t1, const Triangle& t2) {
            Line l(a,normedRay);

            for (std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
                Polygon& p = *polIt;

                if (!p.checkSphere(l)){
                    continue;
                }

                for (Polygon::TriangleIterator tit = p.getTriangleBegin(); tit != p.getTriangleEnd(); tit++){
                    PolygonTriangle& t = *tit;
                    const Plane& p = t.getTrianglePlane();

		    if (&t1 == &t || &t2 == &t)
		        continue;

                    try {
                        Plane::Intersect inter(p.calcIntersect(l));

			if(
			    (inter.getDistance() > 0.0f) &&  (inter.getDistance() < len) &&
			    t.pointInTriangle(inter.getPoint())
			  )
                            return false;

                    } catch (Plane::NoIntersectException e) {
                    }
                }
            }
            return true;
    }


    bool Scene::findViewables(std::vector<PolygonTriangle*>& store, const PolygonTriangle& ref){
        const Plane& p = ref.getTrianglePlane();
        Vertex refN = p.getNormedNormal();

        for(std::vector<Polygon>::iterator polIt = polygons.begin(); polIt != polygons.end(); polIt++){
            Polygon& po = *polIt;
            for (Polygon::TriangleIterator tit = po.getTriangleBegin(); tit != po.getTriangleEnd(); tit++){

	        if (&(*tit) == &ref)
		  continue;

                const Plane& pl = (*tit).getTrianglePlane();
                Vertex testN = pl.getNormedNormal();

/*                if ( refN.equal(testN) )
                    continue;
*/
                if( 
		    ( ((p.getNormal() * tit->A()) + p.D() ) < 0.0f) &&
		    ( ((p.getNormal() * tit->B()) + p.D() ) < 0.0f) &&
		    ( ((p.getNormal() * tit->C()) + p.D() ) < 0.0f)
		  )
                    continue;

                if( 
		      ( ((pl.getNormal() * ref.A()) + pl.D() ) < 0.0f) &&
		      ( ((pl.getNormal() * ref.B()) + pl.D() ) < 0.0f) &&
		      ( ((pl.getNormal() * ref.C()) + pl.D() ) < 0.0f) 
		  )
                    continue;

                store.push_back(&(*tit));
            }
        }
    }
}
