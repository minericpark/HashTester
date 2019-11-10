#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "a4.h"

#include <ctype.h>

#define BUFFER_SIZE    1024

unsigned long collisions;
unsigned long duplicates;
unsigned long collisions_license;
unsigned long duplicates_license;
unsigned long collisions_issue;
unsigned long duplicates_issue;

int char2int(unsigned char c) {
    if (isupper(c)) {
        return (int) (c - 'A');
    }
    if (islower(c)) {
        return (int) (c - 'a');
    }
    return 26;
}

int hash1(char *s, int max) {
    char *c;
    unsigned long new;
    unsigned long hashMultiplier = 33;
    unsigned long initialValue = 5381;
    unsigned long hashValue = 5405931;
    unsigned long hashValue2 = 4324321;
    unsigned long hashValue3 = 12341;
    new = initialValue;

    for (c = s; (*c); c++) {
        new = new ^ char2int(*c);
        new = new ^ hashMultiplier;
        new = new * hashMultiplier;
        new = new % max;
    }

    if (new == (max - 1)) {
        new - 1;
    }

    return (int) new;
}

int backUp(char *s, int max) {
    char *c;
    unsigned long number, column, new;
    int hashMultiplier = 33;
    int initialValue = 5381;
    int i = 0;
    new = initialValue;

    for (c = s; (*c); c++) {
        new = ((new * hashMultiplier) + char2int(*c));
    }

    return (int) new % max;
}

int hash2(char *s, int max) {
    char *c;
    unsigned long new;
    unsigned long hashMultiplier = 33;
    unsigned long initialValue = 5381;
    new = initialValue;

    for (c = s; (*c); c++) {
        new = new * hashMultiplier;
        new = new + char2int(*c);
        new = new % max;
    }

    if (new == (max - 1)) {
        new - 1;
    }

    return (int) new;
}

int hash3(char *s, int max) {
    char *c;
    unsigned long new;
    unsigned long hashMultiplier = 33;
    unsigned long initialValue = 5381;
    new = initialValue;

    for (c = s; (*c); c++) {
        new = new * hashMultiplier;
        new = new + char2int(*c);
        new = new % max;
    }

    if (new == (max - 1)) {
        new - 1;
    }

    return (int) new;
}

struct array *read_records() {
    char buffer[BUFFER_SIZE];

    struct array *arrptr;

    FILE *fp;

    int line, start, end;

    arrptr = malloc(sizeof(struct array));
    arrptr->nelements = 0;

    fp = fopen("Professional_and_Occupational_Licensing.csv", "r");
    fgets(buffer, BUFFER_SIZE, fp);

    while (!feof(fp)) {
        if (fgets(buffer, BUFFER_SIZE, fp) == NULL) {
            break;
        }

        if (strlen(buffer) == BUFFER_SIZE - 1) {
            fprintf(stderr, "Error:  BUFFER TOO SMALL\n");
            exit(-1);
        }

        (arrptr->nelements)++;
    }

    arrptr->arr = malloc(sizeof(struct record) * (arrptr->nelements));

    fseek(fp, 0, SEEK_SET);

    fgets(buffer, BUFFER_SIZE, fp);
    for (line = 0; line < arrptr->nelements; line++) {
        fgets(buffer, BUFFER_SIZE, fp);

        start = 0;
        for (end = start; buffer[end] != ','; end++);    /* find next comma */

        (arrptr->arr)[line].last_name = malloc(end - start + 1);
        strncpy((arrptr->arr)[line].last_name, buffer + start, end - start);
        (arrptr->arr)[line].last_name[end - start] = '\0';/*
        printf("Last name: %s\n", (arrptr->arr)[line].last_name);*/

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        (arrptr->arr)[line].first_name = malloc(end - start + 1);
        strncpy((arrptr->arr)[line].first_name, buffer + start, end - start);
        (arrptr->arr)[line].first_name[end - start] = '\0';/*
        printf("First name: %s\n", (arrptr->arr)[line].first_name);*/

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        (arrptr->arr)[line].license_no = malloc(end - start + 1);
        strncpy((arrptr->arr)[line].license_no, buffer + start, end - start);
        (arrptr->arr)[line].license_no[end - start] = '\0';/*
        printf("License no: %s\n", (arrptr->arr)[line].license_no);*/

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        (arrptr->arr)[line].license_type = malloc(end - start + 1);
        strncpy((arrptr->arr)[line].license_type, buffer + start, end - start);
        (arrptr->arr)[line].license_type[end - start] = '\0';/*
        printf("License type: %s\n", (arrptr->arr)[line].license_type);*/

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        start = end + 1;
        for (end = start; buffer[end] != ','; end++); /* find next comma */

        (arrptr->arr)[line].issue_date = malloc(end - start + 1);
        strncpy((arrptr->arr)[line].issue_date, buffer + start, end - start);
        (arrptr->arr)[line].issue_date[end - start] = '\0';/*
        printf("Issue date: %s\n", (arrptr->arr)[line].issue_date);*/

    }

