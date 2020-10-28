#pragma once
#include "../oxygine-include.h"
#include "Actor.h"

namespace oxygine
{
    DECLARE_SMART(ClipRectActor, spClipRectActor);
    /**
    ClipRectActor clips all out of bound children. Rotation is not supported
    */
    class ClipRectActor : public Actor
    {
    public:
        ClipRectActor();
        ~ClipRectActor();

        bool getClipping() const { return _clipping; }

        /**Enables clipping for children. By default is on*/
        void setClipping(bool enable) {_clipping = enable;}

        void render(const RenderState& rs) override;


        void handleEvent(Event* event) override;
    protected:

        bool _clipping;
    };
}
