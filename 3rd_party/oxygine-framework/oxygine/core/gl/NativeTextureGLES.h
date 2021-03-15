#pragma once
#include "3rd_party/oxygine-framework/oxygine/oxygine-include.h"
#include "3rd_party/oxygine-framework/oxygine/core/NativeTexture.h"
#include <QOpenGLShader>

namespace oxygine
{
    DECLARE_SMART(NativeTextureGLES, spNativeTextureGLES);
    class NativeTextureGLES : public NativeTexture
    {
    public:
        ~NativeTextureGLES();

        void init(GLuint id, int w, int h, ImageData::TextureFormat tf);
        void init(int w, int h, ImageData::TextureFormat tf, bool renderTarget);
        void init(const ImageData& src, bool sysMemCopy);
        void release();
        void swap(NativeTexture*) ;

        nativeTextureHandle getHandle() const;
        int                 getWidth() const;
        int                 getHeight() const;
        ImageData::TextureFormat       getFormat() const;
        unsigned int        getFboID() const;

        ImageData lock(lock_flags, const Rect* src);
        void unlock();

        void setLinearFilter(quint32 filter) override;
        void setClamp2Edge(bool clamp2edge);

        void updateRegion(int x, int y, const ImageData& data);
        void apply(const Rect* rect = 0);

        GLuint getId() override
        {
            return _id;
        }
    protected:
        void* _getRestorableObject() {return this;}
        friend class VideoDriverGL;
        friend class VideoDriverGLES20;
        NativeTextureGLES();

        GLuint _id;
        size_t _fbo;

        ImageData::TextureFormat _format;
        int _width;
        int _height;


        QVector<unsigned char> _data;
        int _lockFlags;
        Rect _lockRect;
    };
}
