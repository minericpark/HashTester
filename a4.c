/* Eric Minseo Park
 * 1001018
 * epark03@uoguelph.ca
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "a4.h"

/*E.g. Harrison*/
/*This hash function is based on the Multiplicative String Hash function introduced in ZyBooks 5.7: Common Hash Functions:
 * https://learn.zybooks.com/zybook/UOGUELPHCIS2520KremerFall2019/chapter/5/section/7
 * Also follows the structure of the york provided example:
 * http://www.cse.yorku.ca/~oz/hash.html */
int hash1(char *string, int hash_size) {
    int index;
    unsigned long new;
    unsigned long initialValue = 5381;
    new = initialValue;

    while ((index = *string++)) {
        new = ((new << 5) + new) + index;
    }
    new ^= index + 3;
    new = new % hash_size;

    return (int) new;
}

/*E.G. CD-123432*/
/*This hash function is based on the Multiplicative String Hash function introduced in ZyBooks 5.7: Common Hash Functions:
 * https://learn.zybooks.com/zybook/UOGUELPHCIS2520KremerFall2019/chapter/5/section/7
 * Also follows the structure of the york provided example of djb2:
 * http://www.cse.yorku.ca/~oz/hash.html */
int hash2(char *string, int hash_size) {
    int index;
    unsigned long new, temp;
    unsigned long initialValue = 5381;
    new = initialValue;

    while ((index = *string++)) {
        new = ((new << 5) + new) + index;
        temp = ((((new << 5) + new) + index + 2) << 11) ^ new;
        new = (new << 16) ^ temp;
        new += new >> 11;
        new ^= new << 25;
        new += new << 3;
    }
    new ^= index + 25;
    new = new % hash_size;

    return (int) new;
}

/*E.g. 03/01/1000*/
/*This hash function is based on the Multiplicative String Hash function introduced in ZyBooks 5.7: Common Hash Functions:
 * https://learn.zybooks.com/zybook/UOGUELPHCIS2520KremerFall2019/chapter/5/section/7
 * Also follows the structure of the york provided example:
 * http://www.cse.yorku.ca/~oz/hash.html */
int hash3(char *string, int hash_size) {
    int index;
    unsigned long new;
    unsigned long initialValue = 5381;
    new = initialValue;

    while ((index = *string++)) {
        new = ((new << 5) + new) + index;
    }
    new += new >> 16;
    new ^= index << 19;

    new = new % hash_size;

    return (int) new;
}
