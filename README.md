CCMask
======

CCMask is a class which makes masking in Cocos2D-x v2.0 fairly easy.  
You just have to define an object and a mask. And that's it!

Usage:

    // Create a mask and an object
    CCSprite* mask = CCSprite::create("mask_circle.png");
    CCSprite* object = CCSprite::create("HelloWorld.png");
    object->setPosition(ccp(mask->getContentSize().width/2, mask->getContentSize().height/2));
    
    // Create a masked image
    CCMask* masked = CCMask::create(mask , object);
    masked->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(masked);

![alt text](http://blog.syuhari.jp/wp-content/uploads/2013/01/CCMask_image.png "CCMask Image")
