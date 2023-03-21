#include "../viwerr.h"
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