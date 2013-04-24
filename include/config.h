#ifndef _CONFIG_H_
#define _CONFIG_H_

////
//// Ensure that POCO_DLL is default unless POCO_STATIC is defined
////
//#if defined(_WIN32) && defined(_WINDLL)
//	#if !defined(METAMACHINE_DLL) && !defined(METAMACHINE_STATIC)
//		#define METAMACHINE_DLL
//	#endif
//#endif
//
//#if (defined(_WIN32) || defined(_WIN32_WCE))
//	#if defined(MetaMachine_EXPORTS)
//		#define MetaMachine_API __declspec(dllexport)
//	#else
//		#define MetaMachine_API __declspec(dllimport)
//	#endif
//#endif
//
//
//#if !defined(MetaMachine_API)
//	#define MetaMachine_API
//#endif
//
////
//// Automatically link MetaMachine library.
////
//#if defined(_MSC_VER)
//	#if defined(_DEBUG)
//		#define LIB_SUFFIX "d.lib"
//	#else
//		#define LIB_SUFFIX ".lib"
//	#endif
//
//	#if !defined(MetaMachine_EXPORTS)
//		#pragma comment(lib, "MetaMachine" LIB_SUFFIX)
//	#endif
//#endif
//
#endif /* end of config.h */
