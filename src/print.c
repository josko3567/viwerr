#include "../viwerr.h"
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