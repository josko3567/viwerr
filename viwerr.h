/*** LICENSE: LGPLV2. *************************************
 *                                                        *
 *                                                        *
 * viwerr.h is a "advanced" error catching library.       *
 * Copyright (C) 2022 josko3567                           *
 * <jkrianovic123@gmail.com>                              *
 *                                                        *
 * This library is free software; you can redistribute    *
 * it and/or modify it under the terms of the GNU Lesser  *
 * General Public License as published by the Free        *
 * Software Foundation; either version 2.1 of the         *
 * License, or (at your option) any later version.        *
 *                                                        *
 * This library is distributed in the hope that it will   *
 * be useful,                                             *
 * but WITHOUT ANY WARRANTY; without even the implied     *
 * warranty of MERCHANTABILITY or FITNESS FOR A           *
 * PARTICULAR PURPOSE. See the GNU Lesser General Public  *
 * License for more details.                              *
 *                                                        *
 * You should have received a copy of the GNU Lesser      *
 * General Public License along with this library; if     *
 * not, write to the Free Software Foundation, Inc.,      *
 * 51 Franklin Street, Fifth Floor, Boston,               *
 * MA  02110-1301  USA                                    *
 *                                                        *
 *                                                        *
 *********************************************************/

/*** INSCRIBING: FILE, AUTHOR & DATE INFORMATION. *********
 *                                                        *
 *                                                        *
 * FILE:                                                  *
 * Header for bubbling implementations to the surface     *
 * that the user is entrusted to use.                     *
 *                                                        *
 *                                                        *
 * AUTHOR:                                                *
 *      NAME:  josko3567 <github.com>                     *
 *      EMAIL: jkrianovic123@gmail.com                    *
 *                                                        *
 *                                                        *
 * DATE:                                                  *
 * 3.12.2022.                                             *
 *                                                        *
 *                                                        *
 *********************************************************/

/*** INTRODUCTION: ****************************************
 *                                                        *
 *                                                        *
 * viwerr.h is a library for catching multiple errors     *
 * with custom messages.                                  *
 *                                                        *
 *                                                        *
 * viwerr.h is a "successor" to my prior project sierr.h  *
 * but it's more like ctrl+c/ctrl+v with a few tweaks to  *
 * make it function as it does now.                       *
 *                                                        *
 *                                                        *
 * viwerr.h stores multiple errors & can filter through   *
 * these errors to get specific errors, so we can do      *
 * things only if a specific error occured & handle the   *
 * other errors with a general method.                    *
 *                                                        *
 *                                                        *
 * viwerr.h can be used in production but I mostly        *
 * use it for debugging projects.                         *
 *                                                        *
 *                                                        *
 *********************************************************/

/*** INSCRIBING: COMPATIBILITY. ***************************
 *                                                        *
 *                                                        *
 * C:                                                     *
 * This library is written in compliance to the limited   *
 * functionality at the disposal of the C99 standard.     *
 *                                                        *
 *                                                        *
 * POSIX:                                                 *
 * This libraries creator has yet to inscribe the minimum *
 * POSIX compatibilty version that this library requires. *
 * In its absance the user of the library is free to use  *
 * any compatibilty version of the POSIX standard that is *
 * deemed to work through trial and error.                *
 *                                                        *
 *                                                        *
 *********************************************************/

/*** INSCRIBING: USED NAMESPACE ***************************
 *                                                        *
 *                                                        *
 * The following words stated after "->" are used as the  *
 * first characters of every function, macro, definiton,  *
 * global variable, type, structure, enum & union.        *
 * If any item inside your code use the "namespace" used  *
 * by this library it is advised that you either:         *
 *   a) Give up on life.                                  *
 *   b) Change the name of your functions.                *
 *   c) Change the name of my functions.                  *
 *   d) Use a different library.                          *
 *   e) Check for collisons and appropriately change only *
 *      a select few item names that collide inside your  *
 *      or mine code.                                     *
 *                                                        *
 *                                                        *
 * -> _viwerr...                                          *
 * -> viwerr...                                           *
 * -> VIWERR...                                           *
 *                                                        *
 *                                                        *
 *********************************************************/

