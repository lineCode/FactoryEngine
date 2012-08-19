// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

class FTWorkspace : public FTNode
{
public:
                        FTWorkspace();
                        ~FTWorkspace();
    virtual void        Render();
    void                SetViewportRect(FTRectf);
private:
    FTPad*              mpPad;
    FTHUD*              mpHUD;
};

