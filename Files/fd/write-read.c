#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100
#define SAVE "text.data"

int main() {
  int  fd;
  char buffer[SIZE];

  printf("Enter anything: ");
  fgets(buffer, SIZE, stdin);

  /* opens for writing, creates if not existing, overwrites */
  fd = open(SAVE, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);

  printf("\nRecorded: %s\n", buffer);
  printf("Input size - %ld\n", strlen(buffer));

  write(fd, &buffer, sizeof(buffer));
  close(fd);

  bzero(buffer, SIZE);

  printf("\nReading...\n");

  fd = open(SAVE, O_RDONLY);
  read(fd, (&buffer), sizeof(buffer));
  close(fd);

  printf("\nRead: %s\n", buffer);
  printf("Output size - %ld\n", strlen(buffer));
  bzero(buffer, SIZE);
}
