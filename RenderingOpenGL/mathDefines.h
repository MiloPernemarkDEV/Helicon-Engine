#pragma once

#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif defined(__GNU__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#else 
#define FORCE_INLINE inline
#endif
