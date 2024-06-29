#include "../viwerr.h"

void _viwerr_print_package(viwerr_package* package) {

    fprintf(stderr, "\n");
    fprintf(
        stderr,
        "Inside of '%s', function '%s' on line '%d' returned the following "
        "exception:\n",
        package->file,
        package->func,
        package->line
    );
    fprintf(
        stderr,
        "\t%s: %s (code: %d%s)\n",
        package->name,
        package->message,
        package->code,
        package->code == viwerr_package_empty.code ? " [defualt]" : ""
    );

}
