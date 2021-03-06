#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

#include "Polygon.hpp"
#include "View.hpp"


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
            {}

            template <class T>
	    class IntersectDistanceComparator {
		public:
		inline bool operator()(const std::pair<T, Plane::Intersect>& a, 
			               const std::pair<T, Plane::Intersect>& b) {
		    return (a.second.getDistance() < b.second.getDistance());
		}
	    };

            void define();
            void render();

            void lighten();



        protected:
            virtual void defScene() ;
            std::vector<Polygon> polygons;

        private:
            bool findViewables(std::vector<PolygonTriangle*>& store, const PolygonTriangle& ref);
            inline bool isReachable(const Vertex& a, const Vertex& b, const Vertex& ray, const Vertex& normedRay, float len, const Triangle& t1, const Triangle& t2);
            void updateLight();
            void runLightPass();

            int width;
            int height;
            float ptr_dist;
            ViewPlane viewPlane;
	    View& view;
	    bool defined;

    };
}
#endif