/*** INSCRIBING: DEVELOPMENT HISTORY/VERSIONS PUBLISHED ***
 *                                                        *
 *                                                        *
 * VIWERR:                                                *
 * Author  Release & Date  Description of modifications   *
 * ------  --------------  ----------------------------   *
 * josko3  V0.0            Inital creation.               *
 * 567     14.12.2022                                     *
 * ------  --------------  ----------------------------   *
 * josko3  V0.1b           _viwerr_list and all it's      *
 * 567     14.12.2022      contained functions created    *
 *                         Only VIWERR_PUSH & POP work    *
 * ------  --------------  ----------------------------   *
 * josko3  V1a             Added viwerr macro and added   *
 * 567                     new arguments VIWERR_PRINT     *
 *                         & VIWERR_OCCURED.              *
 *                                                        *
 * ------  --------------  ----------------------------   *
 * SIERR:                                                 *
 * Author  Release & Date  Description of modifications   *
 * ------  --------------  ----------------------------   *
 * josko3  V0.0            Inital creation.               *
 * 567     Date : ?                                       *
 * ------  --------------  ----------------------------   *
 * josko3  V1.0b           Mostly complete version.       *
 * 567     Date : ?                                       *
 * ------  --------------  ----------------------------   *
 * josko3  V1.0            Complete version.              *
 * 567     Date : ?                                       *
 * ------  --------------  ----------------------------   *
 * josko3  V1.1            Bug fixes.                     *
 * 567     Date : ?                                       *
 * ------  --------------  ----------------------------   *
 * josko3  V1.2            Added destructor function      *
 * 567     Date : ?                                       *
 * ------  --------------  ----------------------------   *
 * josko3  V1.2 fix1       Fixed viwerr exiting program   *
 * 567     Date : 27.2.23  upon first call to viwerr,     *
 *                         the _viwerr_init() function    *
 *                         exits if errno was set to      *
 *                         ENOMEM before hand.            *
 * ------  --------------  ----------------------------   *
 *                                                        *
 *********************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>


#ifndef VIWERR_INCLUDE
#define VIWERR_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#define VIWERR_SUBSCRIPTION_ERRNO

/**
 * @brief
 * https://stackoverflow.com/questions/4421681/how-to-
 * count-the-number-of-arguments-passed-to-a-function-
 * that-accepts-a-variabl
 *
 * This is the only thing i have no idea how to explain other
 * than black magic & it works.
 *
 * After using this argument counter ive come to realize that
 * it just counts the , symbols xD.
 */
#define VIWERR_VARCNT_NARG(...) \
        VIWERR_VARCNT_NARG_(__VA_ARGS__,VIWERR_VARCNT_PP_RSEQ_N())

#define VIWERR_VARCNT_NARG_(...) \
        VIWERR_VARCNT_128TH_ARG(__VA_ARGS__)

#define VIWERR_VARCNT_128TH_ARG(                           \
         _1,   _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
        _11,  _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21,  _22, _23, _24, _25, _26, _27, _28, _29, _30, \
        _31,  _32, _33, _34, _35, _36, _37, _38, _39, _40, \
        _41,  _42, _43, _44, _45, _46, _47, _48, _49, _50, \
        _51,  _52, _53, _54, _55, _56, _57, _58, _59, _60, \
        _61,  _62, _63, _64, _65, _66, _67, _68, _69, _70, \
        _71,  _72, _73, _74, _75, _76, _77, _78, _79, _80, \
        _81,  _82, _83, _84, _85, _86, _87, _88, _89, _90, \
        _91,  _92, _93, _94, _95, _96, _97, _98, _99,_100, \
        _101,_102,_103,_104,_105,_106,_107,_108,_109,_110, \
        _111,_112,_113,_114,_115,_116,_117,_118,_119,_120, \
        _121,_122,_123,_124,_125,_126,_127,N,...) N

