///////////////////
// MathDefines.h //
///////////////////

// 2026-02-10 - Milo
// Filename changed from mathDefines.h -- to MathDefines.h

#pragma once

#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif defined(__GNU__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#else 
#define FORCE_INLINE inline
#endif
