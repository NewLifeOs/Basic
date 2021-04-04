#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int main() {
  FILE *fptr;
  char buffer[SIZE];

  if ((fptr = fopen("text.txt", "r")) == NULL) {
    printf("Не могу открыть файл\n");
    exit(1);
  }

  fscanf(fptr, "%[^\n]", buffer);

  printf("Прочитано из файла: \n%s\n", buffer);
  fclose(fptr);

  return 0;
}