#define VIWERR_VARCNT_PP_RSEQ_N()                \
        127,126,125,124,123,122,121,120,         \
        119,118,117,116,115,114,113,112,111,110, \
        109,108,107,106,105,104,103,102,101,100, \
         99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
         89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
         79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
         69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
         59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
         49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
         39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
         29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
         19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
          9,  8,  7,  6,  5,  4,  3,  2,  1,  0

/**
 * @brief
 * Exit code if constructor fails to allocate memory for
 * error packages.
 * We don't allocate memory when we place packages into the
 * list because viwerr could potentially throw ENOMEM if the
 * program ran out of memory prior to the call.
 *
 */
#define VIWERR_EXIT_CODE 78

/**
 * @brief
 * Depending on the function we use it in this constant
 * will do something different.
 *
 *      @tparam @c _viwerr_list(4,5)
 *      In this function VIWERR_PUSH indicated that we need to
 *      place the interlinked package into the array.
 *      (interlinked: passed together into the function).
 *
 *      @tparam @c viwerr(1,2)
 *      In this function VIWERR_PUSH and its interlinked package are both
 *      passed to _viwerr_list(4,5). (interlinked: passed together
 *      into the function).
 *
 *      @param @b _viwerr_list(VIWERR_PUSH,&(viwerr_package){...})
 *
 *      @param @b viwerr(VIWERR_PUSH,&(viwerr_package){...})
 *
 */
#define VIWERR_PUSH          1<<0

/**
 * @brief
 * For @b viwerr(1,2) only.
 * Acts exactly as VIWERR_POP but other than returning a package it also
 * prints it out to stderr.
 *
 */
#define VIWERR_PRINT         1<<2

/**
 * @brief
 * Depending on the function we use it in this constant
 * will do something different.
 *
 *      @tparam @c _viwerr_list(4,5)
 *      In this function VIWERR_POP returns a package, depending on
 *      if any other arguments were included the package returned may
 *      vary.
 *
 *      @tparam @c viwerr(1,2)
 *      Just a direct call to _viwerr_list(4,5) with the same parameters.
 *
 *      @param @b _viwerr_list(VIWERR_POP,NULL);
 *
 *      @param @b _viwerr_list(VIWERR_POP|VIWERR_BY...,&(viwerr_package){...});
 *
 *      @param @b viwerr(VIWERR_POP,NULL);
 *
 *      @param @b viwerr(VIWERR_POP|VIWERR_BY...,&(viwerr_package){...});
 *
 */
#define VIWERR_POP           1<<3

/**
 * @brief
 * For @b viwerr(1,2) only.
 * Acts exactly as VIWERR_POP but other than returning a package we
 * flush all packages that fit the criteria, that being all if no
 * argument from the VIWERR_BY... family is passed.
 */
#define VIWERR_FLUSH         1<<4

/**
 * @brief
 * For @b viwerr(1,2) only.
 * Acts exactly as VIWERR_POP but when returning the package it will
 * not update any static information about the package amount, newest
 * packages & the flag.returned value if viwerr were to return a package.
 */
#define VIWERR_OCCURED       1<<5

#define VIWERR_BY_CODE       1<<11
#define VIWERR_BY_NAME       1<<12
#define VIWERR_BY_MESSAGE    1<<13
#define VIWERR_BY_GROUP      1<<14

/**
 * @brief
 * Remove extra call in _viwerr_list() to viwerr_errno_redefine()
 * if we are calling from viwerr_errno_redefine()
 */
#define VIWERR_NO_ERRNO_TRIGGER 1<<15

/**
 * @brief
 * Change the flags of the package.
 * Used in combination with @c VIWERR_PUSH
 * in @c _viwerr_list(1,2).
 * Further details explained in @c VIWERR_PUSH.
 */

