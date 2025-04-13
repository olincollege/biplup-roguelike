#include "util.h"

dir *make_dir() { return (dir *)malloc(sizeof(dir)); }

void free_dir(dir *to_free) { free(to_free); }
