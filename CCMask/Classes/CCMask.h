//
//  CCMask.h
//
//  Created by Akihiro Matsuura on 1/22/13.
//
//

#ifndef __Tailer__CCMask__
#define __Tailer__CCMask__

#include "cocos2d.h"
using namespace cocos2d;

class CCMask : public CCSprite {
private:
    void needsLayout();
    void draw();
public:
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pSprite, Sprite)
    CC_SYNTHESIZE_RETAIN(CCTexture2D*, m_pMaskTexture, MaskTexture)
    CC_SYNTHESIZE(GLuint, m_uTextureLocation, TextureLocation)
    CC_SYNTHESIZE(GLuint, m_uMaskLocation, MaskLocation)
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pMaskSprite, MaskSprite);
    
    CCMask();
    virtual ~CCMask();

    // Initialize a masked object based on an object sprite and a mask sprite
    bool initWithMaskSprite(CCSprite *maskSprite, CCSprite *sprite);
    static CCMask* create(CCSprite *maskSprite, CCSprite * sprite);

    void changeObject(CCSprite* object);
};

#endif /* defined(__Tailer__CCMask__) */