/**
 * @brief
 * Return only the adress of the package without
 * messing around with its flags.
 * Used in combination with @c VIWERR_POP
 * in @c _viwerr_list(1,2)
 * Further details explained in @c VIWERR_POP.
 */
#define VIWERR_ADRESS_ONLY   1<<16

/**
 * @brief
 * Amount of packages that are constructed when
 * the program is initalized.
 */
#define VIWERR_PACKAGE_AMOUNT (size_t)128

/**
 * \ingroup String_Sizes
 * @brief
 * Maximu size for name, message and
 * group string. Any string passed through
 * viwerr(VIWERR_PUSH, ...) will fully copy the
 * contents of the strings, not the pointers.
 * @{
 */
#define VIWERR_NAME_SIZE     (size_t)64
#define VIWERR_MESSAGE_SIZE  (size_t)256
#define VIWERR_GROUP_SIZE    (size_t)64
#define VIWERR_FILENAME_SIZE (size_t)256
#define VIWERR_FUNCTION_SIZE (size_t)256
/**
 * @}
 */


/**
 * @struct  @c viwerr_package_st
 * @typedef @c viwerr_package
 *
 *      @brief Package that will contain our custom errors
 *      for safe keeping until we print them or return them
 *      via. viwerr(...).
 *
 *      @tparam @b code
 *      Error code that was passed.
 *
 *      @tparam @b name
 *      Pointer to a string that contains our error name.
 *
 *      @tparam @b message
 *      Pointer to a string that contains our error description.
 *
 *      @tparam @b group
 *      Pointer to a string that indicates to what group this
 *      error belongs to, I usualy just place the function
 *      name inside.
 *
 *      @tparam @b file
 *      Pointer to the value of the macro __FILE__.
 *
 *      @tparam @b line
 *      Value returned by the macro __LINE__.
 *
 *      @tparam @a flag.
 *      Flags...
 *
 *              @tparam @b flag.returned
 *              Flag that indicates if the error inside the package
 *              was ever returned by viwerr(...). Set to 1
 *              upon creation, if the package gets returned by
 *              viwerr(...) or removal of the error from the package,
 *              set to 0 when a new error is placed inside.
 *
 *              @tparam @b flag.printed
 *              Flag that indicates if the error isnide the package
 *              was ever printed by viwerr(...). Set to 1 upon
 *              creation or printing/removal, set to 0 when a new
 *              error is placed inside the package.
 *
 *              @tparam @b flag.contains
 *              Indicates if the package contains a valid error value.
 *              Set to 0 upon creation or removal an error from
 *              the package, set to 1 when placing a error inside
 *              the package.
 *
 */
typedef struct viwerr_package_st {

        int   code;
        char *name;
        char *message;
        char *group;

        /**
         * @brief
         * Obtained when calling viwerr secretly :p.
         */
        char *file;
        char *func;
        int   line;

        struct {

                int returned;
                int printed;
                int contains;

        } flag;

} viwerr_package;

/**
 * @brief
 * Amount of memory the viwerr_package array uses.
 * The viwerr array is used due to the fact that
 * the viwerr function should not be able to return any
 * errors other than syntax errors. If the computer runs
 * out of memory and we try to report it by creating
 * a new package it's not gonna go well so we have to
 * use a package from a predefined list of packages.
 */
#define VIWERR_MEMORY_USED                                            \
        (VIWERR_NAME_SIZE + VIWERR_MESSAGE_SIZE + VIWERR_GROUP_SIZE + \
        sizeof(viwerr_package)) * VIWERR_PACKAGE_AMOUNT

/**
 * @brief
 * Predefined values for a empty viwerr_package.
 */
