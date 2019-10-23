#ifndef _INCLUDE_SIMPLE_GUI_CONFIG_H_
#define _INCLUDE_SIMPLE_GUI_CONFIG_H_

//=======================================================================//
//= Used for SimpleGUI virtual SDK.									    =//
//=======================================================================//
//#define _SIMPLE_GUI_ENCODE_TEXT_
#ifdef _SIMPLE_GUI_ENCODE_TEXT_
 #define _SIMPLE_GUI_ENCODE_TEXT_SRC_		("UTF-8")
 #define _SIMPLE_GUI_ENCODE_TEXT_DEST_		("GB2312")
#endif // _SIMPLE_GUI_ENCODE_TEXT_
//#define _SIMPLE_GUI_IN_VIRTUAL_SDK_

//=======================================================================//
//= Used for SimpleGUI interface.									    =//
//=======================================================================//
//#define _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
#define _SIMPLE_GUI_ENABLE_BASIC_FONT_

//=======================================================================//
//= Used for SimpleGUI demo process.								    =//
//=======================================================================//
#define _SIMPLE_GUI_NON_ASCII_

#endif // _INCLUDE_SIMPLE_GUI_CONFIG_H_
