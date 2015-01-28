Print the size of various types in C
==========

Magic macro:

```C
#define PRINT_SIZEOF(x) \
    printf("sizeof("#x") = %d\n", sizeof(x));
```