#define viwerr_package_empty (viwerr_package){ \
        .code    = INT_MIN,                    \
        .name    = NULL,                       \
        .message = NULL,                       \
        .group   = NULL,                       \
        .file    = NULL,                       \
        .func    = NULL,                       \
        .line    = INT_MIN,                    \
        .flag.returned = 1,                    \
        .flag.printed  = 1,                    \
        .flag.contains = 0                     \
}

/**
 * @brief
 * Predefined values for a viwerr_package that was
 * just created and was not returned via VIWERR_POP.
 */
#define viwerr_package_new (viwerr_package){ \
        .code    = 0,                        \
        .name    = NULL,                     \
        .message = NULL,                     \
        .group   = NULL,                     \
        .file    = NULL,                     \
        .func    = NULL,                     \
        .line    = 0,                        \
        .flag.returned = 0,                  \
        .flag.printed  = 0,                  \
        .flag.contains = 1                   \
}

/**
 * @brief
 * Predefined values for a viwerr_package that was
 * gotten via VIWERR_POP & had its flag.returned
 * & flag.printed values set to 1.
 */
#define viwerr_package_used (viwerr_package){ \
        .code    = 0,                         \
        .name    = NULL,                      \
        .message = NULL,                      \
        .group   = NULL,                      \
        .file    = NULL,                      \
        .func    = NULL,                      \
        .line    = 0,                         \
        .flag.returned = 1,                   \
        .flag.printed  = 1,                   \
        .flag.contains = 1                    \
}

/**
 * @fn @c _viwerr_list_init(0)
 *
 *      @brief Initalize a viwerr_package array with
 *      default values & return it.
 *
 *
 *      @throw @b ENOMEM - Exits program forcefully if upon startup
 *                      all memory spaces have already been
 *                      occupied.
 *
 *
 *      @return Initalized viwerr_package* array.
 *
 */
#ifdef __GNUC__
__attribute__((constructor))
#endif
viwerr_package**
_viwerr_list_init(
        void
);


#ifdef __GNUC__
__attribute__((destructor))
#endif
void
_viwerr_list_free(
    void
);

/**
 * @fn @c _viwerr_popcnt(1)
 *
 *      @brief Simple bit counter.
 *
 *
 *      @param @b arg
 *                Integer value we count bits from.
 *
 *
 *      @returns Count of bits inside @b arg that are
 *      set to 1.
 *
 */
long _viwerr_popcnt(
        long arg
);

/**
 * @fn @c _viwerr_filter_by(3)
 *
 *      @brief
 *      Filter a package by the filters arguments
 *      VIWERR_BY...
 *
 *
 *      @param @b arg
 *                Arguments that contains one of the
 *                arguments from the VIWERR_BY... family.
 *
 *      @param @b package
 *                Package we will compare/filter with our
 *                filter package.
 *
 *      @param @b filter
 *                Error package from which we take certaint parts
 *                from to use as a filter.
 *
 *
 *      @throw Nothing.
 *
 *
 *      @return Integer boolean value of 0 or 1 that will
 *      tell us if the package passed throught the filter.
 *
 *
 */
bool
_viwerr_filter_by(
        int arg,
        const char * file,
        int line,
        viwerr_package * package,
        viwerr_package * filter
);


/**
 * @fn @c _viwerr_clear_package(1)
 *
 *      @brief Set package variables to that of @b viwerr_package_empty.
 *
 *
 *      @param @b package
 *                Package to reset.
 *
 *
 *      @throw Nothing.
 *
 *
 *      @returns Nothing.
 *
 */
void _viwerr_clear_package(
        viwerr_package * package
);

/**
 * @brief Prints the contents of a viwerr_package.
 */
void
_viwerr_print_package(
        viwerr_package * package
);

/**
 * @fn @c _viwerr_list(4,5)
 *
 *      @brief
 *      Sort of interface function through which we interact
 *      with the error package array.
 *
 *      @param @b arg
 *                Arguments passed through that will indicate
 *                what we want to do to the list.
 *                Possible arguments are:
 *                      Only one of the following arguments are allowed
 *                      per call.
 *                VIWERR_EDIT, VIWERR_FLUSH, VIWERR_POP & VIWERR_PUSH.
 *                      The rest only matter if the prior arguments say
 *                      that they do.
 *
 *
 */
