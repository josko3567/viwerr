#include "../viwerr.h"
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