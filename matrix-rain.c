#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

char *build_col_line(int len) {
  // makes a single line
  int i = 0;
  char *line = malloc(sizeof(char) * (len + 1));
  while (i < len) {
    if ((i % 2) == 0) {
      strcat(line, " ");
    } else {
      int num = (rand() % 2);
      char entry[2];
      sprintf(entry, "%d", num);
      strcat(line, entry);
    }
    i++;
  }
  return line;
  free(line);
}

char **build_matrix(int width, int height) {
  // sets up the grid
  int i = 0;
  char **matrix = malloc(sizeof(char) * ((width + 1) * height));
  while (i < (height - 2)) {
    matrix[i] = build_col_line(width);
    i++;
  }
  return matrix;
}

char **cycle_matrix(char **matrix, int height, int width) {
  int i = (height - 2);
  while (i > 0) {
    int j = (i - 1);
    matrix[i] = matrix[j];
    i--;
  }
  matrix[0] = build_col_line(width);
  return matrix;
}

void clear_screen() { puts("\e[2J\e[H"); }

int main(int argc, char const *argv[]) {
  // randomize seed
  srand(time(0));

  // get the terminal details
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  char **grid = build_matrix(w.ws_col, w.ws_row);

  // print it
  puts("\e[01;32;40m");
  while (1) {
    clear_screen();
    int i = 0;
    while (i < (w.ws_row - 2)) {
      puts(grid[i]);
      i++;
    }
    grid = cycle_matrix(grid, w.ws_row, w.ws_col);
    usleep(100000);
  }

  return 0;
}
