#pragma once
#include "3rd_party/oxygine-framework/oxygine-include.h"
#include "3rd_party/oxygine-framework/oxygine/actor/Actor.h"

namespace oxygine
{
    DECLARE_SMART(Stage, spStage);
    class Stage : public Actor
    {
    public:
        enum
        {
            ACTIVATE = sysEventID('S', 'A', 'c'),
            DEACTIVATE = sysEventID('S', 'D', 'c'),
            LOST_CONTEXT = sysEventID('S', 'L', 'C'),
        };

        static spStage instance;
        static Rect calcCenteredViewport(const Point& displaySize, const Point& gameSize);

        Stage();
        ~Stage();

        /**Initializes size, scale and position of Stage
        @param is real display size of device.
        @param is your "virtual" preferred size. You could change it to any size you need
        */
        void init(const Point& displaySize, const Point& gameSize);

        /**use Scissor test for outer Stage area*/
        void setClipOuterArea(bool clip) {_clipOuter = clip;}
        /**Render all actors*/
        void render(const QColor* clearColor, const Rect& viewport, const Matrix& view, const Matrix& proj);
        /**Render all actors, simplified version*/
        void render(const QColor& clearColor, const Rect& viewport);

        //const Rect    &getArea();

        /**Updates each children*/
        void update();

        void cleanup();

        RectF getDestRect() const override;

    protected:
        void onDeactivate(Event*);

        bool isOn(const Vector2& localPosition, float localScale) override;

    protected:

        timeMS _statUpdate;
        bool    _clipOuter;
        Rect    _viewport;
    };

    inline const spStage& getStage() {return Stage::instance;}
}
