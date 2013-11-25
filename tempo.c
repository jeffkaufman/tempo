#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

#define SAMPLES 16

double current_minute() {
  struct timeval te;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime = 0;
  
  int ok = gettimeofday(&te, &tz);
  if (ok == -1) {
    printf("error in gettimeofday\n");
    exit(1);
  }

  double sec = te.tv_sec;
  double usec = te.tv_usec;

  return (sec + (usec / 1000 / 1000)) / 60;  
}

char* zero[] = {
  "    0000    ",
  "  00    00  ",
  " 0        0 ",
  " 0        0 ",
  " 0        0 ",
  " 0        0 ",
  " 0        0 ",
  "  00    00  ",
  "    0000    ",
};

char* one[] = {
  "    111     ",
  "      1     ",
  "      1     ",
  "      1     ",
  "      1     ",
  "      1     ",
  "      1     ",
  "      1     ",
  "    11111   ",
};


char* two[] = {
  "   22222    ",
  "  2     2   ",
  "        2   ",
  "        2   ",
  "       2    ",
  "     22     ",
  "    2       ",
  "   2        ",
  "  2222222   ",
};

char* three[] = {
  "   33333    ",
  "  3     3   ",
  "         3  ",
  "         3  ",
  "       33   ",
  "         3  ",
  "         3  ",
  "  3     3   ",
  "   33333    ",
};


char* four[] = {
  "        44  ",
  "       4 4  ",
  "      4  4  ",
  "     4   4  ",
  "    4    4  ",
  "   4     4  ",
  "  44444444  ",
  "         4  ",
  "         4  ",
};


char* five[] = {
  " 555555555  ",
  " 5          ",
  " 5          ",
  " 5555555    ",
  "        55  ",
  "          5 ",
  "          5 ",
  " 55     55  ",
  "   55555    ",
};

char* six[] = {
  "       666  ",
  "     66     ",
  "   66       ",
  "  6         ",
  " 6   6666   ",
  " 6  6    6  ",
  " 6        6 ",
  "  66    66  ",
  "    6666    ",
};

char* seven[] = {
  "  77777777  ",
  "         7  ",
  "        7   ",
  "       7    ",
  "    77777   ",
  "     7      ",
  "    7       ",
  "   7        ",
  "  7         ",
};

char* eight[] = {
  "   88888    ",
  "  8     8   ",
  " 8       8  ",
  "  8     8   ",
  "   88888    ",
  "  8     8   ",
  " 8       8  ",
  "  8     8   ",
  "   88888    ",
};

char* nine[] = {
  "    99999   ",
  "   9     9  ",
  "  9       9 ",
  "   9     9  ",
  "    999999  ",
  "        9   ",
  "      99    ",
  "     9      ",
  "   99       ",
};

char** digits[] = {zero, one, two, three, four, five, six, seven, eight, nine};

void display_tempo(int n) {
  if (n > 999 || n < 0) {
    printf("%d\n", n);
    return;
  }

  int digit1 = n/100 % 10;
  int digit2 = n/10 % 10;
  int digit3 = n % 10;

  int i;
  for (i = 0 ; i < 100 ; i++) {
    printf("\n");
  }

  int row;
  for (row = 0 ; row < 9 ; row++) {
    printf("%s    %s     %s\n",
           digits[digit1][row],
           digits[digit2][row],
           digits[digit3][row]);
  }
}

   
int main(int argc, char** argv) {
  double ts[SAMPLES];
  int pos = 0;

  char c;
  while(1) {
    read(1, &c, 1);
    ts[pos % SAMPLES] = current_minute();
    if (pos > SAMPLES) {
       int tempo = (SAMPLES-1)/(
          ts[pos % SAMPLES] -
          ts[(pos+1) % SAMPLES]) + 0.5;
       display_tempo(tempo);
    }
    
    pos++;
  }
}
