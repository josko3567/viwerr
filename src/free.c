#include <stdlib.h>
#include "../viwerr.h"
void
#ifdef __GNUC__
__attribute__((destructor))
#endif
_viwerr_list_free(
    void )
{
        
        viwerr_package ** array = _viwerr_list_init();

        int i;
        for( i = 0; i < (int)VIWERR_PACKAGE_AMOUNT; i++ ) {

                free(array[i]->name);
                free(array[i]->message);
                free(array[i]->group);
                free(array[i]->file);
                free(array[i]);

        }

        free(array);
        return;

}

