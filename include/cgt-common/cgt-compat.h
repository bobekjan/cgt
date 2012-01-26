/**
 * @file cgt-compat.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT_COMPAT_H__INCL__
#define __CGT_COMPAT_H__INCL__

/*************************************************************************/
/* Fixed-width integers                                                  */
/*************************************************************************/
/*
 * There's a shameless assumption here that if there is no inttypes.h,
 * we're compiling using MSVC ...
 */

/*
 * u?int(8|16|32|64)
 */
#ifdef HAVE_INTTYPES_H
typedef  int8_t   int8;
typedef uint8_t  uint8;
typedef  int16_t  int16;
typedef uint16_t uint16;
typedef  int32_t  int32;
typedef uint32_t uint32;
typedef  int64_t  int64;
typedef uint64_t uint64;
#else /* !HAVE_INTTYPES_H */
typedef   signed __int8   int8;
typedef unsigned __int8  uint8;
typedef   signed __int16  int16;
typedef unsigned __int16 uint16;
typedef   signed __int32  int32;
typedef unsigned __int32 uint32;
typedef   signed __int64  int64;
typedef unsigned __int64 uint64;
#endif /* !HAVE_INTTYPES_H */

/*
 * PRI[diouxX](8|16|32|64)
 * SCN[diouxX](8|16|32|64)
 */
#ifndef HAVE_INTTYPES_H
#   define PRId8 "hhd"
#   define PRIi8 "hhi"
#   define PRIo8 "hho"
#   define PRIu8 "hhu"
#   define PRIx8 "hhx"
#   define PRIX8 "hhX"

#   define PRId16 "hd"
#   define PRIi16 "hi"
#   define PRIo16 "ho"
#   define PRIu16 "hu"
#   define PRIx16 "hx"
#   define PRIX16 "hX"

#   define PRId32 "I32d"
#   define PRIi32 "I32i"
#   define PRIo32 "I32o"
#   define PRIu32 "I32u"
#   define PRIx32 "I32x"
#   define PRIX32 "I32X"

#   define PRId64 "I64d"
#   define PRIi64 "I64i"
#   define PRIo64 "I64o"
#   define PRIu64 "I64u"
#   define PRIx64 "I64x"
#   define PRIX64 "I64X"

#   define SCNd8 "hhd"
#   define SCNi8 "hhi"
#   define SCNo8 "hho"
#   define SCNu8 "hhu"
#   define SCNx8 "hhx"

#   define SCNd16 "hd"
#   define SCNi16 "hi"
#   define SCNo16 "ho"
#   define SCNu16 "hu"
#   define SCNx16 "hx"

#   define SCNd32 "I32d"
#   define SCNi32 "I32i"
#   define SCNo32 "I32o"
#   define SCNu32 "I32u"
#   define SCNx32 "I32x"

#   define SCNd64 "I64d"
#   define SCNi64 "I64i"
#   define SCNo64 "I64o"
#   define SCNu64 "I64u"
#   define SCNx64 "I64x"
#endif /* !HAVE_INTTYPES_H */

/*************************************************************************/
/* Text processing                                                       */
/*************************************************************************/
/**
 * @brief sprintf for std::string.
 *
 * @param[in] fmt Format string.
 * @param[in] ... Arguments.
 *
 * @return The resulting string.
 */
std::string ssprintf( const char* fmt, ... );
/**
 * @brief vsprintf for std::string.
 *
 * @param[in] fmt Format string.
 * @param[in] ap  Arguments.
 *
 * @return The resulting string.
 */
std::string vssprintf( const char* fmt, va_list ap );

/**
 * @brief sprintf for std::string.
 *
 * @param[out] str Where to store the result.
 * @param[in]  fmt Format string.
 * @param[in]  ... Arguments.
 */
void ssprintf( std::string& str, const char* fmt, ... );
/**
 * @brief vsprintf for std::string.
 *
 * @param[out] str Where to store the result.
 * @param[in]  fmt Format string.
 * @param[in]  ap  Arguments.
 */
void vssprintf( std::string& str, const char* fmt, va_list ap );

#endif /* !__CGT_COMPAT_H__INCL__ */
