#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <stdlib.h>

void usage(){
    printf("syntax : add-nbo <file1> <file2>\n");
    printf("sample : add-nbo a.bin c.bin\n");
}

uint32_t my_ntohl(uint32_t n){
    uint32_t n1 = (n & 0xff000000) >> 24;
    uint32_t n2 = (n & 0x00ff0000) >> 8;
    uint32_t n3 = (n & 0x0000ff00) << 8;
    uint32_t n4 = (n & 0x000000ff) << 24;
    return n1 | n2 | n3 | n4;
}

int main(int argc, char *argv[]) {
    if(argc!=3){
        usage();
        exit(0);
    }
    FILE *fp1 = fopen(argv[1],"rb");
    FILE *fp2 = fopen(argv[2],"rb");
    uint32_t su1=0, su2=0, sum=0;
    fread(&su1,sizeof(uint32_t),1,fp1);
    fread(&su2,sizeof(uint32_t),1,fp2);
    su1 = my_ntohl(su1);
    su2 = my_ntohl(su2);
    sum=su1+su2;

    printf("%d(0x%02x) + %d(0x%02x) = %d(0x%02x)\n", su1, su1, su2, su2, sum, sum);

    fclose(fp1);
    fclose(fp2);
}
