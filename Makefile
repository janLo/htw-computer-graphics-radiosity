OBJS = Main.o Vertex.o Polygon.o Plane.o Line.o Triangle.o Line.o Scene.o BSphere.o View.o Colour.o
CXXFLAGS += -Wall -g
LDFLAGS += -lglut -fopenmp

radiosity: ${OBJS}
	g++ -o radiosity ${LDFLAGS} ${OBJS}


clean:
	rm -f *.o radiosity


include deps
