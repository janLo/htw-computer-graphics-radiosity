#ifndef ROOMSCENE_HPP
#define ROOMSCENE_HPP

#include "Scene.hpp"


namespace radio {
    class RoomScene : public Scene {

	public:
            RoomScene(View& view_, float ptr_dist_,const Vertex& ul_, const Vertex ur_, const Vertex ol_)
		:Scene(view_,ptr_dist_,ul_,ur_,ol_)
	    {}

	protected:
	    void defScene() ;
    };

}

#endif
