OBJS = Main.o Vertex.o Polygon.o Plane.o Line.o Triangle.o Line.o Scene.o BSphere.o View.o Colour.o RoomScene.o Patch.o PolygonTriangle.o
ifeq ($(DEBUG),1)
CXXFLAGS += -Wall -g
LDFLAGS += -lglut 
else
CXXFLAGS += -O3 -mtune=native -msse  -mfpmath=sse -masm=intel -mpc32 -finline-functions -finline-functions-called-once -finline-small-functions
LDFLAGS += -lglut -O3 -mtune=native -msse  -mfpmath=sse -masm=intel -mpc32 -finline-functions -finline-functions-called-once -finline-small-functions
endif

ifeq ($(USE_OMP),1)
    CXXFLAGS += -fopenmp -DUSE_OMP
    LDFLAGS += -fopenmp
endif


#LDFLAGS += -lglut -fopenmp

radiosity: ${OBJS}
	g++ -o radiosity ${LDFLAGS} ${OBJS}


clean:
	rm -f *.o radiosity


include deps
