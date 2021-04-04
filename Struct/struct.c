#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define WORDS "dict.data"

struct dict {
  char en_word[100];
  char r_word[100];
};

void show_words();
int  add_word();
int  count_objects();

struct dict start;

int main() {
  int choice;

  while (choice != 0) {
    printf("1 - Ввести новое слово\n");
    printf("2 - Показать слова\n");
    printf("0 - Выход\n");
    printf("> ");
    scanf("%d", &choice);

    if (choice == 0)
      exit(0);
    else if (choice == 1)
      add_word();
    else if (choice == 2)
      show_words();
  }
}

/* Добавление нового слова в словарь */
int add_word() {
  int  fd;
  int  objects;
  char en_word[100];
  char r_word[100];

  printf("\nВведите англ слово, потом его перевод\n");
  printf("Eng: ");
  scanf("%s", en_word);
  printf("Rus: ");
  scanf("%s", r_word);

  fd = open(WORDS, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
  strcpy(start.en_word, en_word);
  strcpy(start.r_word, r_word);
  write(fd, &start, sizeof(struct dict));
  close(fd);

  printf("\nДанные успешно сохранены!\n\n");
}

/* Чтение словаря и вывод слов */
void show_words() {
  int i;
  int fd;
  int objects;
  struct dict words;

  fd = open(WORDS, O_RDONLY);

  objects = count_objects();
  if (objects == 0 || fd < 1) {
    printf("\nВаш словарь пока что пуст...\n\n");
    return;
  }

  printf("\n[ ENG ] | [ RUS ]\n");
  for (i = 0; i < objects; i++) {
    read(fd, &words, sizeof(struct dict));
    printf("%s\t|  %-25s\n", words.en_word, words.r_word);
  }
  printf("\n");
  close(fd);
}

/* Подсчёт количества слов в словаре */
int count_objects() {
  off_t size;
  struct stat st;

  if (stat(WORDS, &st) == -1)
    return st.st_size;
  size = st.st_size;

  return size/sizeof(struct dict);
}
