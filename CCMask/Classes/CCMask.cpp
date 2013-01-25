//
//  CCMask.cpp
//
//  Created by Akihiro Matsuura on 1/22/13.
//
//


#include "CCMask.h"
USING_NS_CC;

CCMask* CCMask::create(CCSprite *maskSprite, CCSprite * sprite)
{
    CCMask* pRet = new CCMask();
    if (pRet && pRet->initWithMaskSprite(maskSprite, sprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CCMask::initWithMaskSprite(CCSprite *maskSprite, CCSprite *sprite)
{
    if (CCSprite::initWithTexture(maskSprite->getTexture()))
    {
        this->setSprite(sprite);
        
        // Set up the mask with the Mask shader
        this->setMaskSprite(maskSprite);
        this->setMaskTexture(maskSprite->getTexture());
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccExSwitchMask_frag);
        this->setShaderProgram(pProgram);
        pProgram->release();
        
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        this->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
        
        m_uTextureLocation    = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_texture");
        m_uMaskLocation       = glGetUniformLocation(this->getShaderProgram()->getProgram(), "u_mask");
        CHECK_GL_ERROR_DEBUG();
        
        this->setContentSize(m_pMaskTexture->getContentSize());
        
        needsLayout();
        return true;
    }
    return false;
}

void CCMask::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->getShaderProgram()->setUniformForModelViewProjectionMatrix();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, this->getTexture()->getName());
    glUniform1i(m_uTextureLocation, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture( GL_TEXTURE_2D, m_pMaskTexture->getName() );
    glUniform1i(m_uMaskLocation, 1);
    
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glActiveTexture(GL_TEXTURE0);
}

void CCMask::needsLayout()
{
    if (m_pSprite==NULL) return;
    
    m_pSprite->setFlipY(true);
    CCRenderTexture *rt = CCRenderTexture::create((int)m_pMaskTexture->getContentSize().width, (int)m_pMaskTexture->getContentSize().height);
    
    rt->begin();
    m_pSprite->visit();
    rt->end();
    
    this->setTexture(rt->getSprite()->getTexture());
}

void CCMask::changeObject(CCSprite* object_)
{
    this->setSprite(object_);
    this->needsLayout();
}

CCMask::~CCMask() {

}