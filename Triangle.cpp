#include "Triangle.hpp"
#include "Patch.hpp"

namespace radio {

    float Triangle::scale = 1.0f;

    Triangle::Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_)
	:a(a_), b(b_), c(c_), p(b,a,c)
    {
	//std::cout << p.toString() << std::endl;
    }

    Triangle::Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, float emit_, float reflex_)
	:a(a_), b(b_), c(c_), p(b,a,c), colour(col), emit(emit_), light(emit_), allSum(0), sum(0), reflex(reflex_)//, scale(1.0f)
    {
	//std::cout << p.toString() << std::endl;
    }

    Triangle::Triangle(const Vertex& a_, const Vertex& b_, const Vertex& c_, const Colour& col, const Plane& p_, float emit_, float reflex_)
	:a(a_), b(b_), c(c_), p(p_), colour(col), emit(emit_), light(emit_), allSum(0), sum(0), reflex(reflex_)//, scale(1.0f)
    {
	//std::cout << p.toString() << std::endl;
    }

    void Triangle::split(std::vector<Patch>& store, const Triangle& t){

       // Colour c1(t.colour + Colour(0.07f,0.07f,0.07f));
       // Colour c2(t.colour - Colour(0.05f,0.05f,0.05f));

	float min = 12;
	float abLen = abs(t.b - t.a);
	float bcLen = abs(t.c - t.b);
	float acLen = abs(t.c - t.a);

	// Split AB?
	if ( abLen > bcLen && abLen > acLen ) {
	    if ( abLen > min ) {
		Vertex newVt(splitEdge(t.a,t.b));
	//	split(store, Triangle(t.a, newVt, t.c, c1, t.p));
	//	split(store, Triangle(newVt, t.b, t.c, c2, t.p));
		split(store, Triangle(t.a, newVt, t.c, t.colour, t.p, t.emit, t.reflex));
		split(store, Triangle(newVt, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    } else {
		store.push_back(Patch(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    }
	    return;
	}

	// Split BC?
	if ( bcLen > acLen ) {
	    if ( bcLen > min ) {
		Vertex newVt(splitEdge(t.b, t.c));
	//	split(store, Triangle(t.a, newVt, t.c, c1, t.p));
	//	split(store, Triangle(t.a, t.b, newVt, c2, t.p));
		split(store, Triangle(t.a, newVt, t.c, t.colour, t.p, t.emit, t.reflex));
		split(store, Triangle(t.a, t.b, newVt, t.colour, t.p, t.emit, t.reflex));
	    } else {
		store.push_back(Patch(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    }
	    return;
	}

	// Split AC?
	if ( acLen > min ) {
	    Vertex newVt(splitEdge(t.a, t.c));
	  //  split(store, Triangle(t.a, t.b, newVt, c1, t.p));
	  //  split(store, Triangle(newVt, t.b, t.c, c2, t.p));
	    split(store, Triangle(t.a, t.b, newVt, t.colour, t.p, t.emit, t.reflex));
	    split(store, Triangle(newVt, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	} else {
	    store.push_back(Patch(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	}
    }

    void Triangle::split(std::vector<PatchTriangle>& store, const Triangle& t){

	float min = 40;
	float abLen = abs(t.b - t.a);
	float bcLen = abs(t.c - t.b);
	float acLen = abs(t.c - t.a);

	// Split AB?
	if ( abLen > bcLen && abLen > acLen ) {
	    if ( abLen > min ) {
		Vertex newVt(splitEdge(t.a,t.b));
		split(store, Triangle(t.a, newVt, t.c, t.colour, t.p, t.emit, t.reflex));
		split(store, Triangle(newVt, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    } else {
		store.push_back(PatchTriangle(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    }
	    return;
	}

	// Split BC?
	if ( bcLen > acLen ) {
	    if ( bcLen > min ) {
		Vertex newVt(splitEdge(t.b, t.c));
		split(store, Triangle(t.a, newVt, t.c, t.colour, t.p, t.emit, t.reflex));
		split(store, Triangle(t.a, t.b, newVt, t.colour, t.p, t.emit, t.reflex));
	    } else {
		store.push_back(PatchTriangle(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	    }
	    return;
	}

	// Split AC?
	if ( acLen > min ) {
	    Vertex newVt(splitEdge(t.a, t.c));
	    split(store, Triangle(t.a, t.b, newVt, t.colour, t.p, t.emit, t.reflex));
	    split(store, Triangle(newVt, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	} else {
	    store.push_back(PatchTriangle(t.a, t.b, t.c, t.colour, t.p, t.emit, t.reflex));
	}
    }

}
