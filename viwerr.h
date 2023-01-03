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
 * viwerr.h can be used in production but it's I mostly   *
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
 * josko3  V1a             Added viwerr macro and added
 * 567                     new arguments VIWERR_PRINT
 *                         & VIWERR_OCCURED.
 *                                *
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
 *                                                        *
 *                                                        *
 *********************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>

#define VIWERR_SUBSCRIPTION_ERRNO
// #undef VIWERR_SUBSCRIPTION_ERRNO

#ifndef VIWERR_INCLUDE
#define VIWERR_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

int * viwerr_errno_redefine(
        const char * file, 
        int line 
);

char const * errnoname(
        int errno_
);

/**
 * @brief 
 * https://stackoverflow.com/questions/4421681/how-to-
 * count-the-number-of-arguments-passed-to-a-function-
 * that-accepts-a-variabl
 * 
 * This is the only thing i have no idea how to explain other
 * than black magic & it works.
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
 * packages & the flag.returned value if we were to return a package.
 */
#define VIWERR_OCCURED       1<<5

#define VIWERR_BY_CODE       1<<11
#define VIWERR_BY_NAME       1<<12
#define VIWERR_BY_MESSAGE    1<<13
#define VIWERR_BY_GROUP      1<<14

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
#define VIWERR_PACKAGE_AMOUNT (size_t)20

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
viwerr_package**
_viwerr_list_init(
        void )
{


        static viwerr_package **array = NULL;
        /*viwerr_package *empty_package = viwerr_package_empty;*/
        
        if( array == NULL ) {

                array = (viwerr_package**)malloc(
                        sizeof(viwerr_package) * VIWERR_PACKAGE_AMOUNT
                );

                /**
                 * @brief 
                 * Exit with code VIWERR_EXIT_CODE if we failed
                 * to allocate memory for our error packages.
                 */
                if( array == NULL || errno == ENOMEM ) {
                        exit(VIWERR_EXIT_CODE);
                }

                int i;
                for( i = 0; i < (int)VIWERR_PACKAGE_AMOUNT; i++ ) {

                        array[i] = (viwerr_package*)malloc(
                                sizeof(viwerr_package)
                        );
                        
                        if( array[i] == NULL ) {
                                exit(VIWERR_EXIT_CODE);
                        }                     
                        
                        memcpy(
                                array[i],
                                &(viwerr_package){
                                .code = viwerr_package_empty.code,
                                .name = calloc(
                                        VIWERR_NAME_SIZE, 
                                        sizeof(char)),
                                .message = calloc(
                                        VIWERR_MESSAGE_SIZE,
                                        sizeof(char)),
                                .group = calloc(
                                        VIWERR_GROUP_SIZE,
                                        sizeof(char)),
                                .file = calloc(
                                        VIWERR_FILENAME_SIZE,
                                        sizeof(char)),
                                .line = viwerr_package_empty.line,
                                .flag.returned = 
                                        viwerr_package_empty.flag.returned,
                                .flag.printed  = 
                                        viwerr_package_empty.flag.printed,
                                .flag.contains = 
                                        viwerr_package_empty.flag.contains,
                                }, 
                                sizeof(viwerr_package)
                        );      

                        if( errno == ENOMEM ){
                                exit(VIWERR_EXIT_CODE);
                        }

                }

        }

        return array;

}

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
        long arg )
{

        int i, count;
        for(i = count = 0; i < (int)sizeof(long)*8; i++)
                if( (arg & (long)1<<i) != 0 )
                        count++;

        return count;

}

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
        viwerr_package * filter )
{

        if( package == NULL
        ||  filter  == NULL ) {

                fprintf(stderr,
                " VIWERR-INTERLNAL-CALL:\n"
                "_viwerr_filter_by: expected parameters"
                " \"package\" and \"filter\" to be 2 non"
                " non NULL pointer viwerr_package*'s." 
                " File: %s\n" 
                " Line: %d\n"
                "viwerr file fprintf called at:\n"
                " %d : %s\n",
                file, line,__LINE__,__FILE__
                );   

        }

        /**
         * @brief 
         * Start the evaluation, if any of these conditionals
         * with ternary operators proves false then we return 0, 
         * otherwise we return 1;
         */

        bool evaluation = true;

        if( arg & VIWERR_BY_CODE ) {

                evaluation = package->code != filter->code 
                        ? false : true;
                if( evaluation == 0 ) return evaluation;

        }

        if( arg & VIWERR_BY_NAME ) {

                evaluation = strncmp(
                        package->name, 
                        filter->name,
                        VIWERR_NAME_SIZE
                ) != 0 ? false : true;
                if( evaluation == 0 ) return evaluation;

        }

        if( arg & VIWERR_BY_MESSAGE ) {

                evaluation = strncmp(
                        package->message, 
                        filter->message,
                        VIWERR_MESSAGE_SIZE
                ) != 0 ? false : true;
                if( evaluation == 0 ) return evaluation;

        }

        if( arg & VIWERR_BY_GROUP ) {

                evaluation = strncmp(
                        package->group, 
                        filter->group,
                        VIWERR_GROUP_SIZE
                ) != 0 ? false : true;
                if( evaluation == 0 ) return evaluation;

        }

        return evaluation;

}


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
        viwerr_package * package )
{
        

        if( package != NULL ){

                package->code = viwerr_package_empty.code;

                package->line = viwerr_package_empty.line;

                snprintf(package->name, VIWERR_NAME_SIZE, 
                        "%s",
                        viwerr_package_empty.name == NULL ? 
                                "" : viwerr_package_empty.name
                );
                  
                snprintf(package->message, VIWERR_MESSAGE_SIZE, 
                        "%s",
                        viwerr_package_empty.message == NULL ? 
                                "" : viwerr_package_empty.message
                );

                snprintf(package->group, VIWERR_GROUP_SIZE,
                        "%s",
                        viwerr_package_empty.group == NULL ? 
                                "" : viwerr_package_empty.group
                );

                snprintf(package->file, VIWERR_FILENAME_SIZE, 
                        "%s",
                        viwerr_package_empty.file == NULL ? 
                                "" : viwerr_package_empty.file
                );

                package->flag.returned = 
                        viwerr_package_empty.flag.returned;
                package->flag.printed  = 
                        viwerr_package_empty.flag.printed;
                package->flag.contains = 
                        viwerr_package_empty.flag.contains;

        }

}