    return arrptr;
}


void build_hash(struct array *arrptr, int hash_size) {
    int idx, line;
    int duplicate;

    arrptr->hash_size = hash_size;
    arrptr->hash = malloc(sizeof(struct record *) * arrptr->hash_size);

    for (idx = 0; idx < arrptr->hash_size; idx++) {
        (arrptr->hash)[idx] = NULL;
    }

    for (line = 0; line < arrptr->nelements; line++) {/*
        printf( "%d Adding %s\n", line, (arrptr->arr)[line].last_name );*/
        idx = hash1((arrptr->arr)[line].last_name, arrptr->hash_size);

        duplicate = 0;
        while ((arrptr->hash)[idx] != NULL) {
            if (strcmp(((arrptr->hash)[idx])->last_name,
                       (arrptr->arr)[line].last_name) == 0) {
                /*printf( "  Skipping duplicate\n" );*/
                duplicates++;
                duplicate = 1;
                break;
            }/*
            printf("  collision at %d %s\n", idx, ((arrptr->hash)[idx])->last_name);*/
            collisions++;
            idx++;
            if (idx >= arrptr->hash_size) {
                idx = 0;
            }

        }
        if (!duplicate) {/*
            printf("  inserting at %d\n", idx);*/
            (arrptr->hash)[idx] = (arrptr->arr) + line;
        }
    }

}

void build_hash_license(struct array *arrptr, int hash_size) {
    int idx, line;
    int duplicate;

    arrptr->hash_size = hash_size;
    arrptr->hash = malloc(sizeof(struct record *) * arrptr->hash_size);

    for (idx = 0; idx < arrptr->hash_size; idx++) {
        (arrptr->hash)[idx] = NULL;
    }

    for (line = 0; line < arrptr->nelements; line++) {/*
        printf( "%d Adding %s\n", line, (arrptr->arr)[line].last_name );*/
        idx = hash2((arrptr->arr)[line].license_no, arrptr->hash_size);

        duplicate = 0;
        while ((arrptr->hash)[idx] != NULL) {
            if (strcmp(((arrptr->hash)[idx])->license_no,
                       (arrptr->arr)[line].license_no) == 0) {
                /*printf( "  Skipping duplicate\n" );*/
                duplicates_license++;
                duplicate = 1;
                break;
            }/*
            printf("  collision at %d %s\n", idx, ((arrptr->hash)[idx])->last_name);*/
            collisions_license++;
            idx++;
            if (idx >= arrptr->hash_size) {
                idx = 0;
            }

        }
        if (!duplicate) {/*
            printf("  inserting at %d\n", idx);*/
            (arrptr->hash)[idx] = (arrptr->arr) + line;
        }
    }

}

void build_hash_issue(struct array *arrptr, int hash_size) {
    int idx, line;
    int duplicate;

    arrptr->hash_size = hash_size;
    arrptr->hash = malloc(sizeof(struct record *) * arrptr->hash_size);

    for (idx = 0; idx < arrptr->hash_size; idx++) {
        (arrptr->hash)[idx] = NULL;
    }

    for (line = 0; line < arrptr->nelements; line++) {/*
        printf( "%d Adding %s\n", line, (arrptr->arr)[line].last_name );*/
        idx = hash3((arrptr->arr)[line].issue_date, arrptr->hash_size);

        duplicate = 0;
        while ((arrptr->hash)[idx] != NULL) {
            if (strcmp(((arrptr->hash)[idx])->issue_date,
                       (arrptr->arr)[line].issue_date) == 0) {
                /*printf( "  Skipping duplicate\n" );*/
                duplicates_issue++;
                duplicate = 1;
                break;
            }/*
            printf("  collision at %d %s\n", idx, ((arrptr->hash)[idx])->last_name);*/
            collisions_issue++;
            idx++;
            if (idx >= arrptr->hash_size) {
                idx = 0;
            }

        }
        if (!duplicate) {/*
            printf("  inserting at %d\n", idx);*/
            (arrptr->hash)[idx] = (arrptr->arr) + line;
        }
    }

}

