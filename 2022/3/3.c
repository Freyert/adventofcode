#include <stdio.h>
#include <unistd.h>

int main() {
    FILE* input = fopen("./input.txt", "r");
    char buff[50];
    int length = 0;
    //read the full buffer each time.
    while(1) {
     //https://stackoverflow.com/questions/3167298/how-can-i-convert-a-file-pointer-file-fp-to-a-file-descriptor-int-fd
     ssize_t bytesRead = read(fileno(input), buff, sizeof(buff));

     if (bytesRead <= 0) {
        break;
     }

     ssize_t i = 0;
     while (i < bytesRead) {
        length += 1;
        i += 1;
     }
    }
    printf("%d bytes\n", length);
}