viwerr_package*
_viwerr_list(
        int          arg,
        char*       func,
        const char *file,
        int         line,
        int          cnt,
        ...
);

/**
 * @def @a viwerr_list(2)
 *
 *      @brief _viwerr_list(4,5) with argument 'cnt' counted by
 *      @a VIWERR_VARCNT_NARG(1). Also automatically inserts the
 *      __FILE__ and __LINE__ into file and line arguments.
 *
 */
#define viwerr(arg, ...)                         \
        _viwerr_list(                            \
                arg/*|(errno<<64)*/,             \
                (char*)__func__,                 \
                __FILE__,                        \
                __LINE__,                        \
                VIWERR_VARCNT_NARG(__VA_ARGS__), \
                __VA_ARGS__)

/**
 * @def @a viwerr_file(4)
 *
 *      @brief viwerr_file(4) is viwerr(2) with file and line
 *      being insertable.
 *
 */
#define viwerr_file(arg, func, file, line, ...)  \
        _viwerr_list(                            \
                arg,                             \
                (char*)func,                     \
                file,                            \
                line,                            \
                VIWERR_VARCNT_NARG(__VA_ARGS__), \
                __VA_ARGS__)

#define VIWERR_ERRNO_FLUSH

#define viwerr_occured_in_group(gr) \
        (viwerr(VIWERR_OCCURED, &(viwerr_package){.group=(char*)gr}) ? true : false)

/**
 * @fn @c viwerr_errno_redefine(2)
 *
 *      @brief This function allows viwerr to be updated
 *      on the state of errno every time errno is called.
 *      Due to the C preprocessor reading files line by line,
 *      the errno calls inside this function are of the orginal
 *      errno from <errno.h>. Afterwards errno is redefined
 *      to call this function instead of whatever was
 *      inside of errno before. Due to this function returning the
 *      original errno macro, we can use the normal errno
 *      syntax to read and write values to errno.
 *      viwerr is kind of late to the party when it comes to
 *      reading values from errno because we can't make a macro
 *      that keeps the original syntax and also calls a function
 *      after the errno value was called for
 *      reading or writing. Because of that
 *      viwerr is one read behind errno, which means if errno
 *      is changed viwerr won't be notified until errno is called
 *      again. This can be easily mitigated by calling this
 *      function inside of viwerr but the problem lies not in
 *      the latency but in the fact that we cannot determine
 *      on any call to errno wether the value was written to or
 *      read from. Because of that if we have multiple functions
 *      setting errno to the same value we will only store the
 *      errno value from the first function that set it to that
 *      particular value.
 *
 *      @returns &(errno) <- errno before it was redefined.
 *
 */
int * viwerr_errno_redefine(
        char*        func,
        const char * file,
        int line
);

/**
 * @brief
 * If viwerr(VIWERR_PUSH, ...) pushed a errno value
 * viwerr_errno_redefine will ignore the new value as
 * it is already written.
 */
bool viwerr_errno_ignore_new(bool set);

/* SPDX-License-Identifier: 0BSD */
/* Copyright 2019 Alexander Kozhevnikov <mentalisttraceur@gmail.com> */
char const * errnoname(int errno_);

#ifndef REMOVE_ERRNO_REDEFINE
#if defined(VIWERR_SUBSCRIPTION_ERRNO) && !defined(VIWERR_REMOVE_FOR_OBJ_COMP)
        #undef errno
        #define errno (*viwerr_errno_redefine((char*)___func__,__FILE__,__LINE__))
#endif /** @c VIWERR_SUBSCRIPTION_ERRNO */
#endif

#ifdef __cplusplus
}
#endif

#endif /** @c VIWERR_INCLUDE */
