#include "RoomScene.hpp"
#include "Vertex.hpp"
#include "Colour.hpp"
#include "Polygon.hpp"


namespace radio {
    void RoomScene::defScene() {

        // Room
        {
            Polygon top(Colour(1.0f,1.0f,1.0f), 0);
            top.addVertex(Vertex(0,100,0));
            top.addVertex(Vertex(0,100,100));
            top.addVertex(Vertex(100,100,0));
            top.addVertex(Vertex(100,100,100));
            polygons.push_back(top);

            Polygon right(Colour(0.7,0.0,0.2), 0);
            right.addVertex(Vertex(100,100,0));
            right.addVertex(Vertex(100,100,100));
            right.addVertex(Vertex(100,0,0));
            right.addVertex(Vertex(100,0,100));
            polygons.push_back(right);

            Polygon bottom(Colour(0.7,0.7,0.7), 0);
            bottom.addVertex(Vertex(0,0,0));
            bottom.addVertex(Vertex(100,0,0));
            bottom.addVertex(Vertex(0,0,200));
            bottom.addVertex(Vertex(100,0,100));
            polygons.push_back(bottom);

            Polygon left(Colour(0.4,0.4,0.7), 0);
            left.addVertex(Vertex(0,100,0));
            left.addVertex(Vertex(0,0,0));
            left.addVertex(Vertex(0,100,100));
            left.addVertex(Vertex(0,0,100));
            polygons.push_back(left);

            Polygon back(Colour(0.4,0.8,0.8), 0);
            back.addVertex(Vertex(0,100,100));
            back.addVertex(Vertex(0,0,100));
            back.addVertex(Vertex(100,100,100));
            back.addVertex(Vertex(100,0,100));
            polygons.push_back(back);
        }

        // Block 1
        {
            Polygon top(Colour(1,0,0), 0);
            top.addVertex(Vertex(35,20,35));
            top.addVertex(Vertex(65,20,35));
            top.addVertex(Vertex(35,20,65));
            top.addVertex(Vertex(65,20,65));
            polygons.push_back(top);

	    {
		Polygon right_l(Colour(0,1,0), 0);
		right_l.addVertex(Vertex(62,20,35));
		right_l.addVertex(Vertex(62,20,65));
		right_l.addVertex(Vertex(62, 0,35));
		right_l.addVertex(Vertex(62, 0,65));
		polygons.push_back(right_l);

		Polygon right_r(Colour(0,1,0), 0);
		right_r.addVertex(Vertex(63,20,35));
		right_r.addVertex(Vertex(63, 0,35));
		right_r.addVertex(Vertex(63,20,65));
		right_r.addVertex(Vertex(63, 0,65));
		polygons.push_back(right_r);
	    }
	    {
		Polygon left_r(Colour(0,0,1), 0);
		left_r.addVertex(Vertex(38,20,35));
		left_r.addVertex(Vertex(38, 0,35));
		left_r.addVertex(Vertex(38,20,65));
		left_r.addVertex(Vertex(38, 0,65));
		polygons.push_back(left_r);

		Polygon left_l(Colour(0,0,1), 0);
		left_l.addVertex(Vertex(37,20,35));
		left_l.addVertex(Vertex(37,20,65));
		left_l.addVertex(Vertex(37, 0,35));
		left_l.addVertex(Vertex(37, 0,65));
		polygons.push_back(left_l);
	    }

        /*    Polygon back(Colour(0.7,0.7,0.3), 0, reflex);
            back.addVertex(Vertex(35,20,65));
            back.addVertex(Vertex(35, 0,65));
            back.addVertex(Vertex(65,20,65));
            back.addVertex(Vertex(65, 0,65));
            polygons.push_back(back);*/
        }

	{
	    float light  = 10.0f;
	          light  = 5.0f;
	    
	    Vertex a(55,30,55);
	    Vertex b(55,25,55);
	    Vertex c(60,25,55);
	    Vertex d(60,30,55);
	    Vertex e(55,30,60);
	    Vertex f(55,25,60);
	    Vertex g(60,25,60);
	    Vertex h(60,30,60);

            Polygon top(Colour(1.0f,1.0f,1.0f), light);
            top.addVertex(a);
            top.addVertex(d);
            top.addVertex(e);
            top.addVertex(h);
            polygons.push_back(top);

            Polygon bottom(Colour(1.0f,1.0f,1.0f), light*0.0f);
            bottom.addVertex(b);
            bottom.addVertex(f);
            bottom.addVertex(c);
            bottom.addVertex(g);
            polygons.push_back(bottom);

            Polygon left(Colour(1.0f,1.0f,1.0f), light);
            left.addVertex(a);
            left.addVertex(e);
            left.addVertex(b);
            left.addVertex(f);
            polygons.push_back(left);

            Polygon right(Colour(1.0f,1.0f,1.0f), light);
            right.addVertex(d);
            right.addVertex(c);
            right.addVertex(h);
            right.addVertex(g);
            polygons.push_back(right);

            Polygon front(Colour(1.0f,1.0f,1.0f), light);
            front.addVertex(a);
            front.addVertex(b);
            front.addVertex(d);
            front.addVertex(c);
            polygons.push_back(front);

            Polygon back(Colour(1.0f,1.0f,1.0f), light);
            back.addVertex(e);
            back.addVertex(h);
            back.addVertex(f);
            back.addVertex(g);
            polygons.push_back(back);
	}

	{
	    float light  = 0.0f;
	    
	    Vertex a(56,25,56);
	    Vertex b(56,20,56);
	    Vertex c(59,20,56);
	    Vertex d(59,25,56);
	    Vertex e(56,25,59);
	    Vertex f(56,20,59);
	    Vertex g(59,20,59);
	    Vertex h(59,25,59);

            Polygon top(Colour(1.0f,1.0f,1.0f), light);
            top.addVertex(a);
            top.addVertex(d);
            top.addVertex(e);
            top.addVertex(h);
            polygons.push_back(top);

            Polygon bottom(Colour(1.0f,1.0f,1.0f), light);
            bottom.addVertex(b);
            bottom.addVertex(f);
            bottom.addVertex(c);
            bottom.addVertex(g);
            polygons.push_back(bottom);

            Polygon left(Colour(1.0f,1.0f,1.0f), light);
            left.addVertex(a);
            left.addVertex(e);
            left.addVertex(b);
            left.addVertex(f);
            polygons.push_back(left);

            Polygon right(Colour(1.0f,1.0f,1.0f), light);
            right.addVertex(d);
            right.addVertex(c);
            right.addVertex(h);
            right.addVertex(g);
            polygons.push_back(right);

            Polygon front(Colour(1.0f,1.0f,1.0f), light);
            front.addVertex(a);
            front.addVertex(b);
            front.addVertex(d);
            front.addVertex(c);
            polygons.push_back(front);

            Polygon back(Colour(1.0f,1.0f,1.0f), light);
            back.addVertex(e);
            back.addVertex(h);
            back.addVertex(f);
            back.addVertex(g);
            polygons.push_back(back);
	}



	// Light
	{
	    float light  = 15.0f;
	          light  = 7.5f;
	    
	    Vertex a(45,80,45);
	    Vertex b(45,70,45);
	    Vertex c(55,70,45);
	    Vertex d(55,80,45);
	    Vertex e(45,80,55);
	    Vertex f(45,70,55);
	    Vertex g(55,70,55);
	    Vertex h(55,80,55);

            Polygon top(Colour(1.0f,1.0f,1.0f), light*0.0f);
            top.addVertex(a);
            top.addVertex(d);
            top.addVertex(e);
            top.addVertex(h);
            polygons.push_back(top);

            Polygon bottom(Colour(1.0f,1.0f,1.0f), light);
            bottom.addVertex(b);
            bottom.addVertex(f);
            bottom.addVertex(c);
            bottom.addVertex(g);
            polygons.push_back(bottom);

            Polygon left(Colour(1.0f,1.0f,1.0f), light);
            left.addVertex(a);
            left.addVertex(e);
            left.addVertex(b);
            left.addVertex(f);
            polygons.push_back(left);

            Polygon right(Colour(1.0f,1.0f,1.0f), light);
            right.addVertex(d);
            right.addVertex(c);
            right.addVertex(h);
            right.addVertex(g);
            polygons.push_back(right);

            Polygon front(Colour(1.0f,1.0f,1.0f), light);
            front.addVertex(a);
            front.addVertex(b);
            front.addVertex(d);
            front.addVertex(c);
            polygons.push_back(front);

            Polygon back(Colour(1.0f,1.0f,1.0f), light);
            back.addVertex(e);
            back.addVertex(h);
            back.addVertex(f);
            back.addVertex(g);
            polygons.push_back(back);
	}
	{
	    float light  = 0.0f;
	    
	    Vertex a(48,100,48);
	    Vertex b(48, 80,48);
	    Vertex c(52, 80,48);
	    Vertex d(52,100,48);
	    Vertex e(48,100,52);
	    Vertex f(48, 80,52);
	    Vertex g(52, 80,52);
	    Vertex h(52,100,52);

            Polygon top(Colour(1.0f,1.0f,1.0f), light);
            top.addVertex(a);
            top.addVertex(d);
            top.addVertex(e);
            top.addVertex(h);
            polygons.push_back(top);

            Polygon bottom(Colour(1.0f,1.0f,1.0f), light);
            bottom.addVertex(b);
            bottom.addVertex(f);
            bottom.addVertex(c);
            bottom.addVertex(g);
            polygons.push_back(bottom);

            Polygon left(Colour(1.0f,1.0f,1.0f), light);
            left.addVertex(a);
            left.addVertex(e);
            left.addVertex(b);
            left.addVertex(f);
            polygons.push_back(left);

            Polygon right(Colour(1.0f,1.0f,1.0f), light);
            right.addVertex(d);
            right.addVertex(c);
            right.addVertex(h);
            right.addVertex(g);
            polygons.push_back(right);

            Polygon front(Colour(1.0f,1.0f,1.0f), light);
            front.addVertex(a);
            front.addVertex(b);
            front.addVertex(d);
            front.addVertex(c);
            polygons.push_back(front);

            Polygon back(Colour(1.0f,1.0f,1.0f), light);
            back.addVertex(e);
            back.addVertex(h);
            back.addVertex(f);
            back.addVertex(g);
            polygons.push_back(back);
	}

    }

}
