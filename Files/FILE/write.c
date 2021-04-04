#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

int main() {
  FILE *fptr;
  char buffer[SIZE];
  char verification[1024];

  fptr = fopen("text.txt", "a");
  if (fptr == NULL) {
    printf("Error\n");
    exit(0);
  }

  printf("Введите что-нибудь: ");
  fgets(verification, 1024, stdin);

  if (strlen(verification) > SIZE) {
    printf("\nРазрешенный размер введенных символов (данных) - %d, а не %ld!\n",
    SIZE, strlen(verification));
    exit(0);
  } else {
    strcpy(buffer, verification);
    fprintf(fptr, "%s", buffer);
    fclose(fptr);
  }

  printf("\nВы ввели - %s\n", buffer);
  printf("Размер строки составил - %ld\n", strlen(buffer));

  bzero(buffer, SIZE);
  printf("Размер обнуленной строки составил - %ld\n", strlen(buffer));
}
