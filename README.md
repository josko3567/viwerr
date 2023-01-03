# Description

`viwerr.h` is a simple error catching library, compatible with errno.

# Syntax & Logic

## Packages...

`viwerr` operates with packets called `viwerr_package`'s that store our error information:
  - Error code. ➔ `.code = EINVAL` 
  - Name of the error. ➔ `.name = (char*)"EINVAL"` 
  - Error message. ➔ `.message = (char*)"Invalid arguments"`
  - Group of errors it belongs to. ➔ `.group = (char*)"errno"`

Packages can be created on the spot using [compound literals](https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html).

For example this is a package `ENOMEM` would push:

```C
&(viwerr_package){
        .code = ENOMEM,
        .name = (char*)"ENOMEM",
        .message = (char*)"Not enough space/cannot allocate memory"
        .group = (char*)"errno"
}
```

`viwerr` automaticly stores the line and file it was called from to `.line` and `.file`.

## `viwerr()` function...

The basic syntax of the function `viwerr` is as follows:

```C
viwerr(<ARGUMENT>, <PACKAGE/NULL>);
```

There are 4 main arguments that can be given to `viwerr`:
  - `VIWERR_PUSH`
  - `VIWERR_POP`
  - `VIWERR_PRINT`
  - `VIWERR_OCCURED`
  - `VIWERR_FLUSH`


`VIWERR_PUSH` pushes a new packet onto the package stack:

```C
viwerr(VIWERR_PUSH, &(viwerr_package){
  .code = 15,
  .name = (char*)"BMPCOR",
  .message = (char*)"Bitmap file header has corrupted information!",
  .group = (char*)"bmp.h"

});
```

`VIWERR_POP` pops the latest error package given to `viwerr` & removes it from the package stack:

```C
/* __VA_ARG__ requires atleast 1 argument, therefore when we are not required to give a package we give it NULL as that one argument. */
viwerr_package * package = viwerr(VIWERR_POP, NULL);
```

`VIWERR_PRINT` pops the latest error package given to `viwerr` & removes it from the package stack while also printing the contents of the package if it exists:

```C
viwerr(VIWERR_PUSH, &(viwerr_package){
  .code = 15,
  .name = (char*)"BMPCOR",
  .message = (char*)"Bitmap file header has corrupted information!",
  .group = (char*)"bmp.h"

});
viwerr_package * package = viwerr(VIWERR_PRINT, NULL);
```

```
> cc test.c
> ./a.out
_____________________________________
  VIWERR CAUGHT AN EXCEPTION: 
        code     : 15
        name     : BMPCOR
        message  : Bitmap file header has corrupted information!
        group    : bmp.h
        file     : test.c
        line     : 10
_____________________________________
```

`VIWERR_OCCURED` pops the latest error package given to `viwerr` without removing the package from the stack:

```C
if( viwerr(VIWERR_OCCURED, NULL) != NULL ) {

        /* ... */

}
```

`VIWERR_FLUSH` flushes the all packages from the `viwerr` stack.

```C
viwerr(VIWERR_PUSH, &(viwerr_package){
  .code = 15,
  .name = (char*)"BMPCOR",
  .message = (char*)"Bitmap file header has corrupted information!",
  .group = (char*)"bmp.h"

});

viwerr(VIWERR_FLUSH, NULL);

viwerr_package * package = viwerr(VIWERR_PRINT, NULL);

if(package == NULL) {

        printf("No package!");

}
```

```
> cc test.c
> ./a.out
No package!
```

In addition to the 5 main arguments `VIWERR_POP`, `VIWERR_PRINT`, `VIWERR_OCCURED` & `VIWERR_FLUSH` can be combined with the following arguments to control what packages we want to return:

  - `VIWERR_BY_CODE`
  - `VIWERR_BY_NAME`
  - `VIWERR_BY_MESSAGE`
  - `VIWERR_BY_GROUP`

To give one example, if we combine `VIWERR_BY_GROUP` with `VIWERR_OCCURED`, the package that `viwerr` returns must be from a specific `group` of errors that we specifiy in the `viwerr_package` that we pass as our varadict argument:
```C
viwerr(VIWERR_PUSH, &(viwerr_package){
  .code = 15,
  .name = (char*)"BMPCOR",
  .message = (char*)"Bitmap file header has corrupted information!",
  .group = (char*)"bmp.h"

});

/* Check if errno was set! */
if(viwerr(VIWERR_OCCURED|VIWERR_BY_GROUP, &(viwerr_package){
        .group = (char*)"errno"
})) {

        printf("errno was set!");

} else {

        printf("errno was not set!")

}
```
```
> cc test.c
> ./a.out
errno was not set!
```

We can use multiple `VIWERR_BY_...` arguments in one `viwerr` call.

## `errno` compatiblity...
If `VIWERR_SUBSCRIPTION_ERRNO` is defined before including `viwerr.h` as follows...
```C
#define VIWERR_SUBSCRIPTION_ERRNO
#include "viwerr.h"
```
...`viwerr` will track all changes to the errno variable, albeit not as precise as id like (reason why after example):

```C
errno = ENOMEM;
errno = EINVAL;

while(viwerr(VIWERR_OCCURED|VIWERR_BY_GROUP, &(viwerr_package){
        .group = (char*)"errno"
})) {

        viwerr(VIWERR_PRINT,|VIWERR_BY_GROUP, &(viwerr_package){
                .group = (char*)"errno"
        });

}
```

```
> cc test.c
> ./a.out
_____________________________________
  VIWERR CAUGHT AN EXCEPTION: 
        code     : 22
        name     : EINVAL
        message  : Invalid argument
        group    : errno
        file     : test.c
        line     : 11
_____________________________________

_____________________________________
  VIWERR CAUGHT AN EXCEPTION: 
        code     : 12
        name     : ENOMEM
        message  : Cannot allocate memory
        group    : errno
        file     : test.c
        line     : 10
_____________________________________
```

The only problem with it is if there are multiple calls that set errno to the same specific value we cannot report on them, we only can only know where errno was set to some specific value first.

```C
errno = ENOMEM;
errno = ENOMEM;
errno = EINVAL;
errno = EINVAL;

while(viwerr(VIWERR_OCCURED|VIWERR_BY_GROUP, &(viwerr_package){
        .group = (char*)"errno"
})) {

        viwerr(VIWERR_PRINT,|VIWERR_BY_GROUP, &(viwerr_package){
                .group = (char*)"errno"
        });

}
```

```
> cc test.c
> ./a.out
_____________________________________
  VIWERR CAUGHT AN EXCEPTION: 
        code     : 22
        name     : EINVAL
        message  : Invalid argument
        group    : errno
        file     : test.c
        line     : 11
_____________________________________

_____________________________________
  VIWERR CAUGHT AN EXCEPTION: 
        code     : 12
        name     : ENOMEM
        message  : Cannot allocate memory
        group    : errno
        file     : test.c
        line     : 10
_____________________________________
```

There should be 4 exceptions caught but `viwerr` can only catch 2 because we cannot know if a variable is being written to or read from in `C`.

# External libraries used...

[`mentalisttraceur/errnoname`](https://github.com/mentalisttraceur/errnoname)

  - `errnoname()` ➔ a function that helps us get the symbolic name of each `errno` value.
