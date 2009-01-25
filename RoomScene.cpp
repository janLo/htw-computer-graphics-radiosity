#include "RoomScene.hpp"
#include "Vertex.hpp"
#include "Colour.hpp"
#include "Polygon.hpp"


namespace radio {
    void RoomScene::defScene() {

        // Room
        {
            Polygon top(Colour(0.6,0,0), 2, 0.5);
            top.addVertex(Vertex(0,100,0));
            top.addVertex(Vertex(100,100,0));
            top.addVertex(Vertex(0,100,200));
            top.addVertex(Vertex(100,100,200));
            polygons.push_back(top);

            Polygon right(Colour(0,0.6,0), 0, 1);
            right.addVertex(Vertex(100,100,0));
            right.addVertex(Vertex(100,0,0));
            right.addVertex(Vertex(100,100,200));
            right.addVertex(Vertex(100,0,200));
            polygons.push_back(right);

            Polygon bottom(Colour(0.3,0.3,0.3), 0, 1);
            bottom.addVertex(Vertex(0,0,0));
            bottom.addVertex(Vertex(100,0,0));
            bottom.addVertex(Vertex(0,0,200));
            bottom.addVertex(Vertex(100,0,200));
            polygons.push_back(bottom);

            Polygon left(Colour(0,0,6), 0, 1);
            left.addVertex(Vertex(0,100,0));
            left.addVertex(Vertex(0,100,200));
            left.addVertex(Vertex(0,0,0));
            left.addVertex(Vertex(0,0,200));
            polygons.push_back(left);

            Polygon back(Colour(0.5,0.5,0.1), 0, 1);
            back.addVertex(Vertex(0,100,200));
            back.addVertex(Vertex(100,100,200));
            back.addVertex(Vertex(0,0,200));
            back.addVertex(Vertex(100,0,200));
            polygons.push_back(back);
        }

        // Block 1
        {/*
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
            */}
    }

}
