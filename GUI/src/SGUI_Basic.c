/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Basic.c												**/
/** Author: XuYulin														**/
/** Version: 1.1.0.2													**/
/** Description: Simple GUI basic drawing operating interface.			**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Basic.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define SGUI_MIN_VAL(A, B)			(((A)>(B)?(B):(A)))
#define SGUI_MAX_VAL(A, B)			(((A)<(B)?(B):(A)))

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
//   Here is the 4*6 pixel font data definition, only number characters
// and plug(+), subtract(-), multiply(*), divide(/), brackets and space.
SGUI_CBYTE SGUI_BASIC_FONT_H6[] =
{
    0x1F, 0x11, 0x1F, 0x00,	//0
    0x00, 0x1F, 0x00, 0x00,	//1
    0x1D, 0x15, 0x17, 0x00,	//2
    0x15, 0x15, 0x1F, 0x00,	//3
    0x07, 0x04, 0x1F, 0x00,	//4
    0x17, 0x15, 0x1D, 0x00,	//5
    0x1F, 0x15, 0x1D, 0x00,	//6
    0x19, 0x05, 0x03, 0x00,	//7
    0x1F, 0x15, 0x1F, 0x00,	//8
    0x17, 0x15, 0x1F, 0x00,	//9
    0x00, 0x10, 0x00, 0x00,	//.
    0x04, 0x0E, 0x04, 0x00,	//+
    0x04, 0x04, 0x04, 0x00,	//-
    0x0A, 0x04, 0x0A, 0x00,	//**
    0x18, 0x04, 0x03, 0x00, ///
    0x00, 0x0E, 0x11, 0x00, //(
    0x11, 0x0E, 0x00, 0x00, //)
    0x00, 0x00, 0x00, 0x00, //space
};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawPoint								**/
/** Purpose:		Set a pixel color or draw a point.					**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ uiCoordinateX[in]: X coordinate of point by pixels.				**/
/**	@ uiCoordinateY[in]: Y coordinate of point by pixels.				**/
/**	@ eColor[in]:		Point color, GUI_COLOR_BKGCLR means clear pix, 	**/
/**						GUI_COLOR_FRGCLR means set pix.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiCoordinateX, SGUI_UINT uiCoordinateY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((NULL != pstIFObj) && (uiCoordinateX < RECT_WIDTH(pstIFObj->stSize)) && (uiCoordinateY < RECT_HEIGHT(pstIFObj->stSize)))
    {
    	if(NULL == pstIFObj->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
        else if(SGUI_COLOR_FRGCLR == eColor)
        {
            pstIFObj->fnSetPixel(uiCoordinateX, uiCoordinateY, 1);
        }
        else if(SGUI_COLOR_BKGCLR == eColor)
        {
            pstIFObj->fnSetPixel(uiCoordinateX, uiCoordinateY, 0);
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_GetPoint									**/
/** Purpose:		Get a pixel color .									**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ uiCoordinateX[in]: X coordinate of point by pixels.				**/
/**	@ uiCoordinateY[in]: Y coordinate of point by pixels.				**/
/** Return:			SGUI_COLOR type enumerated for point color.			**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_COLOR SGUI_Basic_GetPoint(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiCoordinateX, SGUI_UINT uiCoordinateY)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_COLOR					eColor;
    SGUI_UINT					uiPixValue;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    eColor =					SGUI_COLOR_BKGCLR;
    uiPixValue =				0;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((NULL != pstIFObj) && (uiCoordinateX < RECT_WIDTH(pstIFObj->stSize)) && (uiCoordinateY < RECT_HEIGHT(pstIFObj->stSize)))
    {
    	if(NULL == pstIFObj->fnSetPixel)
		{
			/* Action function is unspecified, no actions. */
		}
		else
		{
			uiPixValue = pstIFObj->fnGetPixel(uiCoordinateX, uiCoordinateY);
			if(0 == uiPixValue)
			{
				eColor = SGUI_COLOR_BKGCLR;
			}
			else
			{
				eColor = SGUI_COLOR_FRGCLR;
			}
		}
    }

    return eColor;
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_ClearScreen								**/
/** Purpose:		Clean LCD screen display.							**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_ClearScreen(SGUI_SCR_DEV* pstIFObj)
{
    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(NULL != pstIFObj)
	{
		/* Clear screen. */
        if((NULL != pstIFObj->fnClear) && (NULL != pstIFObj->fnSyncBuffer))
		{
			pstIFObj->fnClear();
		}
		else
		{
			SGUI_Basic_DrawRectangle(pstIFObj, 0, 0, RECT_WIDTH(pstIFObj->stSize), RECT_HEIGHT(pstIFObj->stSize), SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawLine									**/
/** Purpose:		Draw a line by the Bresenham algorithm.				**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ iStartX[in]:		X coordinate of start point of line.			**/
/**	@ iStartY[in]:		Y coordinate of start point of line.			**/
/**	@ iEndX[in]:		X coordinate of end point of line.				**/
/**	@ iEndY[in]:		Y coordinate of end point of line.				**/
/**	@ eColor[in]:		Line color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawLine(SGUI_SCR_DEV* pstIFObj, SGUI_INT iStartX, SGUI_INT iStartY, SGUI_INT iEndX, SGUI_INT iEndY, SGUI_COLOR eColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_INT					iDx, iDy;
    SGUI_INT					iIncX, iIncY;
    SGUI_INT					iErrX = 0, iErrY = 0;
    SGUI_INT					i, iDs;
    SGUI_INT					iCurrentPosX, iCurrentPosY;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    iErrX = 0;
    iErrY = 0;
    iDx = iEndX - iStartX;
    iDy = iEndY - iStartY;
    iCurrentPosX = iStartX;
    iCurrentPosY = iStartY;

    if(iDx > 0)
    {
        iIncX = 1;
    }
    else
    {
        if(iDx == 0)
        {
            iIncX = 0;
        }
        else
        {
            iIncX = -1;
            iDx = -iDx;
        }
    }

    if(iDy > 0)
    {
        iIncY = 1;
    }
    else
    {
        if(iDy == 0)
        {
            iIncY = 0;
        }
        else
        {
            iIncY = -1;
            iDy = -iDy;
        }
    }

    if(iDx > iDy)
    {
        iDs = iDx;
    }
    else
    {
        iDs = iDy;
    }

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(i = 0; i <= iDs+1; i++)
    {
        SGUI_Basic_DrawPoint(pstIFObj, iCurrentPosX,iCurrentPosY, eColor);
        iErrX += iDx;
        if(iErrX > iDs)
        {
            iErrX -= iDs;
            iCurrentPosX += iIncX;
        }
        iErrY += iDy;
        if(iErrY > iDs)
        {
            iErrY -= iDs;
            iCurrentPosY += iIncY;
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawRectangle							**/
/** Purpose:		Draw a rectangle on screen. 						**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ uiStartX[in]:		X coordinate of the upper-left corner.			**/
/**	@ uiStartY[in]:		Y coordinate of the upper-left corner.			**/
/**	@ uiWidth[in]: .	Width of rectangle.								**/
/**	@ uiHeight[in]:		Height of rectangle.							**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					uiColumnIndex;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if((uiWidth > 0) && (uiHeight > 0))
    {
        if((uiWidth == 1) && (uiHeight == 1))
        {
            SGUI_Basic_DrawPoint(pstIFObj, uiStartX, uiStartY, eEdgeColor);
        }
        else if(uiWidth == 1)
        {
            SGUI_Basic_DrawLine(pstIFObj, uiStartX, uiStartY, uiStartX, uiStartY+uiHeight-1, eEdgeColor);
        }
        else if(uiHeight == 1)
        {
            SGUI_Basic_DrawLine(pstIFObj, uiStartX, uiStartY, uiStartX+uiWidth-1, uiStartY, eEdgeColor);
        }
        else
        {
            // Draw edge.
            // Check and set changed page and column index is in edge display action.
            SGUI_Basic_DrawLine(pstIFObj, uiStartX, uiStartY, uiStartX, uiStartY+uiHeight-1, eEdgeColor);
            SGUI_Basic_DrawLine(pstIFObj, uiStartX+uiWidth-1, uiStartY, uiStartX+uiWidth-1, uiStartY+uiHeight-1, eEdgeColor);
            SGUI_Basic_DrawLine(pstIFObj, uiStartX, uiStartY, uiStartX+uiWidth-1, uiStartY, eEdgeColor);
            SGUI_Basic_DrawLine(pstIFObj, uiStartX, uiStartY+uiHeight-1, uiStartX+uiWidth-1, uiStartY+uiHeight-1, eEdgeColor);
            // Fill area.
            if((eFillColor != SGUI_COLOR_TRANS) && (uiWidth > 2) && (uiHeight > 2))
            {
                for(uiColumnIndex=(uiStartX+1); uiColumnIndex<(uiStartX+uiWidth-1); uiColumnIndex++)
                {
                    SGUI_Basic_DrawLine(pstIFObj, uiColumnIndex, uiStartY+1, uiColumnIndex, uiStartY+uiHeight-2, eFillColor);
                }
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawCircle								**/
/** Purpose:		Draw a circle by center coordinate and radius.		**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ uiCx[in]:			Circle center X coordinate.						**/
/**	@ uiCy[in]:			Circle center Y coordinate.						**/
/**	@ uiRadius[in]:		Circle radius.									**/
/**	@ eEdgeColor[in]:	Edge color.										**/
/**	@ eFillColor[in]:	Fill color.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiCx, SGUI_UINT uiCy, SGUI_UINT uiRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					uiPosXOffset, uiPosYOffset;
    SGUI_UINT					uiPosXOffset_Old, uiPosYOffset_Old;
    SGUI_INT					iXChange, iYChange, iRadiusError;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    uiPosXOffset				= uiRadius;
    uiPosYOffset				= 0;
    uiPosXOffset_Old			= 0xFFFF;
    uiPosYOffset_Old			= 0xFFFF;
    iXChange					= 1 - 2 * uiRadius;
    iYChange					= 1;
    iRadiusError				= 0;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    if(uiRadius < 1)
    {
        SGUI_Basic_DrawPoint(pstIFObj, uiCx, uiCy, eEdgeColor);
    }
    else
    {
        while(uiPosXOffset >= uiPosYOffset)
        {
            if((uiPosXOffset_Old != uiPosXOffset) || (uiPosYOffset_Old != uiPosYOffset) )
            {
                // Fill the circle
                if((uiRadius > 1) && (eFillColor != SGUI_COLOR_TRANS) && (uiPosXOffset_Old != uiPosXOffset))
                {

                    SGUI_Basic_DrawLine(pstIFObj, uiCx-uiPosXOffset, uiCy-uiPosYOffset+1, uiCx-uiPosXOffset, uiCy+uiPosYOffset-1, eFillColor);
                    SGUI_Basic_DrawLine(pstIFObj, uiCx+uiPosXOffset, uiCy-uiPosYOffset+1, uiCx+uiPosXOffset, uiCy+uiPosYOffset-1, eFillColor);
                    uiPosXOffset_Old = uiPosXOffset;
                }
                SGUI_Basic_DrawLine(pstIFObj, uiCx-uiPosYOffset, uiCy-uiPosXOffset+1, uiCx-uiPosYOffset, uiCy+uiPosXOffset-1, eFillColor);
                SGUI_Basic_DrawLine(pstIFObj, uiCx+uiPosYOffset, uiCy-uiPosXOffset+1, uiCx+uiPosYOffset, uiCy+uiPosXOffset-1, eFillColor);
                uiPosYOffset_Old = uiPosYOffset;

                // Draw edge.
                SGUI_Basic_DrawPoint(pstIFObj, uiCx+uiPosXOffset, uiCy+uiPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx-uiPosXOffset, uiCy+uiPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx-uiPosXOffset, uiCy-uiPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx+uiPosXOffset, uiCy-uiPosYOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx+uiPosYOffset, uiCy+uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx-uiPosYOffset, uiCy+uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx-uiPosYOffset, uiCy-uiPosXOffset, eEdgeColor);
                SGUI_Basic_DrawPoint(pstIFObj, uiCx+uiPosYOffset, uiCy-uiPosXOffset, eEdgeColor);
            }
            uiPosYOffset++;
            iRadiusError += iYChange;
            iYChange += 2;
            if ((2 * iRadiusError + iXChange) > 0)
            {
                uiPosXOffset--;
                iRadiusError += iXChange;
                iXChange += 2;
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_ReverseBlockColor						**/
/** Purpose:		Reverse all pixel color in a rectangle area.		**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ uiStartX[in]:		X coordinate of the upper-left corner.			**/
/**	@ uiStartY[in]:		Y coordinate of the upper-left corner.			**/
/**	@ uiWidth[in]: .	Width of rectangle.								**/
/**	@ uiHeight[in]:		Height of rectangle.							**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    SGUI_UINT					i_W, i_H;

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(i_W=0; i_W<uiWidth; i_W++)
    {
        for(i_H=0; i_H<uiHeight; i_H++)
        {
            if(SGUI_Basic_GetPoint(pstIFObj, uiStartX+i_W, uiStartY+i_H) == SGUI_COLOR_FRGCLR)
            {
                SGUI_Basic_DrawPoint(pstIFObj, uiStartX+i_W, uiStartY+i_H, SGUI_COLOR_BKGCLR);
            }
            else
            {
                SGUI_Basic_DrawPoint(pstIFObj, uiStartX+i_W, uiStartY+i_H, SGUI_COLOR_FRGCLR);
            }
        }
    }
}

/*************************************************************************/
/** Function Name:	SGUI_Basic_DrawBitMap								**/
/** Purpose:		Draw a rectangular area bit map on LCD screen.		**/
/** Params:																**/
/**	@ pstIFObj[in]:	SimpleGUI object pointer.							**/
/**	@ pstDisplayArea[in]: Display area position and size.				**/
/**	@ pstDataArea[in]:	Data area size and display offset.				**/
/**	@ pDataBuffer[in]:	Bit map data buffer.							**/
/**	@ eDrawMode[in]		Bit map display mode(normal or reverse color).	**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Basic_DrawBitMap(SGUI_SCR_DEV* pstIFObj, SGUI_RECT_AREA* pstDisplayArea, SGUI_RECT_AREA* pstDataArea, SGUI_FLASH_DATA_SOURCE eDataSource, SGUI_ROM_ADDRESS adDataStartAddr, SGUI_DRAW_MODE eDrawMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iDrawPixX, iDrawPixY;
	SGUI_INT					iBmpPixX, iBmpPixY;
	SGUI_UINT					uiDrawnWidthIndex, uiDrawnHeightIndex;
	SGUI_UINT					uiPixIndex;
	SGUI_BYTE*					pData;
	SGUI_SIZE					sBitmapDataSize;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiDrawnWidthIndex			= 0;
	uiDrawnHeightIndex			= 0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Only draw in visible area of screen.
	if(	(RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstIFObj->stSize)) && (RECT_Y_START(*pstDisplayArea) < RECT_HEIGHT(pstIFObj->stSize)) &&
		(RECT_X_END(*pstDisplayArea) > 0) && (RECT_Y_END(*pstDisplayArea) > 0))
	{
		// Recalculate display area and data area.
		if(RECT_X_START(*pstDisplayArea) < 0)
		{
			RECT_X_START(*pstDataArea) += RECT_X_START(*pstDisplayArea);
			RECT_WIDTH(*pstDisplayArea) += RECT_X_START(*pstDisplayArea);
			RECT_X_START(*pstDisplayArea) = 0;
		}
		if(RECT_Y_START(*pstDisplayArea) < 0)
		{
			RECT_Y_START(*pstDataArea) += RECT_Y_START(*pstDisplayArea);
			RECT_HEIGHT(*pstDisplayArea) += RECT_Y_START(*pstDisplayArea);
			RECT_Y_START(*pstDisplayArea) = 0;
		}
		// Only process drawing when valid display data existed
		if((RECT_VALID_WIDTH(*pstDataArea) > 0) && (RECT_VALID_HEIGHT(*pstDataArea) > 0))
		{
			// Calculate bitmap data size.
			sBitmapDataSize = pstDataArea->Width * ((pstDataArea->Height-1)/8+1);
			// Read flash data.
			SGUI_SystemIF_GetFlashData(pstIFObj, eDataSource, adDataStartAddr, sBitmapDataSize);
			// Set loop start parameter of x coordinate
			iDrawPixX = RECT_X_START(*pstDisplayArea);
			iBmpPixX = 0;
			if(RECT_X_START(*pstDataArea) > 0)
			{
				iDrawPixX += RECT_X_START(*pstDataArea);
			}
			else
			{
				iBmpPixX -= RECT_X_START(*pstDataArea);
			}
			uiDrawnWidthIndex = iBmpPixX;
			// Loop for x coordinate;
			while((uiDrawnWidthIndex<RECT_WIDTH(*pstDataArea)) && (iDrawPixX<=RECT_X_END(*pstDisplayArea)) && (iDrawPixX<RECT_WIDTH(pstIFObj->stSize)))
			{
				// Redirect to data array for column.
				pData = pstIFObj->arrBmpDataBuffer + iBmpPixX;
				// Set loop start parameter of y coordinate
				iDrawPixY = RECT_Y_START(*pstDisplayArea);
				iBmpPixY = 0;
				if(RECT_Y_START(*pstDataArea) > 0)
				{
					iDrawPixY += RECT_Y_START(*pstDataArea);
				}
				else
				{
					iBmpPixY -= RECT_Y_START(*pstDataArea);
				}
				uiDrawnHeightIndex = iBmpPixY;
				uiPixIndex = iBmpPixY % 8;
				pData += (iBmpPixY / 8) * RECT_WIDTH(*pstDataArea);
				// Loop for y coordinate;
				while((uiDrawnHeightIndex<RECT_HEIGHT(*pstDataArea)) && (iDrawPixY<=RECT_Y_END(*pstDisplayArea)) && (iDrawPixY<RECT_HEIGHT(pstIFObj->stSize)))
				{
					if(uiPixIndex == 8)
					{
						uiPixIndex = 0;
						pData += RECT_WIDTH(*pstDataArea);
					}
					if(SGUI_GET_PAGE_BIT(*pData, uiPixIndex) != eDrawMode)
					{
						SGUI_Basic_DrawPoint(pstIFObj, iDrawPixX, iDrawPixY, SGUI_COLOR_FRGCLR);
					}
					else
					{
						SGUI_Basic_DrawPoint(pstIFObj, iDrawPixX, iDrawPixY, SGUI_COLOR_BKGCLR);
					}
					uiDrawnHeightIndex ++;
					uiPixIndex ++;
					iDrawPixY ++;
					iBmpPixY ++;
				}
				uiDrawnWidthIndex ++;
				iDrawPixX ++;
				iBmpPixX ++;
			}
		}
	}
}
