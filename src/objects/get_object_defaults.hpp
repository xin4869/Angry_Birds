#ifndef GET_OBJECT_DEFAULTS
#define GET_OBJECT_DEFAULTS

#include "object_defs.hpp"
#include "special_birds.hpp"
#include "block.hpp"
#include "pig.hpp"

/**
 * @brief Functions to get default values with a string. Used in level loading.
 * @brief The implementation here is poor. May or may not fix that later.
 */
/*
namespace ObjectDefs
{
    //replace with a class and a map?

    ObjectDefaults* getBirdDefaults(const std::string& name) {
        if (name == "normalbird") return &normalBirdDefaults;
        if (name == "speedbird") return &speedBirdDefaults;
        if (name == "explodebird") return &explodeBirdDefaults;
        return nullptr;
    }

    ObjectDefaults* getPigDefaults(const std::string& name) {
        if (name == "normalpig") return &normalPigDefaults;
        if (name == "ironpig") return &ironPigDefaults;
        return nullptr;
    }

    ObjectDefaults* getBlockDefaults(const std::string& name) {
        if (name == "icecircles") return &iceCircleS;
        if (name == "icecirclem") return &iceCircleM;
        if (name == "icesquare") return &iceSquare;
        if (name == "icetriangleleft") return &iceTriangleLeft;
        if (name == "icetriangleright") return &iceTriangleRight;
        if (name == "icerect") return &iceRect;
        if (name == "icerects") return &iceRectS;
        if (name == "icerectm") return &iceRectM;
        if (name == "icerectl") return &iceRectL;
        if (name == "woodcircles") return &woodCircleS;
        if (name == "woodcirclem") return &woodCircleM;
        if (name == "woodsquare") return &woodSquare;
        if (name == "woodtriangleleft") return &woodTriangleLeft;
        if (name == "woodtriangleright") return &woodTriangleRight;
        if (name == "woodrect") return &woodRect;
        if (name == "woodrects") return &woodRectS;
        if (name == "woodrectm") return &woodRectM;
        if (name == "woodrectl") return &woodRectL;
        if (name == "stonecircles") return &stoneCircleS;
        if (name == "stonecirclem") return &stoneCircleM;
        if (name == "stonesquare") return &stoneSquare;
        if (name == "stonetriangleleft") return &stoneTriangleLeft;
        if (name == "stonetriangleright") return &stoneTriangleRight;
        if (name == "stonerect") return &stoneRect;
        if (name == "stonerects") return &stoneRectS;
        if (name == "stonerectm") return &stoneRectM;
        if (name == "stonerectl") return &stoneRectL;
        if (name == "fixedcircles") return &fixedCircleS;
        if (name == "fixedcirclem") return &fixedCircleM;
        if (name == "fixedsquare") return &fixedSquare;
        if (name == "fixedtriangleleft") return &fixedTriangleLeft;
        if (name == "fixedtriangleright") return &fixedTriangleRight;
        if (name == "fixedrect") return &fixedRect;
        if (name == "fixedrects") return &fixedRectS;
        if (name == "fixedrectm") return &fixedRectM;
        if (name == "fixedrectl") return &fixedRectL;
        return nullptr;
    }
}
*/

#endif
