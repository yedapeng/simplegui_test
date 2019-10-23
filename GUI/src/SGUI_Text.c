/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Text.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Text display interface									**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Text.h"

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
const SGUI_FONT_SIZE_STRUCT	g_stFontSize[SGUI_FONT_SIZE_MAX] = {	{6,   4,   6,   4},
																	{8,   6,   8,	6},
																	{12,  6,   12,	12},
																	{16,  8,   16,	16},
																	{24,  12,  24,	36},
																	{32,  16,  32,	64}};

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static SGUI_SIZE			SGUI_Text_GetCharacterTableIndex(SGUI_UINT16 uiCharacterCode);
static SGUI_FLASH_DATA_SOURCE SGUI_Text_GetFontResource(SGUI_FONT_SIZE eFontSize);

//=======================================================================//
//= Function define.										            =//
//=======================================================================//

/*************************************************************************/
/** Function Name:	SGUI_Text_DrawSingleLineText						**/
/** Purpose:		Write a single line text in a fixed area.			**/
/** Params:																**/
/**	@szText[in]:		Text array pointer.								**/
/**	@eFontSize[in]:		Font size.										**/
/**	@pstDisplayArea[in]: Display area size.								**/
/**	@pstTextDataArea[in]: Text area size.								**/
/**	@eFontMode[in]		Character display mode(normal or reverse color).**/
/** Return:			Next character X coordinate in current line.		**/
/** Limitation:		None.												**/
/*************************************************************************/
void SGUI_Text_DrawSingleLineText(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR szText, SGUI_FONT_SIZE eFontSize, SGUI_RECT_AREA* pstDisplayArea, SGUI_RECT_AREA* pstTextDataArea, SGUI_DRAW_MODE eFontMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SZSTR					pcTextPointer;										// Text character pointer.
	SGUI_UINT16					uiCodeHighByte, uiCodeLowByte, uiCharacterCode;		// Character byte, might be tow bytes.
	SGUI_UINT16					uiFontWidth, uiFontHeight, uiCharacterWidth;		// Font size and character graphics width.
	SGUI_UINT32					uiCharacterDataSize;
	SGUI_RECT_AREA				stCharacterDataArea = {0};
	SGUI_COLOR					eBackColor;
	SGUI_FLASH_DATA_SOURCE		eFontResource;
	SGUI_ROM_ADDRESS			adFontDataAddr;
	SGUI_INT					iFontDataIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Initialize variable.
	pcTextPointer =				(SGUI_SZSTR)ENCODE(szText);
	uiCharacterCode =			0x0000;
	eBackColor =				(eFontMode == SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR;
	// Get font graphics size.
	uiFontWidth =				g_stFontSize[eFontSize].Width;
	uiFontHeight =				g_stFontSize[eFontSize].Height;
	uiCharacterDataSize =		(((uiFontHeight-1)/8)+1)*uiFontWidth;
	eFontResource =				SGUI_Text_GetFontResource(eFontSize);
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((szText != NULL) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstIFObj->stSize)) && (SGUI_FONT_SRC_UNKNOWN != eFontResource))
	{
		// Recalculate text display area and data area.
        if(RECT_X_START(*pstDisplayArea) < 0)
		{
			RECT_X_START(*pstTextDataArea) += RECT_X_START(*pstDisplayArea);
			RECT_WIDTH(*pstDisplayArea) += RECT_X_START(*pstDisplayArea);
			RECT_X_START(*pstDisplayArea) = 0;
		}
		if(RECT_Y_START(*pstDisplayArea) < 0)
		{
			RECT_Y_START(*pstTextDataArea) += RECT_Y_START(*pstDisplayArea);
			RECT_HEIGHT(*pstDisplayArea) += RECT_Y_START(*pstDisplayArea);
			RECT_Y_START(*pstDisplayArea) = 0;
		}
		// Clear text area.
        SGUI_Basic_DrawRectangle(pstIFObj, RECT_X_START(*pstDisplayArea), RECT_Y_START(*pstDisplayArea),
						RECT_WIDTH(*pstDisplayArea), RECT_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);
		// Initialize drawing area data.
		RECT_X_START(stCharacterDataArea) = RECT_X_START(*pstTextDataArea);
		RECT_Y_START(stCharacterDataArea) = RECT_Y_START(*pstTextDataArea);
		RECT_HEIGHT(stCharacterDataArea) = uiFontHeight;
		// Loop for Each char.
		while(((NULL != pcTextPointer) && ('\0' != *pcTextPointer)) && (RECT_X_START(stCharacterDataArea) < RECT_WIDTH(*pstDisplayArea)))
		{
			// Get character.
			uiCodeHighByte = 0x00;
			uiCodeLowByte = 0x00;
			// Process with ASCII code.
			if((SGUI_BYTE)(*pcTextPointer) < 0x7F)
			{
				uiCodeLowByte = (SGUI_BYTE)(*pcTextPointer);
				uiCharacterWidth = uiFontWidth;
				pcTextPointer++;
			}
			// Process with GB2312.
			else if(((SGUI_BYTE)(*pcTextPointer) >= 0xA1) && ((SGUI_BYTE)(*pcTextPointer) <= 0xF7))
			{
				uiCodeHighByte = (SGUI_BYTE)*pcTextPointer++;
				uiCodeLowByte = (SGUI_BYTE)*pcTextPointer++;
				uiCharacterWidth = uiFontWidth << 1;	//uiCharacterWidth = uiFontWidth * 2; for full-width character;
			}
			// Invalid character
			else
			{
				uiCharacterWidth = 0;
				pcTextPointer++;
				continue;
			}
			uiCharacterCode = uiCodeHighByte;
			uiCharacterCode = uiCharacterCode << 8;
			uiCharacterCode = uiCharacterCode | uiCodeLowByte;

			RECT_WIDTH(stCharacterDataArea) = uiCharacterWidth;

			if(RECT_X_END(stCharacterDataArea) >= 0)
			{
				iFontDataIndex = SGUI_Text_GetCharacterTableIndex(uiCharacterCode);
				adFontDataAddr = iFontDataIndex * uiCharacterDataSize;
				SGUI_Basic_DrawBitMap(pstIFObj, pstDisplayArea, &stCharacterDataArea, eFontResource, adFontDataAddr, eFontMode);
			}
			RECT_X_START(stCharacterDataArea) += uiCharacterWidth;
		}
	}
}


