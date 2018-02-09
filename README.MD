```
make re
gcc main.c
./run.sh ./a.out
```

creation du malloc init
106 tiny

create new tiny segfault due to ->next = NULL doesn't work


=============
debug : compiler le makefile avec -g
lldb ./a.out

env DYLD_LIBRARY_PATH=.
env DYLD_INSERT_LIBRARIES="libft_malloc.so"
env DYLD_FORCE_FLAT_NAMESPACE=1
disas
r

=============

en train de faire les larges car segfault sur les realloc large test3

// ft_putstr("\n_____vvvv_____\n");