void
_viwerr_print_package(
        viwerr_package * package)
{

        fprintf(stderr, "_____________________________________\n");
        fprintf(stderr, "  VIWERR CAUGHT AN EXCEPTION: \n");
        if( package->code == viwerr_package_empty.code )
                fprintf(stderr, " \tcode     : %d \t[default]\n", 
                        package->code);
        else
                fprintf(stderr, " \tcode     : %d\n", 
                        package->code);              
        fprintf(stderr, " \tname     : %s\n", package->name);
        fprintf(stderr, " \tmessage  : %s\n", package->message);
        fprintf(stderr, " \tgroup    : %s\n", package->group);
        fprintf(stderr, " \tfile     : %s\n", package->file);
        fprintf(stderr, " \tline     : %d\n", package->line);
        fprintf(stderr, "_____________________________________\n\n");

}

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
        const char *file,
        int         line,
        int          cnt,
        ... ) 
{

        viwerr_package **packages = _viwerr_list_init();

        static struct {

                int newest;
                int amount;

        } packageinfo = {

                .newest = 0,
                .amount = 0

        };

        /**
         * @brief 
         * Evaluate argument by counting the arguments
         * that cannot coexist. If 0 then there is nothing to do.
         * If 1 then everything is aokay. If 2 or more then 
         * we have to many arguments.
         */
        int evalarg = _viwerr_popcnt(
                arg & (VIWERR_FLUSH
                      |VIWERR_POP
                      |VIWERR_PUSH
                      |VIWERR_PRINT
                      |VIWERR_OCCURED)
        );

        if(evalarg != 1) {

                if( evalarg <= 0 ){

                        fprintf(stderr,
                                " VIWERR-INTERLNAL-CALL:\n"
                                "viwerr_list: requires 1 of the following"
                                " arguments:\n"
                                "\tVIWERR_PUSH, \n"
                                "\tVIWERR_POP,  \n"
                                "\tVIWERR_FLUSH \n"
                                " File: %s\n" 
                                " Line: %d\n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                        );

                } else if( evalarg >= 2 ){

                        fprintf(stderr,
                                " VIWERR-INTERLNAL-CALL:\n"
                                "viwerr_list: viwerr only accepts the" 
                                "following arguments one at time:\n"
                                "\tVIWERR_PUSH, \n"
                                "\tVIWERR_POP,  \n"
                                "\tVIWERR_FLUSH \n"
                                " File: %s\n" 
                                " Line: %d\n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                        );

                }

                return NULL;

        }

#ifdef VIWERR_DEBUG_MODE
        fprintf(strderr,
                "viwerr-debug: number of arguments passed to "
               "viwerr_list = %d\n", cnt);
        fprintf(stderr,
                "viwerr-debug: static values:\n"
                "\t packageinfo.newest = %d\n"
                "\t packageinfo.amount = %d\n",
                packageinfo.newest, packageinfo.amount);
#endif

        if( arg & VIWERR_PUSH ) {

                /**
                 * @brief 
                 * Load 2 packages from va_list.
                 * Overwrite flags from the first package
                 * with flags from the second package only
                 * if they are actual valid flags (0 or 1).
                 * If they are not valid flags we keep whatever 
                 * the first package already had it set to prior
                 * to the function call.
                 */
                if( cnt < 1 ) {

                        fprintf(stderr, 
                                "viwerr: VIWERR_PUSH"
                                " requires 1 argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains any sort of values"
                                " that are non negative (even for"
                                " pointers).\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                        );
                        return NULL;

                }

                va_list list;

                va_start(list, cnt);
                viwerr_package *package = (viwerr_package*)va_arg(
                        list, viwerr_package*
                );
                va_end(list);

                if( package == NULL ) {

                        fprintf(stderr, 
                                "viwerr: VIWERR_PUSH"
                                " requires 1 NON NULL argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains any sort of values"
                                " that are non negative (even for"
                                " pointers).\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " line %d -> %s\n",
                                file, line, __LINE__, __FILE__
                        );
                        return NULL;

                }

                int index = (packageinfo.newest + 1) 
                            % VIWERR_PACKAGE_AMOUNT;
                
                /**
                 * @brief 
                 * Copy into the package at index fully.
                 * If varadict package contains NULL pointers
                 * we write a empty string to the corresponding
                 * variable.
                 * If varadict package contains negative integers
                 * we clamp their values to 0.
                 */
                packages[index]->code = 
                        package->code != viwerr_package_new.code ?
                                package->code : viwerr_package_new.code;

                packages[index]->line = 
                        line != viwerr_package_new.line ? 
                                line : viwerr_package_new.line;

                snprintf(packages[index]->name,
                        VIWERR_NAME_SIZE, "%s",
                        package->name != NULL ? 
                                package->name : 
                                viwerr_package_new.name
                );
                        
                snprintf(packages[index]->message,
                        VIWERR_MESSAGE_SIZE, "%s",
                        package->message != NULL ?
                                package->message :
                                viwerr_package_new.message
                );

                snprintf(packages[index]->group,
                        VIWERR_GROUP_SIZE, "%s",
                        package->group != NULL ?
                                package->group :
                                viwerr_package_new.group
                );

                snprintf(packages[index]->file,
                        VIWERR_FILENAME_SIZE, "%s",
                        file != NULL ?
                                file :
                                viwerr_package_new.file
                );

                packages[index]->flag.returned = 
                        viwerr_package_new.flag.returned;
                packages[index]->flag.printed  = 
                        viwerr_package_new.flag.printed;
                packages[index]->flag.contains = 
                        viwerr_package_new.flag.contains;

                packageinfo.newest = index;
                packageinfo.amount += 
                        (size_t)packageinfo.amount >= VIWERR_PACKAGE_AMOUNT ?
                                0 : 1;

                return package;

        } else if( arg & VIWERR_POP  
               ||  arg & VIWERR_PRINT 
               ||  arg & VIWERR_OCCURED ) {
                
#ifdef VIWERR_SUBSCRIPTION_ERRNO
                if((*viwerr_errno_redefine(file,line)) == 0){};
#endif

                /**
                 * @brief 
                 * We do one full loop and attempt to find
                 * the newest unpoped package.
                 */
                viwerr_package * newest_package = NULL;
                int index = packageinfo.newest;

                /**
                 * @brief 
                 * Filter if we combined VIWERR_POP with
                 * one of the arguments from the VIWERR_BY family.
                 */
                viwerr_package * filter = NULL;

                /**
                 * @brief
                 * If we contiant one of the following arguments
                 * we must check if we have a package passed
                 * through VA_ARG. 
                 */
                if( _viwerr_popcnt((long)(arg & 
                        (VIWERR_BY_CODE|
                         VIWERR_BY_NAME|
                         VIWERR_BY_MESSAGE|
                         VIWERR_BY_GROUP)      
                ))) {

                        if( cnt < 1 ) {

                                fprintf(stderr, 
                                "viwerr: VIWERR_POP with a"
                                " argument from the"
                                " VIWERR_BY... family"
                                " requires 1 argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains the values we will filter"
                                " our packages with!\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                                );
                                return NULL;

                        }

                        va_list list;
                        va_start(list, cnt);
                        filter = (viwerr_package*)va_arg(
                                list, viwerr_package*
                        );
                        va_end(list);

                        if( filter == NULL ) {

                                fprintf(stderr, 
                                "viwerr: VIWERR_POP with a"
                                " argument from the"
                                " VIWERR_BY... family"
                                " requires 1 NON NULL argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains the values we will filter"
                                " our packages with!\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                                );
                                return NULL;

                        }

                }

                /**
                 * @brief 
                 * We call errno here to see what it contains.
                 */
                #ifdef VIWERR_SUBSCRIPTION_ERRNO

                #endif

                /**
                 * @brief 
                 * Loop through the entire list of packages
                 * until we find one that fits the criteria.
                 */
                do {

                        viwerr_package * package = packages[index];

                        /**
                         * @brief 
                         * Check if package is empty and has not been
                         * returned!
                         */
                        if( package->flag.contains 
                                == viwerr_package_new.flag.contains
                        &&  package->flag.returned
                                == viwerr_package_new.flag.returned ) {

                                /**
                                 * @brief 
                                 * Evaluate if package fits criteria
                                 * if we have a VIWERR_BY... argument
                                 * with _viwerr_filter_by(...).
                                 */
                                bool eval = true;
                                if( filter != NULL ) {

                                        eval = _viwerr_filter_by(
                                                arg, file, line,
                                                package, filter
                                        );

                                }

                                if( eval == true ) {

                                        newest_package = package;
                                        break;

                                }
                                
                        }
                        
                        index = (index - 1) 
                                % VIWERR_PACKAGE_AMOUNT;



                } while (index != packageinfo.newest);

                /**
                 * @brief
                 * Exit if no package was found.
                 */
                if( newest_package == NULL ) {
      
                        return NULL;

                };

                /**
                 * @brief
                 * If VIWERR_OCCURED is the argument we leave
                 * everything as is and return the package.
                 */
                if( arg & VIWERR_OCCURED ) {
                
                        return newest_package;

                }

                /**
                 * @brief
                 * If argument is VIWERR_PRINT we call
                 * _viwerr_print_package(1) before we return
                 * the package.
                 */
                if( arg & VIWERR_PRINT ){

                        _viwerr_print_package(newest_package);
                        newest_package->flag.printed =
                                viwerr_package_used.flag.printed;

                }
                /**
                 * @brief 
                 * Update static information and send package.
                 * VIWERR_PRINT & VIWERR_POP
                 */
                newest_package->flag.returned = 
                        viwerr_package_used.flag.returned;
                packageinfo.amount -=   
                        packageinfo.amount <= 0 ? 0 : 1;
                packageinfo.newest = packageinfo.amount <= 0 ?
                        0 : (index - 1) % VIWERR_PACKAGE_AMOUNT;
                
                return newest_package;
                

        } else if( arg & VIWERR_FLUSH ) {

                /**
                 * @brief 
                 * Amount of packages that were cleared.
                 */
                int cleared = 0;
                int index = packageinfo.newest;

                /**
                 * @brief 
                 * Filter if we combined VIWERR_FLUSH with
                 * one of the arguments from the VIWERR_BY family.
                 */
                viwerr_package * filter = NULL;
                /**
                 * @brief
                 * If we contiant one of the following arguments
                 * we must check if we have a package passed
                 * through VA_ARG. 
                 */
                if( _viwerr_popcnt((long)(arg & 
                        (VIWERR_BY_CODE|
                         VIWERR_BY_NAME|
                         VIWERR_BY_MESSAGE|
                         VIWERR_BY_GROUP)      
                ))) {

                        if( cnt < 1 ) {

                                fprintf(stderr, 
                                "viwerr: VIWERR_FLUSH with a"
                                " argument from the"
                                " VIWERR_BY... family"
                                " requires 1 argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains the values we will filter"
                                " our packages with!\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                                );
                                return NULL;

                        }

                        va_list list;
                        va_start(list, cnt);
                        filter = (viwerr_package*)va_arg(
                                list, viwerr_package*
                        );
                        va_end(list);

                        if( filter == NULL ) {

                                fprintf(stderr, 
                                "viwerr: VIWERR_FLUSH with a argument"
                                " from the VIWERR_BY... family"
                                " requires 1 NON NULL argument:\n"
                                "        "
                                "A viwerr_package pointer that"
                                " contains the values we will filter"
                                " our packages with!\n"
                                " File: %s \n"
                                " Line: %d \n"
                                "viwerr file fprintf called at:\n"
                                " %d : %s\n",
                                file, line,__LINE__,__FILE__
                                );
                                return NULL;

                        }

                }

                /**
                 * @brief 
                 * Loop through the entire list of packages
                 * until we find one that fits the criteria.
                 */
                do {

                        viwerr_package * package = packages[index];

                        if( package->flag.contains 
                                == viwerr_package_new.flag.contains ){
                                
                                /**
                                 * @brief 
                                 * Evaluate if package fits criteria
                                 * if we have a VIWERR_BY... argument
                                 * with _viwerr_filter_by(...).
                                 */

                                bool eval = true;
                                if( filter != NULL ) {

                                        eval = _viwerr_filter_by(
                                                arg, file, line,
                                                package, filter
                                        );
                                        
                                }

                                if( eval == true ) {

                                        _viwerr_clear_package(package);
                                        cleared++;

                                }

                        }

                        index = (index - 1) 
                                % VIWERR_PACKAGE_AMOUNT;

                } while (index != packageinfo.newest);

                /**
                 * @brief 
                 * Update static information and send package.
                 */
                packageinfo.amount -= cleared;
                return NULL;

        }

        return NULL;

}

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
                arg/*|(errno<<64)*/,                 \
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
#define viwerr_file(arg, file, line, ...)        \
        _viwerr_list(                            \
                arg,                             \
                file,                            \
                line,                            \
                VIWERR_VARCNT_NARG(__VA_ARGS__), \
                __VA_ARGS__)

#define VIWERR_ERRNO_FLUSH

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
        const char * file, 
        int line )
{

        static struct {

                int code;
                char * file;
                int line;

        } previous = {
                .code = 0,
                .file = (char*)"",
                .line = 0
        };

        /**
         * @brief @b IMPORTANT
         * The reason this works is because we call errno
         * before we redefine it. This means that every call of
         * errno is the errno defined by <errno.h>. Afterwards
         * when we redefine errno every call of errno that is:
         * 1. Not from a function defined in a static or dynamic
         * library,
         * 2. In a file or function included/defined after we 
         * include <viwerr.h>;
         * will use the new version that notifies viwerr to any
         * errors that may have occured every time it is called
         * either for reading or writing. 
         */
        if(errno == 0
        || errno == previous.code) {
                
                previous.code = errno;
                previous.file = (char*)file;
                previous.line = line;
                return &errno;
        
        }

        viwerr_file(VIWERR_PUSH, 
        (char*)previous.file, previous.line, &(viwerr_package){
                .code = errno,
                .name = (char*)errnoname(errno),
                .message = strerror(errno),
                .group = (char*)"errno"
        });
        
        previous.code = errno;
        previous.file = (char*)file;
        previous.line = line;
        return &errno;

}


#ifdef VIWERR_SUBSCRIPTION_ERRNO
        #undef errno
        #define errno (*viwerr_errno_redefine(__FILE__,__LINE__))
#endif /** @c VIWERR_SUBSCRIPTION_ERRNO */

/* SPDX-License-Identifier: 0BSD */
/* Copyright 2019 Alexander Kozhevnikov <mentalisttraceur@gmail.com> */

#ifndef ERRNONAME_C
#define ERRNONAME_C

char const * errnoname(int errno_)
{
#ifdef ERRNONAME_SAFE_TO_USE_ARRAY
    static char const * const names[] =
    {
        [0] = 0,
    #ifdef E2BIG
        [E2BIG] = "E2BIG",
    #endif
    #ifdef EACCES
        [EACCES] = "EACCES",
    #endif
    #ifdef EADDRINUSE
        [EADDRINUSE] = "EADDRINUSE",
    #endif
    #ifdef EADDRNOTAVAIL
        [EADDRNOTAVAIL] = "EADDRNOTAVAIL",
    #endif
    #ifdef EADI
        [EADI] = "EADI",
    #endif
    #ifdef EADV
        [EADV] = "EADV",
    #endif
    #ifdef EAFNOSUPPORT
        [EAFNOSUPPORT] = "EAFNOSUPPORT",
    #endif
    #ifdef EAGAIN
        [EAGAIN] = "EAGAIN",
    #endif
    #ifdef EAIO
        [EAIO] = "EAIO",
    #endif
    #ifdef EAI_AGAIN
        [EAI_AGAIN] = "EAI_AGAIN",
    #endif
    #ifdef EAI_BADFLAGS
        [EAI_BADFLAGS] = "EAI_BADFLAGS",
    #endif
    #ifdef EAI_FAIL
        [EAI_FAIL] = "EAI_FAIL",
    #endif
    #ifdef EAI_FAMILY
        [EAI_FAMILY] = "EAI_FAMILY",
    #endif
    #ifdef EAI_MEMORY
        [EAI_MEMORY] = "EAI_MEMORY",
    #endif
    #ifdef EAI_NONAME
        [EAI_NONAME] = "EAI_NONAME",
    #endif
    #ifdef EAI_OVERFLOW
        [EAI_OVERFLOW] = "EAI_OVERFLOW",
    #endif
    #ifdef EAI_SERVICE
        [EAI_SERVICE] = "EAI_SERVICE",
    #endif
    #ifdef EAI_SOCKTYPE
        [EAI_SOCKTYPE] = "EAI_SOCKTYPE",
    #endif
    #ifdef EALIGN
        [EALIGN] = "EALIGN",
    #endif
    #ifdef EALREADY
        [EALREADY] = "EALREADY",
    #endif
    #ifdef EASYNC
        [EASYNC] = "EASYNC",
    #endif
    #ifdef EAUTH
        [EAUTH] = "EAUTH",
    #endif
    #ifdef EBADARCH
        [EBADARCH] = "EBADARCH",
    #endif
    #ifdef EBADCOOKIE
        [EBADCOOKIE] = "EBADCOOKIE",
    #endif
    #ifdef EBADE
        [EBADE] = "EBADE",
    #endif
    #ifdef EBADEXEC
        [EBADEXEC] = "EBADEXEC",
    #endif
    #ifdef EBADF
        [EBADF] = "EBADF",
    #endif
    #ifdef EBADFD
        [EBADFD] = "EBADFD",
    #endif
    #ifdef EBADFSYS
        [EBADFSYS] = "EBADFSYS",
    #endif
    #ifdef EBADHANDLE
        [EBADHANDLE] = "EBADHANDLE",
    #endif
    #ifdef EBADMACHO
        [EBADMACHO] = "EBADMACHO",
    #endif
    #ifdef EBADMSG
        [EBADMSG] = "EBADMSG",
    #endif
    #ifdef EBADOBJ
        [EBADOBJ] = "EBADOBJ",
    #endif
    #ifdef EBADR
        [EBADR] = "EBADR",
    #endif
    #ifdef EBADRPC
        [EBADRPC] = "EBADRPC",
    #endif
    #ifdef EBADRQC
        [EBADRQC] = "EBADRQC",
    #endif
    #ifdef EBADSLT
        [EBADSLT] = "EBADSLT",
    #endif
    #ifdef EBADTYPE
        [EBADTYPE] = "EBADTYPE",
    #endif
    #ifdef EBADVER
        [EBADVER] = "EBADVER",
    #endif
    #ifdef EBFONT
        [EBFONT] = "EBFONT",
    #endif
    #ifdef EBUSY
        [EBUSY] = "EBUSY",
    #endif
    #ifdef ECANCEL
        [ECANCEL] = "ECANCEL",
    #endif
    #ifdef ECANCELED
        [ECANCELED] = "ECANCELED",
    #endif
    #ifdef ECANCELLED
        #if !defined(ECANCELED) || ECANCELLED != ECANCELED
        [ECANCELLED] = "ECANCELLED",
        #endif
    #endif
    #ifdef ECAPMODE
        [ECAPMODE] = "ECAPMODE",
    #endif
    #ifdef ECASECLASH
        [ECASECLASH] = "ECASECLASH",
    #endif
    #ifdef ECHILD
        [ECHILD] = "ECHILD",
    #endif
    #ifdef ECHRNG
        [ECHRNG] = "ECHRNG",
    #endif
    #ifdef ECKPT
        [ECKPT] = "ECKPT",
    #endif
    #ifdef ECKSUM
        [ECKSUM] = "ECKSUM",
    #endif
    #ifdef ECLONEME
        [ECLONEME] = "ECLONEME",
    #endif
    #ifdef ECLOSED
        [ECLOSED] = "ECLOSED",
    #endif
    #ifdef ECOMM
        [ECOMM] = "ECOMM",
    #endif
    #ifdef ECONFIG
        [ECONFIG] = "ECONFIG",
    #endif
    #ifdef ECONNABORTED
        [ECONNABORTED] = "ECONNABORTED",
    #endif
    #ifdef ECONNCLOSED
        [ECONNCLOSED] = "ECONNCLOSED",
    #endif
    #ifdef ECONNREFUSED
        [ECONNREFUSED] = "ECONNREFUSED",
    #endif
    #ifdef ECONNRESET
        [ECONNRESET] = "ECONNRESET",
    #endif
    #ifdef ECONSOLEINTERRUPT
        [ECONSOLEINTERRUPT] = "ECONSOLEINTERRUPT",
    #endif
    #ifdef ECORRUPT
        [ECORRUPT] = "ECORRUPT",
    #endif
    #ifdef ECTRLTERM
        [ECTRLTERM] = "ECTRLTERM",
    #endif
    #ifdef ECVCERORR
        [ECVCERORR] = "ECVCERORR",
    #endif
    #ifdef ECVPERORR
        [ECVPERORR] = "ECVPERORR",
    #endif
    #ifdef EDATALESS
        [EDATALESS] = "EDATALESS",
    #endif
    #ifdef EDEADLK
        [EDEADLK] = "EDEADLK",
    #endif
    #ifdef EDEADLOCK
        #if !defined(EDEADLK) || EDEADLOCK != EDEADLK
        [EDEADLOCK] = "EDEADLOCK",
        #endif
    #endif
    #ifdef EDESTADDREQ
        #if !defined(EDESTADDRREQ) || EDESTADDREQ != EDESTADDRREQ
        [EDESTADDREQ] = "EDESTADDREQ",
        #endif
    #endif
    #ifdef EDESTADDRREQ
        [EDESTADDRREQ] = "EDESTADDRREQ",
    #endif
    #ifdef EDEVERR
        [EDEVERR] = "EDEVERR",
    #endif
    #ifdef EDIRIOCTL
        [EDIRIOCTL] = "EDIRIOCTL",
    #endif
    #ifdef EDIRTY
        [EDIRTY] = "EDIRTY",
    #endif
    #ifdef EDIST
        [EDIST] = "EDIST",
    #endif
    #ifdef EDOM
        [EDOM] = "EDOM",
    #endif
    #ifdef EDOMAINSERVERFAILURE
        [EDOMAINSERVERFAILURE] = "EDOMAINSERVERFAILURE",
    #endif
    #ifdef EDOOFUS
        [EDOOFUS] = "EDOOFUS",
    #endif
    #ifdef EDOTDOT
        [EDOTDOT] = "EDOTDOT",
    #endif
    #ifdef EDQUOT
        [EDQUOT] = "EDQUOT",
    #endif
    #ifdef EDUPFD
        [EDUPFD] = "EDUPFD",
    #endif
    #ifdef EDUPPKG
        [EDUPPKG] = "EDUPPKG",
    #endif
    #ifdef EENDIAN
        [EENDIAN] = "EENDIAN",
    #endif
    #ifdef EEXIST
        [EEXIST] = "EEXIST",
    #endif
    #ifdef EFAIL
        [EFAIL] = "EFAIL",
    #endif
    #ifdef EFAULT
        [EFAULT] = "EFAULT",
    #endif
    #ifdef EFBIG
        [EFBIG] = "EFBIG",
    #endif
    #ifdef EFORMAT
        [EFORMAT] = "EFORMAT",
    #endif
    #ifdef EFPOS
        [EFPOS] = "EFPOS",
    #endif
    #ifdef EFRAGS
        [EFRAGS] = "EFRAGS",
    #endif
    #ifdef EFSCORRUPTED
        [EFSCORRUPTED] = "EFSCORRUPTED",
    #endif
    #ifdef EFTYPE
        [EFTYPE] = "EFTYPE",
    #endif
    #ifdef EHOSTDOWN
        [EHOSTDOWN] = "EHOSTDOWN",
    #endif
    #ifdef EHOSTNOTFOUND
        [EHOSTNOTFOUND] = "EHOSTNOTFOUND",
    #endif
    #ifdef EHOSTUNREACH
        [EHOSTUNREACH] = "EHOSTUNREACH",
    #endif
    #ifdef EHWPOISON
        [EHWPOISON] = "EHWPOISON",
    #endif
    #ifdef EIBMBADCONNECTIONMATCH
        [EIBMBADCONNECTIONMATCH] = "EIBMBADCONNECTIONMATCH",
    #endif
    #ifdef EIBMBADCONNECTIONSTATE
        [EIBMBADCONNECTIONSTATE] = "EIBMBADCONNECTIONSTATE",
    #endif
    #ifdef EIBMBADREQUESTCODE
        [EIBMBADREQUESTCODE] = "EIBMBADREQUESTCODE",
    #endif
    #ifdef EIBMBADTCPNAME
        [EIBMBADTCPNAME] = "EIBMBADTCPNAME",
    #endif
    #ifdef EIBMCALLINPROGRESS
        [EIBMCALLINPROGRESS] = "EIBMCALLINPROGRESS",
    #endif
    #ifdef EIBMCANCELLED
        [EIBMCANCELLED] = "EIBMCANCELLED",
    #endif
    #ifdef EIBMCONFLICT
        [EIBMCONFLICT] = "EIBMCONFLICT",
    #endif
    #ifdef EIBMINVDELETE
        [EIBMINVDELETE] = "EIBMINVDELETE",
    #endif
    #ifdef EIBMINVSOCKET
        [EIBMINVSOCKET] = "EIBMINVSOCKET",
    #endif
    #ifdef EIBMINVTCPCONNECTION
        [EIBMINVTCPCONNECTION] = "EIBMINVTCPCONNECTION",
    #endif
    #ifdef EIBMINVTSRBUSERDATA
        [EIBMINVTSRBUSERDATA] = "EIBMINVTSRBUSERDATA",
    #endif
    #ifdef EIBMINVUSERDATA
        [EIBMINVUSERDATA] = "EIBMINVUSERDATA",
    #endif
    #ifdef EIBMIUCVERR
        [EIBMIUCVERR] = "EIBMIUCVERR",
    #endif
    #ifdef EIBMNOACTIVETCP
        [EIBMNOACTIVETCP] = "EIBMNOACTIVETCP",
    #endif
    #ifdef EIBMSELECTEXPOST
        [EIBMSELECTEXPOST] = "EIBMSELECTEXPOST",
    #endif
    #ifdef EIBMSOCKINUSE
        [EIBMSOCKINUSE] = "EIBMSOCKINUSE",
    #endif
    #ifdef EIBMSOCKOUTOFRANGE
        [EIBMSOCKOUTOFRANGE] = "EIBMSOCKOUTOFRANGE",
    #endif
    #ifdef EIBMTCPABEND
        [EIBMTCPABEND] = "EIBMTCPABEND",
    #endif
    #ifdef EIBMTERMERROR
        [EIBMTERMERROR] = "EIBMTERMERROR",
    #endif
    #ifdef EIBMUNAUTHORIZEDCALLER
        [EIBMUNAUTHORIZEDCALLER] = "EIBMUNAUTHORIZEDCALLER",
    #endif
    #ifdef EIDRM
        [EIDRM] = "EIDRM",
    #endif
    #ifdef EILSEQ
        [EILSEQ] = "EILSEQ",
    #endif
    #ifdef EINIT
        [EINIT] = "EINIT",
    #endif
    #ifdef EINPROG
        #if !defined(EINPROGRESS) || EINPROG != EINPROGRESS
        [EINPROG] = "EINPROG",
        #endif
    #endif
    #ifdef EINPROGRESS
        [EINPROGRESS] = "EINPROGRESS",
    #endif
    #ifdef EINTEGRITY
        [EINTEGRITY] = "EINTEGRITY",
    #endif
    #ifdef EINTR
        [EINTR] = "EINTR",
    #endif
    #ifdef EINTRNODATA
        [EINTRNODATA] = "EINTRNODATA",
    #endif
    #ifdef EINVAL
        [EINVAL] = "EINVAL",
    #endif
    #ifdef EINVALIDCLIENTID
        [EINVALIDCLIENTID] = "EINVALIDCLIENTID",
    #endif
    #ifdef EINVALIDCOMBINATION
        [EINVALIDCOMBINATION] = "EINVALIDCOMBINATION",
    #endif
    #ifdef EINVALIDNAME
        [EINVALIDNAME] = "EINVALIDNAME",
    #endif
    #ifdef EINVALIDRXSOCKETCALL
        [EINVALIDRXSOCKETCALL] = "EINVALIDRXSOCKETCALL",
    #endif
    #ifdef EIO
        [EIO] = "EIO",
    #endif
    #ifdef EIOCBQUEUED
        [EIOCBQUEUED] = "EIOCBQUEUED",
    #endif
    #ifdef EIPADDRNOTFOUND
        [EIPADDRNOTFOUND] = "EIPADDRNOTFOUND",
    #endif
    #ifdef EIPSEC
        [EIPSEC] = "EIPSEC",
    #endif
    #ifdef EISCONN
        [EISCONN] = "EISCONN",
    #endif
    #ifdef EISDIR
        [EISDIR] = "EISDIR",
    #endif
    #ifdef EISNAM
        [EISNAM] = "EISNAM",
    #endif
    #ifdef EJUKEBOX
        [EJUKEBOX] = "EJUKEBOX",
    #endif
    #ifdef EJUSTRETURN
        [EJUSTRETURN] = "EJUSTRETURN",
    #endif
    #ifdef EKEEPLOOKING
        [EKEEPLOOKING] = "EKEEPLOOKING",
    #endif
    #ifdef EKEYEXPIRED
        [EKEYEXPIRED] = "EKEYEXPIRED",
    #endif
    #ifdef EKEYREJECTED
        [EKEYREJECTED] = "EKEYREJECTED",
    #endif
    #ifdef EKEYREVOKED
        [EKEYREVOKED] = "EKEYREVOKED",
    #endif
    #ifdef EL2HLT
        [EL2HLT] = "EL2HLT",
    #endif
    #ifdef EL2NSYNC
        [EL2NSYNC] = "EL2NSYNC",
    #endif
    #ifdef EL3HLT
        [EL3HLT] = "EL3HLT",
    #endif
    #ifdef EL3RST
        [EL3RST] = "EL3RST",
    #endif
    #ifdef ELBIN
        [ELBIN] = "ELBIN",
    #endif
    #ifdef ELIBACC
        [ELIBACC] = "ELIBACC",
    #endif
    #ifdef ELIBBAD
        [ELIBBAD] = "ELIBBAD",
    #endif
    #ifdef ELIBEXEC
        [ELIBEXEC] = "ELIBEXEC",
    #endif
    #ifdef ELIBMAX
        [ELIBMAX] = "ELIBMAX",
    #endif
    #ifdef ELIBSCN
        [ELIBSCN] = "ELIBSCN",
    #endif
    #ifdef ELINKED
        [ELINKED] = "ELINKED",
    #endif
    #ifdef ELNRNG
        [ELNRNG] = "ELNRNG",
    #endif
    #ifdef ELOCKUNMAPPED
        [ELOCKUNMAPPED] = "ELOCKUNMAPPED",
    #endif
    #ifdef ELOOP
        [ELOOP] = "ELOOP",
    #endif
    #ifdef EMAXSOCKETSREACHED
        [EMAXSOCKETSREACHED] = "EMAXSOCKETSREACHED",
    #endif
    #ifdef EMEDIA
        [EMEDIA] = "EMEDIA",
    #endif
    #ifdef EMEDIUMTYPE
        [EMEDIUMTYPE] = "EMEDIUMTYPE",
    #endif
    #ifdef EMFILE
        [EMFILE] = "EMFILE",
    #endif
    #ifdef EMISSED
        [EMISSED] = "EMISSED",
    #endif
    #ifdef EMLINK
        [EMLINK] = "EMLINK",
    #endif
    #ifdef EMORE
        [EMORE] = "EMORE",
    #endif
    #ifdef EMOUNTEXIT
        [EMOUNTEXIT] = "EMOUNTEXIT",
    #endif
    #ifdef EMOVEFD
        [EMOVEFD] = "EMOVEFD",
    #endif
    #ifdef EMSGSIZE
        [EMSGSIZE] = "EMSGSIZE",
    #endif
    #ifdef EMTIMERS
        [EMTIMERS] = "EMTIMERS",
    #endif
    #ifdef EMULTIHOP
        [EMULTIHOP] = "EMULTIHOP",
    #endif
    #ifdef EMVSARMERROR
        [EMVSARMERROR] = "EMVSARMERROR",
    #endif
    #ifdef EMVSCATLG
        [EMVSCATLG] = "EMVSCATLG",
    #endif
    #ifdef EMVSCPLERROR
        [EMVSCPLERROR] = "EMVSCPLERROR",
    #endif
    #ifdef EMVSCVAF
        [EMVSCVAF] = "EMVSCVAF",
    #endif
    #ifdef EMVSDYNALC
        [EMVSDYNALC] = "EMVSDYNALC",
    #endif
    #ifdef EMVSERR
        [EMVSERR] = "EMVSERR",
    #endif
    #ifdef EMVSEXPIRE
        [EMVSEXPIRE] = "EMVSEXPIRE",
    #endif
    #ifdef EMVSINITIAL
        [EMVSINITIAL] = "EMVSINITIAL",
    #endif
    #ifdef EMVSNORTL
        [EMVSNORTL] = "EMVSNORTL",
    #endif
    #ifdef EMVSNOTUP
        [EMVSNOTUP] = "EMVSNOTUP",
    #endif
    #ifdef EMVSPARM
        [EMVSPARM] = "EMVSPARM",
    #endif
    #ifdef EMVSPASSWORD
        [EMVSPASSWORD] = "EMVSPASSWORD",
    #endif
    #ifdef EMVSPFSFILE
        [EMVSPFSFILE] = "EMVSPFSFILE",
    #endif
    #ifdef EMVSPFSPERM
        [EMVSPFSPERM] = "EMVSPFSPERM",
    #endif
    #ifdef EMVSSAF2ERR
        [EMVSSAF2ERR] = "EMVSSAF2ERR",
    #endif
    #ifdef EMVSSAFEXTRERR
        [EMVSSAFEXTRERR] = "EMVSSAFEXTRERR",
    #endif
    #ifdef EMVSWLMERROR
        [EMVSWLMERROR] = "EMVSWLMERROR",
    #endif
    #ifdef ENAMETOOLONG
        [ENAMETOOLONG] = "ENAMETOOLONG",
    #endif
    #ifdef ENAVAIL
        [ENAVAIL] = "ENAVAIL",
    #endif
    #ifdef ENEEDAUTH
        [ENEEDAUTH] = "ENEEDAUTH",
    #endif
    #ifdef ENETDOWN
        [ENETDOWN] = "ENETDOWN",
    #endif
    #ifdef ENETRESET
        [ENETRESET] = "ENETRESET",
    #endif
    #ifdef ENETUNREACH
        [ENETUNREACH] = "ENETUNREACH",
    #endif
    #ifdef ENFILE
        [ENFILE] = "ENFILE",
    #endif
    #ifdef ENFSREMOTE
        [ENFSREMOTE] = "ENFSREMOTE",
    #endif
    #ifdef ENIVALIDFILENAME
        [ENIVALIDFILENAME] = "ENIVALIDFILENAME",
    #endif
    #ifdef ENMELONG
        [ENMELONG] = "ENMELONG",
    #endif
    #ifdef ENMFILE
        [ENMFILE] = "ENMFILE",
    #endif
    #ifdef ENOANO
        [ENOANO] = "ENOANO",
    #endif
    #ifdef ENOATTR
        [ENOATTR] = "ENOATTR",
    #endif
    #ifdef ENOBUFS
        [ENOBUFS] = "ENOBUFS",
    #endif
    #ifdef ENOCONNECT
        [ENOCONNECT] = "ENOCONNECT",
    #endif
    #ifdef ENOCSI
        [ENOCSI] = "ENOCSI",
    #endif
    #ifdef ENODATA
        [ENODATA] = "ENODATA",
    #endif
    #ifdef ENODEV
        [ENODEV] = "ENODEV",
    #endif
    #ifdef ENOENT
        [ENOENT] = "ENOENT",
    #endif
    #ifdef ENOEXEC
        [ENOEXEC] = "ENOEXEC",
    #endif
    #ifdef ENOGRACE
        [ENOGRACE] = "ENOGRACE",
    #endif
    #ifdef ENOIOCTL
        [ENOIOCTL] = "ENOIOCTL",
    #endif
    #ifdef ENOIOCTLCMD
        [ENOIOCTLCMD] = "ENOIOCTLCMD",
    #endif
    #ifdef ENOKEY
        [ENOKEY] = "ENOKEY",
    #endif
    #ifdef ENOLCK
        [ENOLCK] = "ENOLCK",
    #endif
    #ifdef ENOLIC
        [ENOLIC] = "ENOLIC",
    #endif
    #ifdef ENOLINK
        [ENOLINK] = "ENOLINK",
    #endif
    #ifdef ENOLOAD
        [ENOLOAD] = "ENOLOAD",
    #endif
    #ifdef ENOMATCH
        [ENOMATCH] = "ENOMATCH",
    #endif
    #ifdef ENOMEDIUM
        [ENOMEDIUM] = "ENOMEDIUM",
    #endif
    #ifdef ENOMEM
        [ENOMEM] = "ENOMEM",
    #endif
    #ifdef ENOMOVE
        [ENOMOVE] = "ENOMOVE",
    #endif
    #ifdef ENOMSG
        [ENOMSG] = "ENOMSG",
    #endif
    #ifdef ENONDP
        [ENONDP] = "ENONDP",
    #endif
    #ifdef ENONET
        [ENONET] = "ENONET",
    #endif
    #ifdef ENOPARAM
        [ENOPARAM] = "ENOPARAM",
    #endif
    #ifdef ENOPARTNERINFO
        [ENOPARTNERINFO] = "ENOPARTNERINFO",
    #endif
    #ifdef ENOPKG
        [ENOPKG] = "ENOPKG",
    #endif
    #ifdef ENOPOLICY
        [ENOPOLICY] = "ENOPOLICY",
    #endif
    #ifdef ENOPROTOOPT
        [ENOPROTOOPT] = "ENOPROTOOPT",
    #endif
    #ifdef ENOREG
        [ENOREG] = "ENOREG",
    #endif
    #ifdef ENOREMOTE
        [ENOREMOTE] = "ENOREMOTE",
    #endif
    #ifdef ENOREUSE
        [ENOREUSE] = "ENOREUSE",
    #endif
    #ifdef ENOSHARE
        [ENOSHARE] = "ENOSHARE",
    #endif
    #ifdef ENOSPC
        [ENOSPC] = "ENOSPC",
    #endif
    #ifdef ENOSR
        [ENOSR] = "ENOSR",
    #endif
    #ifdef ENOSTR
        [ENOSTR] = "ENOSTR",
    #endif
    #ifdef ENOSYM
        [ENOSYM] = "ENOSYM",
    #endif
    #ifdef ENOSYS
        [ENOSYS] = "ENOSYS",
    #endif
    #ifdef ENOTACTIVE
        [ENOTACTIVE] = "ENOTACTIVE",
    #endif
    #ifdef ENOTBLK
        [ENOTBLK] = "ENOTBLK",
    #endif
    #ifdef ENOTCAPABLE
        [ENOTCAPABLE] = "ENOTCAPABLE",
    #endif
    #ifdef ENOTCONN
        [ENOTCONN] = "ENOTCONN",
    #endif
    #ifdef ENOTDIR
        [ENOTDIR] = "ENOTDIR",
    #endif
    #ifdef ENOTEMPT
        [ENOTEMPT] = "ENOTEMPT",
    #endif
    #ifdef ENOTEMPTY
        [ENOTEMPTY] = "ENOTEMPTY",
    #endif
    #ifdef ENOTNAM
        [ENOTNAM] = "ENOTNAM",
    #endif
    #ifdef ENOTREADY
        [ENOTREADY] = "ENOTREADY",
    #endif
    #ifdef ENOTRECOVERABLE
        [ENOTRECOVERABLE] = "ENOTRECOVERABLE",
    #endif
    #ifdef ENOTRUST
        [ENOTRUST] = "ENOTRUST",
    #endif
    #ifdef ENOTSOCK
        [ENOTSOCK] = "ENOTSOCK",
    #endif
    #ifdef ENOTSUP
        [ENOTSUP] = "ENOTSUP",
    #endif
    #ifdef ENOTSUPP
        [ENOTSUPP] = "ENOTSUPP",
    #endif
    #ifdef ENOTSYNC
        [ENOTSYNC] = "ENOTSYNC",
    #endif
    #ifdef ENOTTY
        [ENOTTY] = "ENOTTY",
    #endif
    #ifdef ENOTUNIQ
        [ENOTUNIQ] = "ENOTUNIQ",
    #endif
    #ifdef ENOUNLD
        [ENOUNLD] = "ENOUNLD",
    #endif
    #ifdef ENOUNREG
        [ENOUNREG] = "ENOUNREG",
    #endif
    #ifdef ENXIO
        [ENXIO] = "ENXIO",
    #endif
    #ifdef EOFFLOADboxDOWN
        [EOFFLOADboxDOWN] = "EOFFLOADboxDOWN",
    #endif
    #ifdef EOFFLOADboxERROR
        [EOFFLOADboxERROR] = "EOFFLOADboxERROR",
    #endif
    #ifdef EOFFLOADboxRESTART
        [EOFFLOADboxRESTART] = "EOFFLOADboxRESTART",
    #endif
    #ifdef EOPCOMPLETE
        [EOPCOMPLETE] = "EOPCOMPLETE",
    #endif
    #ifdef EOPENSTALE
        [EOPENSTALE] = "EOPENSTALE",
    #endif
    #ifdef EOPNOTSUPP
        #if !defined(ENOTSUP) || EOPNOTSUPP != ENOTSUP
        [EOPNOTSUPP] = "EOPNOTSUPP",
        #endif
    #endif
    #ifdef EOUTOFSTATE
        [EOUTOFSTATE] = "EOUTOFSTATE",
    #endif
    #ifdef EOVERFLOW
        [EOVERFLOW] = "EOVERFLOW",
    #endif
    #ifdef EOWNERDEAD
        [EOWNERDEAD] = "EOWNERDEAD",
    #endif
    #ifdef EPASSTHROUGH
        [EPASSTHROUGH] = "EPASSTHROUGH",
    #endif
    #ifdef EPATHREMOTE
        [EPATHREMOTE] = "EPATHREMOTE",
    #endif
    #ifdef EPERM
        [EPERM] = "EPERM",
    #endif
    #ifdef EPFNOSUPPORT
        [EPFNOSUPPORT] = "EPFNOSUPPORT",
    #endif
    #ifdef EPIPE
        [EPIPE] = "EPIPE",
    #endif
    #ifdef EPOWERF
        [EPOWERF] = "EPOWERF",
    #endif
    #ifdef EPROBE_DEFER
        [EPROBE_DEFER] = "EPROBE_DEFER",
    #endif
    #ifdef EPROCLIM
        [EPROCLIM] = "EPROCLIM",
    #endif
    #ifdef EPROCUNAVAIL
        [EPROCUNAVAIL] = "EPROCUNAVAIL",
    #endif
    #ifdef EPROGMISMATCH
        [EPROGMISMATCH] = "EPROGMISMATCH",
    #endif
    #ifdef EPROGUNAVAIL
        [EPROGUNAVAIL] = "EPROGUNAVAIL",
    #endif
    #ifdef EPROTO
        [EPROTO] = "EPROTO",
    #endif
    #ifdef EPROTONOSUPPORT
        [EPROTONOSUPPORT] = "EPROTONOSUPPORT",
    #endif
    #ifdef EPROTOTYPE
        [EPROTOTYPE] = "EPROTOTYPE",
    #endif
    #ifdef EPWROFF
        [EPWROFF] = "EPWROFF",
    #endif
    #ifdef EQFULL
        [EQFULL] = "EQFULL",
    #endif
    #ifdef EQSUSPENDED
        [EQSUSPENDED] = "EQSUSPENDED",
    #endif
    #ifdef ERANGE
        [ERANGE] = "ERANGE",
    #endif
    #ifdef ERECALLCONFLICT
        [ERECALLCONFLICT] = "ERECALLCONFLICT",
    #endif
    #ifdef ERECURSE
        [ERECURSE] = "ERECURSE",
    #endif
    #ifdef ERECYCLE
        [ERECYCLE] = "ERECYCLE",
    #endif
    #ifdef EREDRIVEOPEN
        [EREDRIVEOPEN] = "EREDRIVEOPEN",
    #endif
    #ifdef EREFUSED
        #if !defined(ECONNREFUSED) || EREFUSED != ECONNREFUSED
        [EREFUSED] = "EREFUSED",
        #endif
    #endif
    #ifdef ERELOC
        [ERELOC] = "ERELOC",
    #endif
    #ifdef ERELOCATED
        [ERELOCATED] = "ERELOCATED",
    #endif
    #ifdef ERELOOKUP
        [ERELOOKUP] = "ERELOOKUP",
    #endif
    #ifdef EREMCHG
        [EREMCHG] = "EREMCHG",
    #endif
    #ifdef EREMDEV
        [EREMDEV] = "EREMDEV",
    #endif
    #ifdef EREMOTE
        [EREMOTE] = "EREMOTE",
    #endif
    #ifdef EREMOTEIO
        [EREMOTEIO] = "EREMOTEIO",
    #endif
    #ifdef EREMOTERELEASE
        [EREMOTERELEASE] = "EREMOTERELEASE",
    #endif
    #ifdef ERESTART
        [ERESTART] = "ERESTART",
    #endif
    #ifdef ERESTARTNOHAND
        [ERESTARTNOHAND] = "ERESTARTNOHAND",
    #endif
    #ifdef ERESTARTNOINTR
        [ERESTARTNOINTR] = "ERESTARTNOINTR",
    #endif
    #ifdef ERESTARTSYS
        [ERESTARTSYS] = "ERESTARTSYS",
    #endif
    #ifdef ERESTART_RESTARTBLOCK
        [ERESTART_RESTARTBLOCK] = "ERESTART_RESTARTBLOCK",
    #endif
    #ifdef ERFKILL
        [ERFKILL] = "ERFKILL",
    #endif
    #ifdef EROFS
        [EROFS] = "EROFS",
    #endif
    #ifdef ERPCMISMATCH
        [ERPCMISMATCH] = "ERPCMISMATCH",
    #endif
    #ifdef ERREMOTE
        [ERREMOTE] = "ERREMOTE",
    #endif
    #ifdef ESAD
        [ESAD] = "ESAD",
    #endif
    #ifdef ESECTYPEINVAL
        [ESECTYPEINVAL] = "ESECTYPEINVAL",
    #endif
    #ifdef ESERVERFAULT
        [ESERVERFAULT] = "ESERVERFAULT",
    #endif
    #ifdef ESHLIBVERS
        [ESHLIBVERS] = "ESHLIBVERS",
    #endif
    #ifdef ESHUTDOWN
        [ESHUTDOWN] = "ESHUTDOWN",
    #endif
    #ifdef ESIGPARM
        [ESIGPARM] = "ESIGPARM",
    #endif
    #ifdef ESOCKETNOTALLOCATED
        [ESOCKETNOTALLOCATED] = "ESOCKETNOTALLOCATED",
    #endif
    #ifdef ESOCKETNOTDEFINED
        [ESOCKETNOTDEFINED] = "ESOCKETNOTDEFINED",
    #endif
    #ifdef ESOCKTNOSUPPORT
        [ESOCKTNOSUPPORT] = "ESOCKTNOSUPPORT",
    #endif
    #ifdef ESOFT
        [ESOFT] = "ESOFT",
    #endif
    #ifdef ESPIPE
        [ESPIPE] = "ESPIPE",
    #endif
    #ifdef ESRCH
        [ESRCH] = "ESRCH",
    #endif
    #ifdef ESRMNT
        [ESRMNT] = "ESRMNT",
    #endif
    #ifdef ESRVRFAULT
        [ESRVRFAULT] = "ESRVRFAULT",
    #endif
    #ifdef ESTALE
        [ESTALE] = "ESTALE",
    #endif
    #ifdef ESTRPIPE
        [ESTRPIPE] = "ESTRPIPE",
    #endif
    #ifdef ESUBTASKALREADYACTIVE
        [ESUBTASKALREADYACTIVE] = "ESUBTASKALREADYACTIVE",
    #endif
    #ifdef ESUBTASKINVALID
        [ESUBTASKINVALID] = "ESUBTASKINVALID",
    #endif
    #ifdef ESUBTASKNOTACTIVE
        [ESUBTASKNOTACTIVE] = "ESUBTASKNOTACTIVE",
    #endif
    #ifdef ESYSERROR
        [ESYSERROR] = "ESYSERROR",
    #endif
    #ifdef ETERM
        [ETERM] = "ETERM",
    #endif
    #ifdef ETIME
        [ETIME] = "ETIME",
    #endif
    #ifdef ETIMEDOUT
        [ETIMEDOUT] = "ETIMEDOUT",
    #endif
    #ifdef ETOOMANYREFS
        [ETOOMANYREFS] = "ETOOMANYREFS",
    #endif
    #ifdef ETOOSMALL
        [ETOOSMALL] = "ETOOSMALL",
    #endif
    #ifdef ETXTBSY
        [ETXTBSY] = "ETXTBSY",
    #endif
    #ifdef ETcpBadObj
        [ETcpBadObj] = "ETcpBadObj",
    #endif
    #ifdef ETcpClosed
        [ETcpClosed] = "ETcpClosed",
    #endif
    #ifdef ETcpErr
        [ETcpErr] = "ETcpErr",
    #endif
    #ifdef ETcpLinked
        [ETcpLinked] = "ETcpLinked",
    #endif
    #ifdef ETcpOutOfState
        [ETcpOutOfState] = "ETcpOutOfState",
    #endif
    #ifdef ETcpUnattach
        [ETcpUnattach] = "ETcpUnattach",
    #endif
    #ifdef EUCLEAN
        [EUCLEAN] = "EUCLEAN",
    #endif
    #ifdef EUNATCH
        [EUNATCH] = "EUNATCH",
    #endif
    #ifdef EUNKNOWN
        [EUNKNOWN] = "EUNKNOWN",
    #endif
    #ifdef EUSERS
        [EUSERS] = "EUSERS",
    #endif
    #ifdef EVERSION
        [EVERSION] = "EVERSION",
    #endif
    #ifdef EWOULDBLOCK
        #if !defined(EAGAIN) || EWOULDBLOCK != EAGAIN
        [EWOULDBLOCK] = "EWOULDBLOCK",
        #endif
    #endif
    #ifdef EWRONGFS
        [EWRONGFS] = "EWRONGFS",
    #endif
    #ifdef EWRPROTECT
        [EWRPROTECT] = "EWRPROTECT",
    #endif
    #ifdef EXDEV
        [EXDEV] = "EXDEV",
    #endif
    #ifdef EXFULL
        [EXFULL] = "EXFULL",
    #endif
    };
    if(errno_ >= 0 && errno_ < (sizeof(names) / sizeof(*names)))
    {
        return names[errno_];
    }
    return 0;
#else /* ERRNONAME_SAFE_TO_USE_ARRAY */
    switch(errno_)
    {
        case 0: return 0;
    #ifdef E2BIG
        case E2BIG: return "E2BIG";
    #endif
    #ifdef EACCES
        case EACCES: return "EACCES";
    #endif
    #ifdef EADDRINUSE
        case EADDRINUSE: return "EADDRINUSE";
    #endif
    #ifdef EADDRNOTAVAIL
        case EADDRNOTAVAIL: return "EADDRNOTAVAIL";
    #endif
    #ifdef EADI
        case EADI: return "EADI";
    #endif
    #ifdef EADV
        case EADV: return "EADV";
    #endif
    #ifdef EAFNOSUPPORT
        case EAFNOSUPPORT: return "EAFNOSUPPORT";
    #endif
    #ifdef EAGAIN
        case EAGAIN: return "EAGAIN";
    #endif
    #ifdef EAIO
        case EAIO: return "EAIO";
    #endif
    #ifdef EAI_AGAIN
        case EAI_AGAIN: return "EAI_AGAIN";
    #endif
    #ifdef EAI_BADFLAGS
        case EAI_BADFLAGS: return "EAI_BADFLAGS";
    #endif
    #ifdef EAI_FAIL
        case EAI_FAIL: return "EAI_FAIL";
    #endif
    #ifdef EAI_FAMILY
        case EAI_FAMILY: return "EAI_FAMILY";
    #endif
    #ifdef EAI_MEMORY
        case EAI_MEMORY: return "EAI_MEMORY";
    #endif
    #ifdef EAI_NONAME
        case EAI_NONAME: return "EAI_NONAME";
    #endif
    #ifdef EAI_OVERFLOW
        case EAI_OVERFLOW: return "EAI_OVERFLOW";
    #endif
    #ifdef EAI_SERVICE
        case EAI_SERVICE: return "EAI_SERVICE";
    #endif
    #ifdef EAI_SOCKTYPE
        case EAI_SOCKTYPE: return "EAI_SOCKTYPE";
    #endif
    #ifdef EALIGN
        case EALIGN: return "EALIGN";
    #endif
    #ifdef EALREADY
        case EALREADY: return "EALREADY";
    #endif
    #ifdef EASYNC
        case EASYNC: return "EASYNC";
    #endif
    #ifdef EAUTH
        case EAUTH: return "EAUTH";
    #endif
    #ifdef EBADARCH
        case EBADARCH: return "EBADARCH";
    #endif
    #ifdef EBADCOOKIE
        case EBADCOOKIE: return "EBADCOOKIE";
    #endif
    #ifdef EBADE
        case EBADE: return "EBADE";
    #endif
    #ifdef EBADEXEC
        case EBADEXEC: return "EBADEXEC";
    #endif
    #ifdef EBADF
        case EBADF: return "EBADF";
    #endif
    #ifdef EBADFD
        case EBADFD: return "EBADFD";
    #endif
    #ifdef EBADFSYS
        case EBADFSYS: return "EBADFSYS";
    #endif
    #ifdef EBADHANDLE
        case EBADHANDLE: return "EBADHANDLE";
    #endif
    #ifdef EBADMACHO
        case EBADMACHO: return "EBADMACHO";
    #endif
    #ifdef EBADMSG
        case EBADMSG: return "EBADMSG";
    #endif
    #ifdef EBADOBJ
        case EBADOBJ: return "EBADOBJ";
    #endif
    #ifdef EBADR
        case EBADR: return "EBADR";
    #endif
    #ifdef EBADRPC
        case EBADRPC: return "EBADRPC";
    #endif
    #ifdef EBADRQC
        case EBADRQC: return "EBADRQC";
    #endif
    #ifdef EBADSLT
        case EBADSLT: return "EBADSLT";
    #endif
    #ifdef EBADTYPE
        case EBADTYPE: return "EBADTYPE";
    #endif
    #ifdef EBADVER
        case EBADVER: return "EBADVER";
    #endif
    #ifdef EBFONT
        case EBFONT: return "EBFONT";
    #endif
    #ifdef EBUSY
        case EBUSY: return "EBUSY";
    #endif
    #ifdef ECANCEL
        case ECANCEL: return "ECANCEL";
    #endif
    #ifdef ECANCELED
        case ECANCELED: return "ECANCELED";
    #endif
    #ifdef ECANCELLED
        #if !defined(ECANCELED) || ECANCELLED != ECANCELED
        case ECANCELLED: return "ECANCELLED";
        #endif
    #endif
    #ifdef ECAPMODE
        case ECAPMODE: return "ECAPMODE";
    #endif
    #ifdef ECASECLASH
        case ECASECLASH: return "ECASECLASH";
    #endif
    #ifdef ECHILD
        case ECHILD: return "ECHILD";
    #endif
    #ifdef ECHRNG
        case ECHRNG: return "ECHRNG";
    #endif
    #ifdef ECKPT
        case ECKPT: return "ECKPT";
    #endif
    #ifdef ECKSUM
        case ECKSUM: return "ECKSUM";
    #endif
    #ifdef ECLONEME
        case ECLONEME: return "ECLONEME";
    #endif
    #ifdef ECLOSED
        case ECLOSED: return "ECLOSED";
    #endif
    #ifdef ECOMM
        case ECOMM: return "ECOMM";
    #endif
    #ifdef ECONFIG
        case ECONFIG: return "ECONFIG";
    #endif
    #ifdef ECONNABORTED
        case ECONNABORTED: return "ECONNABORTED";
    #endif
    #ifdef ECONNCLOSED
        case ECONNCLOSED: return "ECONNCLOSED";
    #endif
    #ifdef ECONNREFUSED
        case ECONNREFUSED: return "ECONNREFUSED";
    #endif
    #ifdef ECONNRESET
        case ECONNRESET: return "ECONNRESET";
    #endif
    #ifdef ECONSOLEINTERRUPT
        case ECONSOLEINTERRUPT: return "ECONSOLEINTERRUPT";
    #endif
    #ifdef ECORRUPT
        case ECORRUPT: return "ECORRUPT";
    #endif
    #ifdef ECTRLTERM
        case ECTRLTERM: return "ECTRLTERM";
    #endif
    #ifdef ECVCERORR
        case ECVCERORR: return "ECVCERORR";
    #endif
    #ifdef ECVPERORR
        case ECVPERORR: return "ECVPERORR";
    #endif
    #ifdef EDATALESS
        case EDATALESS: return "EDATALESS";
    #endif
    #ifdef EDEADLK
        case EDEADLK: return "EDEADLK";
    #endif
    #ifdef EDEADLOCK
        #if !defined(EDEADLK) || EDEADLOCK != EDEADLK
        case EDEADLOCK: return "EDEADLOCK";
        #endif
    #endif
    #ifdef EDESTADDREQ
        #if !defined(EDESTADDRREQ) || EDESTADDREQ != EDESTADDRREQ
        case EDESTADDREQ: return "EDESTADDREQ";
        #endif
    #endif
    #ifdef EDESTADDRREQ
        case EDESTADDRREQ: return "EDESTADDRREQ";
    #endif
    #ifdef EDEVERR
        case EDEVERR: return "EDEVERR";
    #endif
    #ifdef EDIRIOCTL
        case EDIRIOCTL: return "EDIRIOCTL";
    #endif
    #ifdef EDIRTY
        case EDIRTY: return "EDIRTY";
    #endif
    #ifdef EDIST
        case EDIST: return "EDIST";
    #endif
    #ifdef EDOM
        case EDOM: return "EDOM";
    #endif
    #ifdef EDOMAINSERVERFAILURE
        case EDOMAINSERVERFAILURE: return "EDOMAINSERVERFAILURE";
    #endif
    #ifdef EDOOFUS
        case EDOOFUS: return "EDOOFUS";
    #endif
    #ifdef EDOTDOT
        case EDOTDOT: return "EDOTDOT";
    #endif
    #ifdef EDQUOT
        case EDQUOT: return "EDQUOT";
    #endif
    #ifdef EDUPFD
        case EDUPFD: return "EDUPFD";
    #endif
    #ifdef EDUPPKG
        case EDUPPKG: return "EDUPPKG";
    #endif
    #ifdef EENDIAN
        case EENDIAN: return "EENDIAN";
    #endif
    #ifdef EEXIST
        case EEXIST: return "EEXIST";
    #endif
    #ifdef EFAIL
        case EFAIL: return "EFAIL";
    #endif
    #ifdef EFAULT
        case EFAULT: return "EFAULT";
    #endif
    #ifdef EFBIG
        case EFBIG: return "EFBIG";
    #endif
    #ifdef EFORMAT
        case EFORMAT: return "EFORMAT";
    #endif
    #ifdef EFPOS
        case EFPOS: return "EFPOS";
    #endif
    #ifdef EFRAGS
        case EFRAGS: return "EFRAGS";
    #endif
    #ifdef EFSCORRUPTED
        case EFSCORRUPTED: return "EFSCORRUPTED";
    #endif
    #ifdef EFTYPE
        case EFTYPE: return "EFTYPE";
    #endif
    #ifdef EHOSTDOWN
        case EHOSTDOWN: return "EHOSTDOWN";
    #endif
    #ifdef EHOSTNOTFOUND
        case EHOSTNOTFOUND: return "EHOSTNOTFOUND";
    #endif
    #ifdef EHOSTUNREACH
        case EHOSTUNREACH: return "EHOSTUNREACH";
    #endif
    #ifdef EHWPOISON
        case EHWPOISON: return "EHWPOISON";
    #endif
    #ifdef EIBMBADCONNECTIONMATCH
        case EIBMBADCONNECTIONMATCH: return "EIBMBADCONNECTIONMATCH";
    #endif
    #ifdef EIBMBADCONNECTIONSTATE
        case EIBMBADCONNECTIONSTATE: return "EIBMBADCONNECTIONSTATE";
    #endif
    #ifdef EIBMBADREQUESTCODE
        case EIBMBADREQUESTCODE: return "EIBMBADREQUESTCODE";
    #endif
    #ifdef EIBMBADTCPNAME
        case EIBMBADTCPNAME: return "EIBMBADTCPNAME";
    #endif
    #ifdef EIBMCALLINPROGRESS
        case EIBMCALLINPROGRESS: return "EIBMCALLINPROGRESS";
    #endif
    #ifdef EIBMCANCELLED
        case EIBMCANCELLED: return "EIBMCANCELLED";
    #endif
    #ifdef EIBMCONFLICT
        case EIBMCONFLICT: return "EIBMCONFLICT";
    #endif
    #ifdef EIBMINVDELETE
        case EIBMINVDELETE: return "EIBMINVDELETE";
    #endif
    #ifdef EIBMINVSOCKET
        case EIBMINVSOCKET: return "EIBMINVSOCKET";
    #endif
    #ifdef EIBMINVTCPCONNECTION
        case EIBMINVTCPCONNECTION: return "EIBMINVTCPCONNECTION";
    #endif
    #ifdef EIBMINVTSRBUSERDATA
        case EIBMINVTSRBUSERDATA: return "EIBMINVTSRBUSERDATA";
    #endif
    #ifdef EIBMINVUSERDATA
        case EIBMINVUSERDATA: return "EIBMINVUSERDATA";
    #endif
    #ifdef EIBMIUCVERR
        case EIBMIUCVERR: return "EIBMIUCVERR";
    #endif
    #ifdef EIBMNOACTIVETCP
        case EIBMNOACTIVETCP: return "EIBMNOACTIVETCP";
    #endif
    #ifdef EIBMSELECTEXPOST
        case EIBMSELECTEXPOST: return "EIBMSELECTEXPOST";
    #endif
    #ifdef EIBMSOCKINUSE
        case EIBMSOCKINUSE: return "EIBMSOCKINUSE";
    #endif
    #ifdef EIBMSOCKOUTOFRANGE
        case EIBMSOCKOUTOFRANGE: return "EIBMSOCKOUTOFRANGE";
    #endif
    #ifdef EIBMTCPABEND
        case EIBMTCPABEND: return "EIBMTCPABEND";
    #endif
    #ifdef EIBMTERMERROR
        case EIBMTERMERROR: return "EIBMTERMERROR";
    #endif
    #ifdef EIBMUNAUTHORIZEDCALLER
        case EIBMUNAUTHORIZEDCALLER: return "EIBMUNAUTHORIZEDCALLER";
    #endif
    #ifdef EIDRM
        case EIDRM: return "EIDRM";
    #endif
    #ifdef EILSEQ
        case EILSEQ: return "EILSEQ";
    #endif
    #ifdef EINIT
        case EINIT: return "EINIT";
    #endif
    #ifdef EINPROG
        #if !defined(EINPROGRESS) || EINPROG != EINPROGRESS
        case EINPROG: return "EINPROG";
        #endif
    #endif
    #ifdef EINPROGRESS
        case EINPROGRESS: return "EINPROGRESS";
    #endif
    #ifdef EINTEGRITY
        case EINTEGRITY: return "EINTEGRITY";
    #endif
    #ifdef EINTR
        case EINTR: return "EINTR";
    #endif
    #ifdef EINTRNODATA
        case EINTRNODATA: return "EINTRNODATA";
    #endif
    #ifdef EINVAL
        case EINVAL: return "EINVAL";
    #endif
    #ifdef EINVALIDCLIENTID
        case EINVALIDCLIENTID: return "EINVALIDCLIENTID";
    #endif
    #ifdef EINVALIDCOMBINATION
        case EINVALIDCOMBINATION: return "EINVALIDCOMBINATION";
    #endif
    #ifdef EINVALIDNAME
        case EINVALIDNAME: return "EINVALIDNAME";
    #endif
    #ifdef EINVALIDRXSOCKETCALL
        case EINVALIDRXSOCKETCALL: return "EINVALIDRXSOCKETCALL";
    #endif
    #ifdef EIO
        case EIO: return "EIO";
    #endif
    #ifdef EIOCBQUEUED
        case EIOCBQUEUED: return "EIOCBQUEUED";
    #endif
    #ifdef EIPADDRNOTFOUND
        case EIPADDRNOTFOUND: return "EIPADDRNOTFOUND";
    #endif
    #ifdef EIPSEC
        case EIPSEC: return "EIPSEC";
    #endif
    #ifdef EISCONN
        case EISCONN: return "EISCONN";
    #endif
    #ifdef EISDIR
        case EISDIR: return "EISDIR";
    #endif
    #ifdef EISNAM
        case EISNAM: return "EISNAM";
    #endif
    #ifdef EJUKEBOX
        case EJUKEBOX: return "EJUKEBOX";
    #endif
    #ifdef EJUSTRETURN
        case EJUSTRETURN: return "EJUSTRETURN";
    #endif
    #ifdef EKEEPLOOKING
        case EKEEPLOOKING: return "EKEEPLOOKING";
    #endif
    #ifdef EKEYEXPIRED
        case EKEYEXPIRED: return "EKEYEXPIRED";
    #endif
    #ifdef EKEYREJECTED
        case EKEYREJECTED: return "EKEYREJECTED";
    #endif
    #ifdef EKEYREVOKED
        case EKEYREVOKED: return "EKEYREVOKED";
    #endif
    #ifdef EL2HLT
        case EL2HLT: return "EL2HLT";
    #endif
    #ifdef EL2NSYNC
        case EL2NSYNC: return "EL2NSYNC";
    #endif
    #ifdef EL3HLT
        case EL3HLT: return "EL3HLT";
    #endif
    #ifdef EL3RST
        case EL3RST: return "EL3RST";
    #endif
    #ifdef ELBIN
        case ELBIN: return "ELBIN";
    #endif
    #ifdef ELIBACC
        case ELIBACC: return "ELIBACC";
    #endif
    #ifdef ELIBBAD
        case ELIBBAD: return "ELIBBAD";
    #endif
    #ifdef ELIBEXEC
        case ELIBEXEC: return "ELIBEXEC";
    #endif
    #ifdef ELIBMAX
        case ELIBMAX: return "ELIBMAX";
    #endif
    #ifdef ELIBSCN
        case ELIBSCN: return "ELIBSCN";
    #endif
    #ifdef ELINKED
        case ELINKED: return "ELINKED";
    #endif
    #ifdef ELNRNG
        case ELNRNG: return "ELNRNG";
    #endif
    #ifdef ELOCKUNMAPPED
        case ELOCKUNMAPPED: return "ELOCKUNMAPPED";
    #endif
    #ifdef ELOOP
        case ELOOP: return "ELOOP";
    #endif
    #ifdef EMAXSOCKETSREACHED
        case EMAXSOCKETSREACHED: return "EMAXSOCKETSREACHED";
    #endif
    #ifdef EMEDIA
        case EMEDIA: return "EMEDIA";
    #endif
    #ifdef EMEDIUMTYPE
        case EMEDIUMTYPE: return "EMEDIUMTYPE";
    #endif
    #ifdef EMFILE
        case EMFILE: return "EMFILE";
    #endif
    #ifdef EMISSED
        case EMISSED: return "EMISSED";
    #endif
    #ifdef EMLINK
        case EMLINK: return "EMLINK";
    #endif
    #ifdef EMORE
        case EMORE: return "EMORE";
    #endif
    #ifdef EMOUNTEXIT
        case EMOUNTEXIT: return "EMOUNTEXIT";
    #endif
    #ifdef EMOVEFD
        case EMOVEFD: return "EMOVEFD";
    #endif
    #ifdef EMSGSIZE
        case EMSGSIZE: return "EMSGSIZE";
    #endif
    #ifdef EMTIMERS
        case EMTIMERS: return "EMTIMERS";
    #endif
    #ifdef EMULTIHOP
        case EMULTIHOP: return "EMULTIHOP";
    #endif
    #ifdef EMVSARMERROR
        case EMVSARMERROR: return "EMVSARMERROR";
    #endif
    #ifdef EMVSCATLG
        case EMVSCATLG: return "EMVSCATLG";
    #endif
    #ifdef EMVSCPLERROR
        case EMVSCPLERROR: return "EMVSCPLERROR";
    #endif
    #ifdef EMVSCVAF
        case EMVSCVAF: return "EMVSCVAF";
    #endif
    #ifdef EMVSDYNALC
        case EMVSDYNALC: return "EMVSDYNALC";
    #endif
    #ifdef EMVSERR
        case EMVSERR: return "EMVSERR";
    #endif
    #ifdef EMVSEXPIRE
        case EMVSEXPIRE: return "EMVSEXPIRE";
    #endif
    #ifdef EMVSINITIAL
        case EMVSINITIAL: return "EMVSINITIAL";
    #endif
    #ifdef EMVSNORTL
        case EMVSNORTL: return "EMVSNORTL";
    #endif
    #ifdef EMVSNOTUP
        case EMVSNOTUP: return "EMVSNOTUP";
    #endif
    #ifdef EMVSPARM
        case EMVSPARM: return "EMVSPARM";
    #endif
    #ifdef EMVSPASSWORD
        case EMVSPASSWORD: return "EMVSPASSWORD";
    #endif
    #ifdef EMVSPFSFILE
        case EMVSPFSFILE: return "EMVSPFSFILE";
    #endif
    #ifdef EMVSPFSPERM
        case EMVSPFSPERM: return "EMVSPFSPERM";
    #endif
    #ifdef EMVSSAF2ERR
        case EMVSSAF2ERR: return "EMVSSAF2ERR";
    #endif
    #ifdef EMVSSAFEXTRERR
        case EMVSSAFEXTRERR: return "EMVSSAFEXTRERR";
    #endif
    #ifdef EMVSWLMERROR
        case EMVSWLMERROR: return "EMVSWLMERROR";
    #endif
    #ifdef ENAMETOOLONG
        case ENAMETOOLONG: return "ENAMETOOLONG";
    #endif
    #ifdef ENAVAIL
        case ENAVAIL: return "ENAVAIL";
    #endif
    #ifdef ENEEDAUTH
        case ENEEDAUTH: return "ENEEDAUTH";
    #endif
    #ifdef ENETDOWN
        case ENETDOWN: return "ENETDOWN";
    #endif
    #ifdef ENETRESET
        case ENETRESET: return "ENETRESET";
    #endif
    #ifdef ENETUNREACH
        case ENETUNREACH: return "ENETUNREACH";
    #endif
    #ifdef ENFILE
        case ENFILE: return "ENFILE";
    #endif
    #ifdef ENFSREMOTE
        case ENFSREMOTE: return "ENFSREMOTE";
    #endif
    #ifdef ENIVALIDFILENAME
        case ENIVALIDFILENAME: return "ENIVALIDFILENAME";
    #endif
    #ifdef ENMELONG
        case ENMELONG: return "ENMELONG";
    #endif
    #ifdef ENMFILE
        case ENMFILE: return "ENMFILE";
    #endif
    #ifdef ENOANO
        case ENOANO: return "ENOANO";
    #endif
    #ifdef ENOATTR
        case ENOATTR: return "ENOATTR";
    #endif
    #ifdef ENOBUFS
        case ENOBUFS: return "ENOBUFS";
    #endif
    #ifdef ENOCONNECT
        case ENOCONNECT: return "ENOCONNECT";
    #endif
    #ifdef ENOCSI
        case ENOCSI: return "ENOCSI";
    #endif
    #ifdef ENODATA
        case ENODATA: return "ENODATA";
    #endif
    #ifdef ENODEV
        case ENODEV: return "ENODEV";
    #endif
    #ifdef ENOENT
        case ENOENT: return "ENOENT";
    #endif
    #ifdef ENOEXEC
        case ENOEXEC: return "ENOEXEC";
    #endif
    #ifdef ENOGRACE
        case ENOGRACE: return "ENOGRACE";
    #endif
    #ifdef ENOIOCTL
        case ENOIOCTL: return "ENOIOCTL";
    #endif
    #ifdef ENOIOCTLCMD
        case ENOIOCTLCMD: return "ENOIOCTLCMD";
    #endif
    #ifdef ENOKEY
        case ENOKEY: return "ENOKEY";
    #endif
    #ifdef ENOLCK
        case ENOLCK: return "ENOLCK";
    #endif
    #ifdef ENOLIC
        case ENOLIC: return "ENOLIC";
    #endif
    #ifdef ENOLINK
        case ENOLINK: return "ENOLINK";
    #endif
    #ifdef ENOLOAD
        case ENOLOAD: return "ENOLOAD";
    #endif
    #ifdef ENOMATCH
        case ENOMATCH: return "ENOMATCH";
    #endif
    #ifdef ENOMEDIUM
        case ENOMEDIUM: return "ENOMEDIUM";
    #endif
    #ifdef ENOMEM
        case ENOMEM: return "ENOMEM";
    #endif
    #ifdef ENOMOVE
        case ENOMOVE: return "ENOMOVE";
    #endif
    #ifdef ENOMSG
        case ENOMSG: return "ENOMSG";
    #endif
    #ifdef ENONDP
        case ENONDP: return "ENONDP";
    #endif
    #ifdef ENONET
        case ENONET: return "ENONET";
    #endif
    #ifdef ENOPARAM
        case ENOPARAM: return "ENOPARAM";
    #endif
    #ifdef ENOPARTNERINFO
        case ENOPARTNERINFO: return "ENOPARTNERINFO";
    #endif
    #ifdef ENOPKG
        case ENOPKG: return "ENOPKG";
    #endif
    #ifdef ENOPOLICY
        case ENOPOLICY: return "ENOPOLICY";
    #endif
    #ifdef ENOPROTOOPT
        case ENOPROTOOPT: return "ENOPROTOOPT";
    #endif
    #ifdef ENOREG
        case ENOREG: return "ENOREG";
    #endif
    #ifdef ENOREMOTE
        case ENOREMOTE: return "ENOREMOTE";
    #endif
    #ifdef ENOREUSE
        case ENOREUSE: return "ENOREUSE";
    #endif
    #ifdef ENOSHARE
        case ENOSHARE: return "ENOSHARE";
    #endif
    #ifdef ENOSPC
        case ENOSPC: return "ENOSPC";
    #endif
    #ifdef ENOSR
        case ENOSR: return "ENOSR";
    #endif
    #ifdef ENOSTR
        case ENOSTR: return "ENOSTR";
    #endif
    #ifdef ENOSYM
        case ENOSYM: return "ENOSYM";
    #endif
    #ifdef ENOSYS
        case ENOSYS: return "ENOSYS";
    #endif
    #ifdef ENOTACTIVE
        case ENOTACTIVE: return "ENOTACTIVE";
    #endif
    #ifdef ENOTBLK
        case ENOTBLK: return "ENOTBLK";
    #endif
    #ifdef ENOTCAPABLE
        case ENOTCAPABLE: return "ENOTCAPABLE";
    #endif
    #ifdef ENOTCONN
        case ENOTCONN: return "ENOTCONN";
    #endif
    #ifdef ENOTDIR
        case ENOTDIR: return "ENOTDIR";
    #endif
    #ifdef ENOTEMPT
        case ENOTEMPT: return "ENOTEMPT";
    #endif
    #ifdef ENOTEMPTY
        case ENOTEMPTY: return "ENOTEMPTY";
    #endif
    #ifdef ENOTNAM
        case ENOTNAM: return "ENOTNAM";
    #endif
    #ifdef ENOTREADY
        case ENOTREADY: return "ENOTREADY";
    #endif
    #ifdef ENOTRECOVERABLE
        case ENOTRECOVERABLE: return "ENOTRECOVERABLE";
    #endif
    #ifdef ENOTRUST
        case ENOTRUST: return "ENOTRUST";
    #endif
    #ifdef ENOTSOCK
        case ENOTSOCK: return "ENOTSOCK";
    #endif
    #ifdef ENOTSUP
        case ENOTSUP: return "ENOTSUP";
    #endif
    #ifdef ENOTSUPP
        case ENOTSUPP: return "ENOTSUPP";
    #endif
    #ifdef ENOTSYNC
        case ENOTSYNC: return "ENOTSYNC";
    #endif
    #ifdef ENOTTY
        case ENOTTY: return "ENOTTY";
    #endif
    #ifdef ENOTUNIQ
        case ENOTUNIQ: return "ENOTUNIQ";
    #endif
    #ifdef ENOUNLD
        case ENOUNLD: return "ENOUNLD";
    #endif
    #ifdef ENOUNREG
        case ENOUNREG: return "ENOUNREG";
    #endif
    #ifdef ENXIO
        case ENXIO: return "ENXIO";
    #endif
    #ifdef EOFFLOADboxDOWN
        case EOFFLOADboxDOWN: return "EOFFLOADboxDOWN";
    #endif
    #ifdef EOFFLOADboxERROR
        case EOFFLOADboxERROR: return "EOFFLOADboxERROR";
    #endif
    #ifdef EOFFLOADboxRESTART
        case EOFFLOADboxRESTART: return "EOFFLOADboxRESTART";
    #endif
    #ifdef EOPCOMPLETE
        case EOPCOMPLETE: return "EOPCOMPLETE";
    #endif
    #ifdef EOPENSTALE
        case EOPENSTALE: return "EOPENSTALE";
    #endif
    #ifdef EOPNOTSUPP
        #if !defined(ENOTSUP) || EOPNOTSUPP != ENOTSUP
        case EOPNOTSUPP: return "EOPNOTSUPP";
        #endif
    #endif
    #ifdef EOUTOFSTATE
        case EOUTOFSTATE: return "EOUTOFSTATE";
    #endif
    #ifdef EOVERFLOW
        case EOVERFLOW: return "EOVERFLOW";
    #endif
    #ifdef EOWNERDEAD
        case EOWNERDEAD: return "EOWNERDEAD";
    #endif
    #ifdef EPASSTHROUGH
        case EPASSTHROUGH: return "EPASSTHROUGH";
    #endif
    #ifdef EPATHREMOTE
        case EPATHREMOTE: return "EPATHREMOTE";
    #endif
    #ifdef EPERM
        case EPERM: return "EPERM";
    #endif
    #ifdef EPFNOSUPPORT
        case EPFNOSUPPORT: return "EPFNOSUPPORT";
    #endif
    #ifdef EPIPE
        case EPIPE: return "EPIPE";
    #endif
    #ifdef EPOWERF
        case EPOWERF: return "EPOWERF";
    #endif
    #ifdef EPROBE_DEFER
        case EPROBE_DEFER: return "EPROBE_DEFER";
    #endif
    #ifdef EPROCLIM
        case EPROCLIM: return "EPROCLIM";
    #endif
    #ifdef EPROCUNAVAIL
        case EPROCUNAVAIL: return "EPROCUNAVAIL";
    #endif
    #ifdef EPROGMISMATCH
        case EPROGMISMATCH: return "EPROGMISMATCH";
    #endif
    #ifdef EPROGUNAVAIL
        case EPROGUNAVAIL: return "EPROGUNAVAIL";
    #endif
    #ifdef EPROTO
        case EPROTO: return "EPROTO";
    #endif
    #ifdef EPROTONOSUPPORT
        case EPROTONOSUPPORT: return "EPROTONOSUPPORT";
    #endif
    #ifdef EPROTOTYPE
        case EPROTOTYPE: return "EPROTOTYPE";
    #endif
    #ifdef EPWROFF
        case EPWROFF: return "EPWROFF";
    #endif
    #ifdef EQFULL
        case EQFULL: return "EQFULL";
    #endif
    #ifdef EQSUSPENDED
        case EQSUSPENDED: return "EQSUSPENDED";
    #endif
    #ifdef ERANGE
        case ERANGE: return "ERANGE";
    #endif
    #ifdef ERECALLCONFLICT
        case ERECALLCONFLICT: return "ERECALLCONFLICT";
    #endif
    #ifdef ERECURSE
        case ERECURSE: return "ERECURSE";
    #endif
    #ifdef ERECYCLE
        case ERECYCLE: return "ERECYCLE";
    #endif
    #ifdef EREDRIVEOPEN
        case EREDRIVEOPEN: return "EREDRIVEOPEN";
    #endif
    #ifdef EREFUSED
        #if !defined(ECONNREFUSED) || EREFUSED != ECONNREFUSED
        case EREFUSED: return "EREFUSED";
        #endif
    #endif
    #ifdef ERELOC
        case ERELOC: return "ERELOC";
    #endif
    #ifdef ERELOCATED
        case ERELOCATED: return "ERELOCATED";
    #endif
    #ifdef ERELOOKUP
        case ERELOOKUP: return "ERELOOKUP";
    #endif
    #ifdef EREMCHG
        case EREMCHG: return "EREMCHG";
    #endif
    #ifdef EREMDEV
        case EREMDEV: return "EREMDEV";
    #endif
    #ifdef EREMOTE
        case EREMOTE: return "EREMOTE";
    #endif
    #ifdef EREMOTEIO
        case EREMOTEIO: return "EREMOTEIO";
    #endif
    #ifdef EREMOTERELEASE
        case EREMOTERELEASE: return "EREMOTERELEASE";
    #endif
    #ifdef ERESTART
        case ERESTART: return "ERESTART";
    #endif
    #ifdef ERESTARTNOHAND
        case ERESTARTNOHAND: return "ERESTARTNOHAND";
    #endif
    #ifdef ERESTARTNOINTR
        case ERESTARTNOINTR: return "ERESTARTNOINTR";
    #endif
    #ifdef ERESTARTSYS
        case ERESTARTSYS: return "ERESTARTSYS";
    #endif
    #ifdef ERESTART_RESTARTBLOCK
        case ERESTART_RESTARTBLOCK: return "ERESTART_RESTARTBLOCK";
    #endif
    #ifdef ERFKILL
        case ERFKILL: return "ERFKILL";
    #endif
    #ifdef EROFS
        case EROFS: return "EROFS";
    #endif
    #ifdef ERPCMISMATCH
        case ERPCMISMATCH: return "ERPCMISMATCH";
    #endif
    #ifdef ERREMOTE
        case ERREMOTE: return "ERREMOTE";
    #endif
    #ifdef ESAD
        case ESAD: return "ESAD";
    #endif
    #ifdef ESECTYPEINVAL
        case ESECTYPEINVAL: return "ESECTYPEINVAL";
    #endif
    #ifdef ESERVERFAULT
        case ESERVERFAULT: return "ESERVERFAULT";
    #endif
    #ifdef ESHLIBVERS
        case ESHLIBVERS: return "ESHLIBVERS";
    #endif
    #ifdef ESHUTDOWN
        case ESHUTDOWN: return "ESHUTDOWN";
    #endif
    #ifdef ESIGPARM
        case ESIGPARM: return "ESIGPARM";
    #endif
    #ifdef ESOCKETNOTALLOCATED
        case ESOCKETNOTALLOCATED: return "ESOCKETNOTALLOCATED";
    #endif
    #ifdef ESOCKETNOTDEFINED
        case ESOCKETNOTDEFINED: return "ESOCKETNOTDEFINED";
    #endif
    #ifdef ESOCKTNOSUPPORT
        case ESOCKTNOSUPPORT: return "ESOCKTNOSUPPORT";
    #endif
    #ifdef ESOFT
        case ESOFT: return "ESOFT";
    #endif
    #ifdef ESPIPE
        case ESPIPE: return "ESPIPE";
    #endif
    #ifdef ESRCH
        case ESRCH: return "ESRCH";
    #endif
    #ifdef ESRMNT
        case ESRMNT: return "ESRMNT";
    #endif
    #ifdef ESRVRFAULT
        case ESRVRFAULT: return "ESRVRFAULT";
    #endif
    #ifdef ESTALE
        case ESTALE: return "ESTALE";
    #endif
    #ifdef ESTRPIPE
        case ESTRPIPE: return "ESTRPIPE";
    #endif
    #ifdef ESUBTASKALREADYACTIVE
        case ESUBTASKALREADYACTIVE: return "ESUBTASKALREADYACTIVE";
    #endif
    #ifdef ESUBTASKINVALID
        case ESUBTASKINVALID: return "ESUBTASKINVALID";
    #endif
    #ifdef ESUBTASKNOTACTIVE
        case ESUBTASKNOTACTIVE: return "ESUBTASKNOTACTIVE";
    #endif
    #ifdef ESYSERROR
        case ESYSERROR: return "ESYSERROR";
    #endif
    #ifdef ETERM
        case ETERM: return "ETERM";
    #endif
    #ifdef ETIME
        case ETIME: return "ETIME";
    #endif
    #ifdef ETIMEDOUT
        case ETIMEDOUT: return "ETIMEDOUT";
    #endif
    #ifdef ETOOMANYREFS
        case ETOOMANYREFS: return "ETOOMANYREFS";
    #endif
    #ifdef ETOOSMALL
        case ETOOSMALL: return "ETOOSMALL";
    #endif
    #ifdef ETXTBSY
        case ETXTBSY: return "ETXTBSY";
    #endif
    #ifdef ETcpBadObj
        case ETcpBadObj: return "ETcpBadObj";
    #endif
    #ifdef ETcpClosed
        case ETcpClosed: return "ETcpClosed";
    #endif
    #ifdef ETcpErr
        case ETcpErr: return "ETcpErr";
    #endif
    #ifdef ETcpLinked
        case ETcpLinked: return "ETcpLinked";
    #endif
    #ifdef ETcpOutOfState
        case ETcpOutOfState: return "ETcpOutOfState";
    #endif
    #ifdef ETcpUnattach
        case ETcpUnattach: return "ETcpUnattach";
    #endif
    #ifdef EUCLEAN
        case EUCLEAN: return "EUCLEAN";
    #endif
    #ifdef EUNATCH
        case EUNATCH: return "EUNATCH";
    #endif
    #ifdef EUNKNOWN
        case EUNKNOWN: return "EUNKNOWN";
    #endif
    #ifdef EUSERS
        case EUSERS: return "EUSERS";
    #endif
    #ifdef EVERSION
        case EVERSION: return "EVERSION";
    #endif
    #ifdef EWOULDBLOCK
        #if !defined(EAGAIN) || EWOULDBLOCK != EAGAIN
        case EWOULDBLOCK: return "EWOULDBLOCK";
        #endif
    #endif
    #ifdef EWRONGFS
        case EWRONGFS: return "EWRONGFS";
    #endif
    #ifdef EWRPROTECT
        case EWRPROTECT: return "EWRPROTECT";
    #endif
    #ifdef EXDEV
        case EXDEV: return "EXDEV";
    #endif
    #ifdef EXFULL
        case EXFULL: return "EXFULL";
    #endif
    }
    return 0;
#endif /* ERRNONAME_SAFE_TO_USE_ARRAY */
}

#endif /* ERRNONAME_C */

#ifdef __cplusplus
}
#endif

#endif /** @c VIWERR_INCLUDE */