void free_array_ptr(struct array *ptr) {
    int i;

    for (i = 0; i < ptr->nelements; i++) {
        free(ptr->arr[i].last_name);
        free(ptr->arr[i].first_name);
        free(ptr->arr[i].license_type);
        free(ptr->arr[i].license_no);
        free(ptr->arr[i].issue_date);
    }

    free(ptr->arr);
    free(ptr->hash);

    free(ptr);
}

struct record *find(char *key, struct array *arrptr) {
    int idx;

    idx = hash1(key, arrptr->hash_size);
    while ((arrptr->hash)[idx] != NULL) {
        if (strcmp(key, ((arrptr->hash)[idx])->last_name) == 0) {
            return (arrptr->hash)[idx];
        }
        idx++;

        if (idx >= (arrptr->hash_size)) {
            idx = 0;
        }
    }
    return NULL;

}

struct record *find_license(char *key, struct array *arrptr) {
    int idx;

    idx = hash2(key, arrptr->hash_size);
    while ((arrptr->hash)[idx] != NULL) {
        if (strcmp(key, ((arrptr->hash)[idx])->license_no) == 0) {
            return (arrptr->hash)[idx];
        }
        idx++;

        if (idx >= (arrptr->hash_size)) {
            idx = 0;
        }
    }
    return NULL;

}

struct record *find_issue(char *key, struct array *arrptr) {
    int idx;

    idx = hash3(key, arrptr->hash_size);
    while ((arrptr->hash)[idx] != NULL) {
        if (strcmp(key, ((arrptr->hash)[idx])->issue_date) == 0) {
            return (arrptr->hash)[idx];
        }
        idx++;

        if (idx >= (arrptr->hash_size)) {
            idx = 0;
        }
    }
    return NULL;

}


int main() {
    struct array *arrptr;
    struct array *licensePtr;
    struct array *issuePtr;
/*  int line; */
    struct record *r;

    collisions = 0;
    duplicates = 0;

    arrptr = read_records();
    licensePtr = read_records();
    issuePtr = read_records();
    printf ("created all records\n");

    build_hash(arrptr, 500000);
    printf ("built last name hash\n");
    build_hash_license(licensePtr, 500000);
    printf ("built license no hash\n");
    build_hash_issue(issuePtr, 500000);
    printf ("built issuedate hash\n");

/*
  for (line=0;line<arrptr->nelements;line++)
  {
    printf( " %d %s, %s: %s %d\n", line,
	                    (arrptr->arr)[line].last_name,
	                    (arrptr->arr)[line].first_name,
			    (arrptr->arr)[line].license_type,
       			    str2int( (arrptr->arr)[line].last_name, 100 ) );
  }
*/

    printf ("last name hash\n");
    printf("Duplicates: %ld\n", duplicates);
    printf("Collisions: %ld\n\n", collisions);
    printf ("license hash\n");
    printf("Duplicates: %ld\n", duplicates_license);
    printf("Collisions: %ld\n\n", collisions_license);
    printf ("issue date hash\n");
    printf("Duplicates: %ld\n", duplicates_issue);
    printf("Collisions: %ld\n", collisions_issue);

/*
    r = find("Kremer", arrptr);
    if (r == NULL) {
        printf("Not found\n");
    } else {
        printf("%s, %s : %s\n", r->last_name,
               r->first_name,
               r->license_type);
    }
    r = find_license("RN-0012312", licensePtr);
    if (r == NULL) {
        printf("Not found\n");
    } else {
        printf("%s, %s : %s\n", r->last_name,
               r->first_name,
               r->license_type);
    }
    r = find_issue("04/19/2012", issuePtr);
    if (r == NULL) {
        printf("Not found\n");
    } else {
        printf("%s, %s : %s\n", r->last_name,
               r->first_name,
               r->license_type);
    }
*/
    free_array_ptr(arrptr);
    free_array_ptr(licensePtr);
    free_array_ptr(issuePtr);
    return 0;
}
