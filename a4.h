#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct record
{
    char *last_name;
    char *first_name;
    char *license_type;
};


struct array
{
    struct record *arr;
    int nelements;
    struct record **hash;
    int hash_size;
};

int char2int( unsigned char c );
int str2int( char *s, int max );
struct array *read_records();
void build_hash( struct array *arrptr, int hash_size );
void free_array_ptr( struct array *ptr );
struct record *find( char *key, struct array *arrptr );
