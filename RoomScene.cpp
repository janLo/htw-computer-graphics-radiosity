#include "RoomScene.hpp"
#include "Vertex.hpp"
#include "Colour.hpp"
#include "Polygon.hpp"


namespace radio {
    void RoomScene::defScene() {

        // Room
        {
            Polygon top(Colour(0.3,0.6,0), 0, 0.8);
            top.addVertex(Vertex(0,100,0));
            top.addVertex(Vertex(0,100,100));
            top.addVertex(Vertex(100,100,0));
            top.addVertex(Vertex(100,100,100));
            polygons.push_back(top);

            Polygon right(Colour(0.6,0.0,0.1), 0, 0.8);
            right.addVertex(Vertex(100,100,0));
            right.addVertex(Vertex(100,100,100));
            right.addVertex(Vertex(100,0,0));
            right.addVertex(Vertex(100,0,100));
            polygons.push_back(right);

            Polygon bottom(Colour(0.5,0.5,0.5), 0, 0.8);
            bottom.addVertex(Vertex(0,0,0));
            bottom.addVertex(Vertex(100,0,0));
            bottom.addVertex(Vertex(0,0,200));
            bottom.addVertex(Vertex(100,0,100));
            polygons.push_back(bottom);

            Polygon left(Colour(0.3,0.3,0.6), 0, 0.8);
            left.addVertex(Vertex(0,100,0));
            left.addVertex(Vertex(0,0,0));
            left.addVertex(Vertex(0,100,100));
            left.addVertex(Vertex(0,0,100));
            polygons.push_back(left);

            Polygon back(Colour(0.3,0.6,0.6), 0, 0.8);
            back.addVertex(Vertex(0,100,100));
            back.addVertex(Vertex(0,0,100));
            back.addVertex(Vertex(100,100,100));
            back.addVertex(Vertex(100,0,100));
            polygons.push_back(back);
        }

        // Block 1
        {
        /*    Polygon top(Colour(1,0,0), 0, 0.8);
            top.addVertex(Vertex(35,20,35));
            top.addVertex(Vertex(65,20,35));
            top.addVertex(Vertex(35,20,65));
            top.addVertex(Vertex(65,20,65));
            polygons.push_back(top);

            Polygon right(Colour(0,1,0), 0, 0.8);
            right.addVertex(Vertex(65,20,35));
            right.addVertex(Vertex(65,20,65));
            right.addVertex(Vertex(65, 0,35));
            right.addVertex(Vertex(65, 0,65));
            polygons.push_back(right);

            Polygon left(Colour(0,0,1), 0, 0.8);
            left.addVertex(Vertex(35,20,35));
            left.addVertex(Vertex(35, 0,35));
            left.addVertex(Vertex(35,20,65));
            left.addVertex(Vertex(35, 0,65));
            polygons.push_back(left);

            Polygon back(Colour(0.7,0.7,0.3), 0, 0.8);
            back.addVertex(Vertex(35,20,65));
            back.addVertex(Vertex(35, 0,65));
            back.addVertex(Vertex(65,20,65));
            back.addVertex(Vertex(65, 0,65));
            polygons.push_back(back);*/
        }

	// Light
	{
	    Polygon top(Colour(1,1,1), 1, 0.0);
            top.addVertex(Vertex(45,65,55));
            top.addVertex(Vertex(55,65,55));
            top.addVertex(Vertex(45,65,65));
            top.addVertex(Vertex(55,65,65));
            polygons.push_back(top);

	    Polygon bottom(Colour(1,1,1), 1, 0.0);
            top.addVertex(Vertex(45,60,55));
            top.addVertex(Vertex(45,60,65));
            top.addVertex(Vertex(55,60,55));
            top.addVertex(Vertex(55,60,65));
            polygons.push_back(bottom);

	    Polygon left(Colour(1,1,1), 1, 0.0);
            left.addVertex(Vertex(45,65,55));
            left.addVertex(Vertex(45,65,65));
            left.addVertex(Vertex(45,60,55));
            left.addVertex(Vertex(45,60,65));
            polygons.push_back(left);

	    Polygon right(Colour(1,1,1), 1, 0.0);
            right.addVertex(Vertex(55,65,55));
            right.addVertex(Vertex(55,60,55));
            right.addVertex(Vertex(55,65,65));
            right.addVertex(Vertex(55,60,65));
            polygons.push_back(right);

	    Polygon front(Colour(1,1,1), 1, 0.0);
            front.addVertex(Vertex(45,65,55));
            front.addVertex(Vertex(45,60,55));
            front.addVertex(Vertex(55,65,55));
            front.addVertex(Vertex(55,60,55));
            polygons.push_back(front);

	    Polygon back(Colour(1,1,1), 1, 0.0);
            back.addVertex(Vertex(55,60,65));
            back.addVertex(Vertex(45,60,65));
            back.addVertex(Vertex(55,65,65));
            back.addVertex(Vertex(45,65,65));
            polygons.push_back(back);

	}

    }

}
