#include "MaskedSprite.h"
#include "../MaskedRenderer.h"
#include "../RenderDelegate.h"
#include "../RenderState.h"

namespace oxygine
{
    MaskedSprite::MaskedSprite() : _useRChannel(false)
    {
    }

    MaskedSprite::~MaskedSprite()
    {
    }

    spSprite MaskedSprite::getMask() const
    {
        return _mask;
    }

    bool    MaskedSprite::getUseRChannel() const
    {
        return _useRChannel;
    }

    void MaskedSprite::setMask(spSprite mask, bool useRChannel)
    {
        _mask = mask;
        _useRChannel = useRChannel;
    }


    void MaskedSprite::render(const RenderState& parentRS)
    {
        _rdelegate->render(this, parentRS);
    }
}