/*****************************************************************************/
/** Function Name:	GUI_DrawMultipleLinesText								**/
/** Purpose:		Write a mulitiplt line text in a rectangular area.		**/
/** Params:																	**/
/**	@szText[in]:		Text array pointer.									**/
/**	@eFontSize[in]:		Font size.											**/
/**	@pstDisplayArea[in]: Display area size.									**/
/**	@eFontMode[in]:		Character display mode(normal or reverse color).	**/
/** Return:			Next character X coordinate in current line.			**/
/** Notice:			None.													**/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_DrawMultipleLinesText(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR szText, SGUI_FONT_SIZE eFontSize, SGUI_RECT_AREA* pstDisplayArea, SGUI_INT iTopOffset, SGUI_DRAW_MODE eFontMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SZSTR					pcTextPointer;
	SGUI_UINT16					uiCodeHighByte, uiCodeLowByte, uiCharacterCode;
	SGUI_UINT16					uiFontWidth, uiFontHeight;
	SGUI_UINT32					uiCharacterDataSize;
	SGUI_SIZE					uiLines;
	SGUI_RECT_AREA				stCharacterDataArea = {0};
	SGUI_COLOR					eBackColor;
	SGUI_FLASH_DATA_SOURCE		eFontResource;
	SGUI_ROM_ADDRESS			adFontDataAddr;
	SGUI_INT					iFontDataIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcTextPointer =				(SGUI_SZSTR)ENCODE(szText);
	uiCharacterCode =			0x0000;
	uiLines =					0;
	eBackColor =				(eFontMode == SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR;
	// Get font graphics size.
	uiFontWidth =				g_stFontSize[eFontSize].Width;
	uiFontHeight =				g_stFontSize[eFontSize].Height;
	uiCharacterDataSize =		(((uiFontHeight-1)/8)+1)*uiFontWidth;
	eFontResource =				SGUI_Text_GetFontResource(eFontSize);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((szText != NULL) && (RECT_X_START(*pstDisplayArea) < RECT_WIDTH(pstIFObj->stSize)))
	{
		// Recalculate text display area and data area.
		if(RECT_X_START(*pstDisplayArea) < 0)
		{
			RECT_X_START(stCharacterDataArea) += RECT_X_START(*pstDisplayArea);
			RECT_WIDTH(*pstDisplayArea) += RECT_X_START(*pstDisplayArea);
			RECT_X_START(*pstDisplayArea) = 0;
		}
		if(RECT_Y_START(*pstDisplayArea) < 0)
		{
			RECT_Y_START(stCharacterDataArea) += RECT_Y_START(*pstDisplayArea);
			RECT_HEIGHT(*pstDisplayArea) += RECT_Y_START(*pstDisplayArea);
			RECT_Y_START(*pstDisplayArea) = 0;
		}
		// Clear text area.
        SGUI_Basic_DrawRectangle(pstIFObj,
						RECT_X_START(*pstDisplayArea), RECT_Y_START(*pstDisplayArea),
						RECT_WIDTH(*pstDisplayArea), RECT_HEIGHT(*pstDisplayArea),
						eBackColor, eBackColor);
		// Initialize drawing area data.
		RECT_X_START(stCharacterDataArea)		= 0;
		RECT_Y_START(stCharacterDataArea)		= iTopOffset;
		RECT_HEIGHT(stCharacterDataArea)		= uiFontHeight;
		uiLines										= 1;

		// Loop for each word in display area.
		if(NULL != pcTextPointer)
        {
            while(*pcTextPointer != '\0')
            {
                uiCodeHighByte = 0x00;
                uiCodeLowByte = 0x00;
                // Judge change line symbol.
                if(*pcTextPointer == '\n')
                {
                    if(RECT_X_START(stCharacterDataArea) == 0)
                    {
                        // Ignore change lines in line start.
                    }
                    else
                    {
                        // Change lines.
                        RECT_X_START(stCharacterDataArea) = 0;
                        RECT_Y_START(stCharacterDataArea) += uiFontHeight;
                        uiLines ++;
                    }
                    pcTextPointer++;
                    continue;
                }
                // Process with ASCII code.
                if(((SGUI_BYTE)(*pcTextPointer) < 0x7F) && ((SGUI_BYTE)(*pcTextPointer) >= 0x20))
                {
                    uiCodeLowByte = (SGUI_BYTE)*pcTextPointer++;
                    RECT_WIDTH(stCharacterDataArea) = uiFontWidth;
                }
                // Process with GB2312.
                else if(((SGUI_BYTE)(*pcTextPointer) >= 0xA1) && ((SGUI_BYTE)(*pcTextPointer) <= 0xF7))
                {
                    uiCodeHighByte = (SGUI_BYTE)*pcTextPointer++;
                    uiCodeLowByte = (SGUI_BYTE)*pcTextPointer++;
                    RECT_WIDTH(stCharacterDataArea) = uiFontWidth << 1;
                }
                // Invalid character
                else
                {
                    pcTextPointer++;
                    RECT_WIDTH(stCharacterDataArea) = 0;
                    continue;
                }
                uiCharacterCode = uiCodeHighByte;
                uiCharacterCode = uiCharacterCode << 8;
                uiCharacterCode = uiCharacterCode | uiCodeLowByte;

                // Judge change line
                if(RECT_X_END(stCharacterDataArea) >= RECT_WIDTH(*pstDisplayArea))
                {
                    // Change lines.
                    RECT_X_START(stCharacterDataArea) = 0;
                    RECT_Y_START(stCharacterDataArea) += uiFontHeight;
                    uiLines ++;
                }
                // Draw characters.
                if((RECT_Y_END(stCharacterDataArea) >= 0) && (RECT_Y_START(stCharacterDataArea) < RECT_HEIGHT(*pstDisplayArea)))
                {
                    // Draw character.
                    iFontDataIndex = SGUI_Text_GetCharacterTableIndex(uiCharacterCode);
					adFontDataAddr = iFontDataIndex * uiCharacterDataSize;
					SGUI_Basic_DrawBitMap(pstIFObj, pstDisplayArea, &stCharacterDataArea, eFontResource, adFontDataAddr, eFontMode);

                }
                else
                {
                    // character is not in visible area, ignore.
                }
                RECT_X_START(stCharacterDataArea) += RECT_WIDTH(stCharacterDataArea);
            }
        }
	}
	return uiLines;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_GetCharacterTableIndex						**/
/** Purpose:		Get character index in font mode table.					**/
/** Params:																	**/
/**	@uiCharacterCode[in]: Data buffer pointer of read font data.			**/
/** Return:			Font mode data index in table.							**/
/** Limitation:		This function need to override when use external flash	**/
/**					ROM data, user must redefine the data offset by the		**/
/**					actual data.											**/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_GetCharacterTableIndex(SGUI_UINT16 uiCharacterCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_UINT16					uiCharacterCodeHighByte;
	SGUI_UINT16					uiCharacterCodeLowByte;
	SGUI_SIZE					uiFontTableIndex;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiCharacterCodeHighByte =	(uiCharacterCode >> 8) & 0x00FF;
	uiCharacterCodeLowByte =	uiCharacterCode & 0x00FF;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// ASCII code.
	if((0 == uiCharacterCodeHighByte) && (uiCharacterCodeLowByte < 128))
	{
		uiFontTableIndex = (uiCharacterCodeLowByte + FONT_LIB_OFFSET_ASCII);
	}
	// GB2312 punctuation
	else if((0xAA > uiCharacterCodeHighByte) && (0xA0 < uiCharacterCodeHighByte))
	{
		uiFontTableIndex = ((((uiCharacterCodeHighByte-0xA1)*94 + (uiCharacterCodeLowByte-0xA1))*2) + FONT_LIB_OFFSET_GB2312_SYMBOL);
	}
	// GB2312 level one character.
	else if((0xF8 > uiCharacterCodeHighByte) && (0xAF < uiCharacterCodeHighByte))
	{
		uiFontTableIndex = ((((uiCharacterCodeHighByte-0xB0)*94 + (uiCharacterCodeLowByte-0xA1))*2) + FONT_LIB_OFFSET_GB2312_CHARL1);
	}
	// Other to return full width space.
	else
	{
        uiFontTableIndex = FONT_LIB_OFFSET_GB2312_SYMBOL;	// Full-size space.
	}

	return uiFontTableIndex;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_GetTextGraphicsWidth							**/
/** Purpose:		Get text displayed full width.							**/
/** Params:																	**/
/**	@szText[in]: 		Text pointer.										**/
/**	@eFontSize[in]:		Font size, usually means font height.				**/
/** Return:			None.													**/
/** Notice:			Only used with Equal-width characters. 					**/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_GetTextGraphicsWidth(SGUI_CSZSTR szText, SGUI_FONT_SIZE eFontSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    SGUI_SIZE					uiTextHalfCharLength;
    SGUI_UINT16					uiHalfFontWidth;
    SGUI_SIZE					uiTextGraphicsWidth;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiTextHalfCharLength =		0;
	uiTextGraphicsWidth =		0;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != szText)
	{
		uiTextHalfCharLength = SGUI_SystemIF_StringLength(ENCODE(szText));
		uiHalfFontWidth = g_stFontSize[eFontSize].Width;
		uiTextGraphicsWidth = uiHalfFontWidth * uiTextHalfCharLength;
	}
	return uiTextGraphicsWidth;
}


/*****************************************************************************/
/** Function Name:	SGUI_Text_GetMultiLineTextLines							**/
/** Purpose:		Get a string's lines in a fixed width area.				**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@szNoticeText[in]:	Notice text resource.								**/
/**	@uiHalfWidthCharInLine[in]: Max number of half-width character in each	**/
/**						line.												**/
/** Return:			String lines.											**/
/** Notice:			None.													**/
/*****************************************************************************/
SGUI_SIZE SGUI_Text_GetMultiLineTextLines(SGUI_CSZSTR szNoticeText, SGUI_SIZE uiHalfWidthCharInLine)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiLineCount, uiLineByteCount;
	SGUI_CSZSTR					pcCur;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiLineByteCount =			0;
	uiLineCount =				1;
	pcCur =						ENCODE(szNoticeText);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcCur)
	{
		while('\0' != *pcCur)
		{
			if(*pcCur == '\n')
			{
                if(uiLineByteCount > 0)
				{
					// Change lines.
					uiLineCount ++;
					uiLineByteCount = 0;
				}
				else
				{
					// Ignore change lines in line start.
				}
				pcCur++;
				continue;
			}

			if((uint8_t)(*pcCur) < 0x7F)
			{
				if(uiLineByteCount<uiHalfWidthCharInLine)
				{
					uiLineByteCount++;
				}
				else
				{
					uiLineByteCount = 1;
					uiLineCount++;
				}
				pcCur++;
			}
			// Process with GB2312.
			else if(((uint8_t)(*pcCur) >= 0xA1) && ((uint8_t)(*pcCur) <= 0xF7))
			{
				//GB2312
				if((uiHalfWidthCharInLine-uiLineByteCount)>2)
				{
					uiLineByteCount+=2;
				}
				else
				{
					uiLineByteCount = 2;
					uiLineCount++;
				}
				pcCur+=2;
			}
			// Invalid character
			else
			{
				pcCur++;
			}
		}
	}
	return uiLineCount;
}

