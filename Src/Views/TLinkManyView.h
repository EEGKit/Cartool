/************************************************************************\
Copyright 2024 CIBM (Center for Biomedical Imaging), Lausanne, Switzerland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
\************************************************************************/

#pragma once

#include    "TBaseView.h"
#include    "TLinkManyDoc.h"

namespace crtl {

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

enum    {
        LMVIEW_CBG_SEP1          = NumBaseViewButtons,
        LMVIEW_CBG_GTVKEEPSIZE,
        LMVIEW_CBG_GTVSTANDSIZE,
        LMVIEW_CBG_GTVFIT,
        LMVIEW_CBG_SEP2,
        LMVIEW_CBG_ADDTOGROUP,
        LMVIEW_CBG_SEP3,
        LMVIEW_CBG_SYNCALL,
        LMVIEW_CBG_DESYNCALL,
        LMVIEW_CBG_SYNCBETWEENEEG,
        LMVIEW_CBG_DESYNCBETWEENEEG,
        LMVIEW_CBG_COMMANDSCLONING,
        LMVIEW_CBG_SEP4,
        LMVIEW_CBG_SEGMENT,
        LMVIEW_CBG_NUM
        };


class   TLinkManyView : public  TBaseView
{
public:
                        TLinkManyView ( TLinkManyDoc& doc, owl::TWindow* parent = 0 );


    static const char*  StaticName          ()  { return "LinkMany &Display"; }
    const char*         GetViewName         ()  { return StaticName(); }

    void                SetupWindow         ();
    void                GLPaint             ( int how, int renderingmode, TGLClipPlane *otherclipplane );

    owl::TSize          GetBestSize         ();


protected:
    bool                CanClose            ()                                          { return owl::TWindowView::CanClose (); }

    int                 GetNumLines ();
    void                ViewIndexToPosition ( int i, TGLCoordinates<float> &p );
    TBaseDoc*           PositionToDoc       ( const owl::TPoint &p );

    void                Paint               ( owl::TDC& dc, bool erase, owl::TRect& rect );
    void                EvSetFocus          ( HWND hwnd )                               { TBaseView::EvSetFocus  ( hwnd );  }
    void                EvKillFocus         ( HWND hwnd )                               { TBaseView::EvKillFocus ( hwnd );  }
    void                EvKeyDown           ( owl::uint key, owl::uint repeatCount, owl::uint flags );
    void                EvLButtonDown       ( owl::uint, const owl::TPoint &p );
    void                EvLButtonDblClk     ( owl::uint, const owl::TPoint & );
    void                EvSize              ( owl::uint, const owl::TSize& );

    void                CmGTV               ( owlwparam w );
    void                CmAddToGroup        ();
    void                CmSegment           ();
    void                CmSyncUtility       ( owlwparam w );
    void                CmCommandsCloning   ();

    bool                VnReloadData        ( int what );

    DECLARE_RESPONSE_TABLE (TLinkManyView);
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

}
