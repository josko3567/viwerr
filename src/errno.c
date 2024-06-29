#define REMOVE_ERRNO_REDEFINE
#include "../viwerr.h"
#include <errno.h>
#include <stdbool.h>

bool viwerr_errno_ignore_new(
        bool set )
{
        static bool __set = false;
        if(set){

                __set = true;

        } else {

                if(__set == true){
                        __set = false;
                        return true;
                }

        }
        return false;
}

int * viwerr_errno_redefine(
        char*        func,
        const char * file,
        int line )
{

        static struct {

                int code;
                char * func;
                char * file;
                int line;

        } previous = {
                .code = 0,
                .func = (char*)"",
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
                previous.func = func;
                previous.line = line;
                return &errno;

        }

        if(viwerr_errno_ignore_new(false) != true){
                viwerr_file(VIWERR_PUSH|VIWERR_NO_ERRNO_TRIGGER,
                (char*)previous.func, previous.file, previous.line, &(viwerr_package){
                        .code = errno,
                        .name = (char*)errnoname(errno),
                        .message = strerror(errno),
                        .group = (char*)"errno"
                });
        }
        previous.code = errno;
        previous.file = (char*)file;
        previous.line = line;
        return &errno;

}
