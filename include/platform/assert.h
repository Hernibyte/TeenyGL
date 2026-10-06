#pragma once

#include <iostream>
#include <cassert>
#include "platform/log.h"

#define CXX_STATIC_ASSERT(expr) \
    static_assert(expr, \
                "static assert failed: " \
                #expr)

#define CXX_ASSERT(expr) \
    assert(expr)

// CUSTOM ASSERT
//
// 1. Cross-platform compiler breakpoint trigger
#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #define DEBUG_BREAK() __builtin_trap()
#else
    #define DEBUG_BREAK() do { } while(0) 
#endif

// 2. Define the assertion macro based on build configuration
#ifdef TGL_ENABLE_ASSERTS
    // Debug Mode: Active assertion
    #define TGL_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "[APP] [ASSERTION FAILED]\n" \
                          << "  Condition: " << #condition << "\n" \
                          << "  Message:   " << message << "\n" \
                          << "  File:      " << __FILE__ << "\n" \
                          << "  Line:      " << __LINE__ << "\n"; \
                DEBUG_BREAK(); \
            } \
        } while (0)
#else
    // Release Mode: Completely removed by the preprocessor
    #define TGL_ASSERT(condition, message) do { (void)sizeof(condition); } while(0)
#endif

#ifdef TGL_ENABLE_ASSERTS
    // Debug Mode: Active assertion
    #define TGL_CORE_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "[CORE] [ASSERTION FAILED]\n" \
                          << "  Condition: " << #condition << "\n" \
                          << "  Message:   " << message << "\n" \
                          << "  File:      " << __FILE__ << "\n" \
                          << "  Line:      " << __LINE__ << "\n"; \
                DEBUG_BREAK(); \
            } \
        } while (0)
#else
    // Release Mode: Completely removed by the preprocessor
    #define TGL_CORE_ASSERT(condition, message) do { (void)sizeof(condition); } while(0)
#endif

#ifdef TGL_ENABLE_ASSERTS
    #define TGL_ASSERT_LOG(x, ...) { if(!(x)) { TGL_ERROR("Assertion failed: {0}", __VA_ARGS__); DEBUG_BREAK(); } }
    #define TGL_CORE_ASSERT_LOG(x, ...) { if(!(x)) { TGL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); DEBUG_BREAK(); } }
#else
    #define TGL_ASSERT_LOG(x, ...) do { } while(0)
    #define TGL_CORE_ASSERT_LOG(x, ...) do { } while(0)
#endif