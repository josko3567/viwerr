#include <stdlib.h>
#include "../viwerr.h"
viwerr_package**
_viwerr_list_init(
        void )
{


        static viwerr_package **array = NULL;
        /*viwerr_package *empty_package = viwerr_package_empty;*/

        if( array == NULL ) {

                //errno = 0;

                array = (viwerr_package**)malloc(
                        sizeof(viwerr_package) * VIWERR_PACKAGE_AMOUNT
                );

                /**
                 * @brief
                 * Exit with code VIWERR_EXIT_CODE if we failed
                 * to allocate memory for our error packages.
                 */
                if( array == NULL ) {
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
                                .func = calloc(
                                        VIWERR_FUNCTION_SIZE,
                                        sizeof(char)),
                                .line = viwerr_package_empty.line,
				.flag = {
					.returned = viwerr_package_empty.flag.returned,
					.printed  = viwerr_package_empty.flag.printed,
					.contains = viwerr_package_empty.flag.contains,
				}
                                // .flag.returned =
                                        // viwerr_package_empty.flag.returned,
                                // .flag.printed  =
                                        // viwerr_package_empty.flag.printed,
                                // .flag.contains =
                                        // viwerr_package_empty.flag.contains,
                                },
                                sizeof(viwerr_package)
                        );

                        if( array[i]->name    == NULL
                        ||  array[i]->message == NULL
                        ||  array[i]->group   == NULL
                        ||  array[i]->file    == NULL ) {

                            exit(VIWERR_EXIT_CODE);

                        }

                }

        }

        return array;

}
