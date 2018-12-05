#include <string.h>
#include <stdlib.h>
#include <stdio.h>



enum{
  ADD,SUB
};
enum{
  UM,DOIS
};

int func(int op, char um ,char dois);




int add(int x, int y){
  return (x+y);
}

int sub(int x, int y){
  return (x-y);
}

int func(int op, char um, char dois){
  switch (op) {
    case ADD:
      return (int) add( (int) (um - '0') ,(int) (dois - '0') );
    break;
    case SUB:
      return (int) sub( (int) (um - '0') ,(int) (dois - '0') );
    break;
  }
}
