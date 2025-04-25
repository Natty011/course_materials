#ifndef UTILS_HPP /* UTILS_HPP */
#define UTILS_HPP /* UTILS_HPP */


// Use this macro only for debug builds to mark deleted memory
#ifdef DEBUG
    #define DEBUG_ONLY(x) x
#else
    #define DEBUG_ONLY(x)
#endif

#define BAD_MEM_VALUE_32 0xDEADBEEF //invalid address in Vmemory
#define BAD_MEM_VALUE_64 0xDEADBEEFDEADBEEF

// BAD_MEM(T) is used to mark memory as "dead" after Dtor.
// to help catch use-after-free bugs (e.g. segmentation fault on access).

#if defined(PLATFORM_32)
    #define BAD_MEM(T) reinterpret_cast<T *>(BAD_MEM_VALUE_32)
#elif defined(PLATFORM_64)
    #define BAD_MEM(T) reinterpret_cast<T *>(BAD_MEM_VALUE_64)
#else
    #error "Define PLATFORM_32 or PLATFORM_64 in your build system"
#endif

#endif /* UTILS_HPP */
