/* Eric Minseo Park
 * 1001018
 * epark03@uoguelph.ca
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct record
{
    char *last_name;
    char *first_name;
    char *license_no;
    char *license_type;
    char *issue_date;
};


struct array
{
    struct record *arr;
    int nelements;
    struct record **hash;
    int hash_size;
};

int hash1(char *string, int hash_size);
int hash2(char *string, int hash_size);
int hash3(char *string, int hash_size);
int char2int( unsigned char c );
int str2int( char *s, int max );
struct array *read_records();
void build_hash( struct array *arrptr, int hash_size );
void free_array_ptr( struct array *ptr );
struct record *find( char *key, struct array *arrptr );
