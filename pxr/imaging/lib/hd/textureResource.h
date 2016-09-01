//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef HD_TEXTURE_RESOURCE_H
#define HD_TEXTURE_RESOURCE_H

#include "pxr/imaging/hd/api.h"
#include "pxr/imaging/garch/gl.h"
#include "pxr/imaging/garch/glext.h"
#include "pxr/base/tf/declarePtrs.h"
#include "pxr/base/tf/token.h"

#include "pxr/imaging/hd/enums.h"
#include "pxr/imaging/glf/texture.h"
#include "pxr/imaging/glf/textureHandle.h"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<class HdTextureResource> HdTextureResourceSharedPtr;

class HdTextureResource {
public:
    typedef size_t ID;

    /// Returns the hash value of the texture for \a sourceFile
    HDLIB_API
    static ID ComputeHash(TfToken const & sourceFile);
    HDLIB_API
    static ID ComputeFallbackPtexHash();
    HDLIB_API
    static ID ComputeFallbackUVHash();

    HDLIB_API
    virtual ~HdTextureResource();

    virtual bool IsPtex() const = 0;

    virtual GLuint GetTexelsTextureId() = 0;
    virtual GLuint GetTexelsSamplerId() = 0;
    virtual GLuint64EXT GetTexelsTextureHandle() = 0;

    virtual GLuint GetLayoutTextureId() = 0;
    virtual GLuint64EXT GetLayoutTextureHandle() = 0;
};

class HdSimpleTextureResource : public HdTextureResource
                              , boost::noncopyable {
public:
    HDLIB_API
    HdSimpleTextureResource(GlfTextureHandleRefPtr const &textureHandle, bool isPtex);
    HDLIB_API
    HdSimpleTextureResource(GlfTextureHandleRefPtr const &textureHandle, bool isPtex, 
        HdWrap wrapS, HdWrap wrapT, HdMinFilter minFilter, HdMagFilter magFilter);
    HDLIB_API
    virtual ~HdSimpleTextureResource();

    HDLIB_API
    virtual bool IsPtex() const;

    HDLIB_API
    virtual GLuint GetTexelsTextureId();
    HDLIB_API
    virtual GLuint GetTexelsSamplerId();
    HDLIB_API
    virtual GLuint64EXT GetTexelsTextureHandle();

    HDLIB_API
    virtual GLuint GetLayoutTextureId();
    HDLIB_API
    virtual GLuint64EXT GetLayoutTextureHandle();

private:
    GlfTextureHandleRefPtr _textureHandle;
    GlfTextureRefPtr _texture;
    GLuint _sampler;
    bool _isPtex;
};

#endif //HD_TEXTURE_RESOURCE_H
