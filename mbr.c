/*

mbr.c - read/write a master boot record from/to a disk

mbr <input> <output>

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: mbr <input> <output>\n");
        exit(1);
    }

    FILE *ifp, *ofp;
    const char *ifn = argv[1], *ofn = argv[2];

    uint8_t buffer[512];
    memset(buffer, 0, sizeof (buffer));

    ifp = fopen(ifn, "r");

    if (ifp == NULL) {
        printf("Could not open %s\n", ifn);
        exit(1);
    }

    fread(buffer, 1, sizeof (buffer), ifp);

    uint16_t magic = 0xaa55;
    uint16_t proposed = 0;
    memcpy(&proposed, (uint16_t*)&buffer[510], sizeof (uint16_t));
    if (proposed != magic) {
        printf("Invalid boot record");
        exit(1);
    }

    ofp = fopen(ofn, "w");

    if (ofp == NULL) {
        printf("Could not create file %s\n", ofn);
        exit(1);
    }

    fwrite(buffer, 1, sizeof (buffer), ofp);

    close(ifp);
    close(ofp);

    return 0;
}
