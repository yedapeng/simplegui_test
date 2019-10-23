/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Notice.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Notice box display interface.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Notice.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
// User settings
#define NOTICE_BOX_EDGE_DIST								(6)
#define NOTICE_BOX_MARGIN									(2)

// Automatic calculation
#define NOTICE_BOX_WIDTH(SCR_OBJ)							(((SCR_OBJ).stSize.Width)-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT_MIN(FONT_SIZE)					(g_stFontSize[FONT_SIZE].Height*2+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_HEIGHT_MAX(SCR_OBJ)						(((SCR_OBJ).stSize.Height)-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT(LINES, FONT_SIZE)					(LINES*g_stFontSize[FONT_SIZE].Height+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_POSX										(NOTICE_BOX_EDGE_DIST)
#define NOTICE_BOX_POSY(SCR_OBJ, HEIGHT)					((((SCR_OBJ).stSize.Height)-HEIGHT)/2)
#define NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)				(NOTICE_BOX_WIDTH(SCR_OBJ)-NOTICE_BOX_MARGIN*4)
#define	NOTICE_TEXT_AREA_WIDTH(SCR_OBJ)						(NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)-NOTICE_ICON_SIZE-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT(LINES, FONT_SIZE)			(NOTICE_BOX_HEIGHT(LINES, FONT_SIZE)-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT_MIN(FONT_SIZE)				(g_stFontSize[FONT_SIZE].Height*2)
#define NOTICE_TEXT_AREA_HEIGHT_MAX(SCR_OBJ)				(NOTICE_BOX_HEIGHT_MAX(SCR_OBJ)-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX_NOICON								(NOTICE_BOX_POSX+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX									(NOTICE_TEXT_POSX_NOICON+NOTICE_ICON_SIZE+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSY(SCR_OBJ, HEIGHT)					(NOTICE_BOX_POSY(SCR_OBJ, HEIGHT)+NOTICE_BOX_MARGIN)
#define	NOTICE_TEXT_LINES_MAX(SCR_OBJ, FONT_SIZE)			(NOTICE_TEXT_AREA_WIDTH(SCR_OBJ)/g_stFontSize[FONT_SIZE].Width)
#define	NOTICE_TEXT_LINES_MAX_NOICON(SCR_OBJ, FONT_SIZE)	(NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)/g_stFontSize[FONT_SIZE].Width)

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Notice_RefreshNotice							**/
/** Purpose:		Show a notice box.									**/
/** Params:																**/
/** Params:																**/
/**	@ pstIFObj[in]:		SimpleGUI object pointer.						**/
/**	@ szNoticeText[in]:	Notice text.									**/
/** @ iFontSize[in]:	Text font size.									**/
/**	@ uiTextOffset[in]:	Text top offset.								**/
/**	@ eIcon[in]:		Notice icon index.								**/
/** Return:			Remaining text height display.						**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_SIZE SGUI_Notice_Repaint(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR szNoticeText, SGUI_FONT_SIZE iFontSize, SGUI_INT uiTextOffset, SGUI_NOTICE_ICON_IDX eIcon)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiLineCount;
	SGUI_SIZE					uiNoticeBoxHeight;
	SGUI_SIZE					uiTextLines;
	SGUI_RECT_AREA				stTextDisplayArea;
	SGUI_RECT_AREA				stIconDisplayArea, stIconDataArea;
	SGUI_CSZSTR				pszNoticeTextPtr;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Encode string if defined.
	pszNoticeTextPtr = szNoticeText;
	// Get max line of notice text.
	if(SGUI_ICON_NONE != eIcon)
	{
		uiLineCount = SGUI_Text_GetMultiLineTextLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX(*pstIFObj, iFontSize));
	}
	else
	{
		uiLineCount = SGUI_Text_GetMultiLineTextLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX_NOICON(*pstIFObj, iFontSize));
	}
	if(uiLineCount < 2)
	{
		uiLineCount = 2;
	}
	uiNoticeBoxHeight = NOTICE_BOX_HEIGHT(uiLineCount, iFontSize);
	if(uiNoticeBoxHeight > NOTICE_BOX_HEIGHT_MAX(*pstIFObj))
	{
		uiNoticeBoxHeight = NOTICE_BOX_HEIGHT_MAX(*pstIFObj);
	}
	// Draw edge
    SGUI_Basic_DrawRectangle(pstIFObj, NOTICE_BOX_POSX, NOTICE_BOX_POSY(*pstIFObj, uiNoticeBoxHeight), NOTICE_BOX_WIDTH(*pstIFObj), uiNoticeBoxHeight, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
    // Draw icon if exists.
    if(SGUI_ICON_NONE != eIcon)
	{
		stIconDisplayArea.PosX = NOTICE_BOX_POSX+NOTICE_BOX_MARGIN;
		stIconDisplayArea.PosY = NOTICE_BOX_POSY(*pstIFObj, uiNoticeBoxHeight)+NOTICE_BOX_MARGIN;
		stIconDisplayArea.Width = NOTICE_ICON_SIZE;
		stIconDisplayArea.Height = NOTICE_ICON_SIZE;
		stIconDataArea.PosX = 0;
		stIconDataArea.PosY = 0;
		stIconDataArea.Width = NOTICE_ICON_SIZE;
		stIconDataArea.Height = NOTICE_ICON_SIZE;
		SGUI_Basic_DrawBitMap(pstIFObj, &stIconDisplayArea, &stIconDataArea, SGUI_NOTICE_ICON, eIcon*(NOTICE_ICON_SIZE*(NOTICE_ICON_SIZE/8)), SGUI_DRAW_NORMAL);
	}
    // Draw text;
    if(SGUI_ICON_NONE != eIcon)
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH(*pstIFObj);
	}
	else
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX_NOICON;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH_NOICON(*pstIFObj);
	}
	stTextDisplayArea.PosY = NOTICE_TEXT_POSY(*pstIFObj, uiNoticeBoxHeight);
	stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT(uiLineCount, iFontSize);
    if(stTextDisplayArea.Height > NOTICE_TEXT_AREA_HEIGHT_MAX(*pstIFObj))
	{
		stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT_MAX(*pstIFObj);
	}

    uiTextLines = SGUI_Text_DrawMultipleLinesText(pstIFObj, pszNoticeTextPtr, iFontSize, &stTextDisplayArea, uiTextOffset, SGUI_DRAW_NORMAL);

    return uiTextLines;
}