/*****************************************************************************/
/** Function Name:	SGUI_Text_GetFontResource								**/
/** Purpose:		Get character index in font mode table.					**/
/** Params:																	**/
/**	@ eFontSize[in]:	Get font resource ID by font size.					**/
/** Return:				Font data resource ID.								**/
/** Limitation:		This function will be used when user data is in differ-	**/
/**					end media, like flash on chip or external flash. user	**/
/**					can distinguish many different resources by ID, and		**/
/**					this function will read data form different media with	**/
/**					different parameter.									**/
/*****************************************************************************/
SGUI_FLASH_DATA_SOURCE SGUI_Text_GetFontResource(SGUI_FONT_SIZE eFontSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_FLASH_DATA_SOURCE		eResourceID;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(eFontSize)
	{
		case SGUI_FONT_SIZE_H6:
		{
			eResourceID = SGUI_FONT_SRC_H6;
			break;
		}
		case SGUI_FONT_SIZE_H8:
		{
			eResourceID = SGUI_FONT_SRC_H8;
			break;
		}
		case SGUI_FONT_SIZE_H12:
		{
			eResourceID = SGUI_FONT_SRC_H12;
			break;
		}
		case SGUI_FONT_SIZE_H16:
		{
			eResourceID = SGUI_FONT_SRC_H16;
			break;
		}
		default:
		{
			eResourceID = SGUI_FONT_SRC_UNKNOWN;
			break;
		}
	}

	return eResourceID;
}

