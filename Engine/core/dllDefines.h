//////////////////
// DllDefines.h //
//////////////////

// 2026-02-10 - Milo
// Filename changed from dllDefines.h -- to DllDefines.h


#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif