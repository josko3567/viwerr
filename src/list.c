#define VIWERR_REMOVE_FOR_OBJ_COMP
#include "../viwerr.h"
viwerr_package*
_viwerr_list(
        int          arg,
        char*       func,
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
         * Update once upon entering, viwerr_errno_redefine
         * calls _viwerr_list in of it self so we have to
         * be vary not to stack overflow by accident.
         */
        static bool errno_update = true;
        if(errno_update == true && !(arg & VIWERR_NO_ERRNO_TRIGGER)){
                errno_update = false;
                viwerr_errno_redefine(func,file,line);
        }
        errno_update = true;



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
                                "\tVIWERR_PUSH,  \n"
                                "\tVIWERR_POP,   \n"
                                "\tVIWERR_FLUSH, \n"
                                "\tVIWERR_PRINT, \n"
                                "\tVIWERR_OCCURED\n"
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
                                "\tVIWERR_FLUSH,\n"
                                "\tVIWERR_PRINT, \n"
                                "\tVIWERR_OCCURED\n"
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

                snprintf(packages[index]->func,
                        VIWERR_FILENAME_SIZE, "%s",
                        func != NULL ?
                                func :
                                viwerr_package_new.func
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


#ifdef VIWERR_SUBSCRIPTION_ERRNO
                if(!strncmp(packages[index]->group, "errno", 5)
                && !(arg & VIWERR_NO_ERRNO_TRIGGER)) {
                        errno = packages[index]->code;
                        if(package->name == NULL)
                                packages[index]->name = (char*)errnoname(
                                        packages[index]->code
                                );
                        if(package->message == NULL)
                                packages[index]->message = strerror(
                                        packages[index]->code
                                );
                        viwerr_errno_ignore_new(true);

                }
#endif
                return package;

        } else if( arg & VIWERR_POP
               ||  arg & VIWERR_PRINT
               ||  arg & VIWERR_OCCURED ) {

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

                        fprintf(stderr, "\nviwerr: an exception was caught!");
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
