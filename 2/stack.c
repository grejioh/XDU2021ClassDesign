#include <stdio.h>
#include <stdlib.h>

const char HELP[] = "Please input operation number:\n0: push\n1: top\n2: "
                    "pop\n8: show HELP\n9: exit";
struct Stack {
  int top;
  int max_size;
  int *array; // simulate the stack with an array
};
struct Stack *initStack(int max_size) {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->max_size = max_size;
  stack->top = -1;
  stack->array = (int *)malloc(stack->max_size * sizeof(int));
  return stack;
}
int isFull(struct Stack *stack) {
  return stack->top == stack->max_size - 1 ? 1 : 0;
}
int isEmpty(struct Stack *stack) { return stack->top == -1; }
void Error() {
  printf("Somethings must be wrong!");
  exit(0);
}
int pop(struct Stack *stack) {
  if (isEmpty(stack)) {
    Error();
  }
  stack->top--;
  return stack->array[stack->top + 1];
}
int top(struct Stack *stack) {
  if (isEmpty(stack)) {
    Error();
  }
  return stack->array[stack->top];
}
void push(struct Stack *stack, int value) {
  if (isFull(stack)) {
    Error();
  }
  stack->top++;
  stack->array[stack->top] = value;
}
int main() {
  // init a stack, of which max_size == 1000;
  struct Stack *stack = initStack(1000);
  printf("%s", HELP);
  while (1) {
    int op, temp;
    printf(">>");
    scanf("%d", &op);
    switch (op) {
    case 0:
      scanf("%d", &temp);
      push(stack, temp);
      break;
    case 1:
      top(stack);
      break;
    case 2:
      pop(stack);
      break;
    case 9:
      return 0;
    default:
      printf("%s", HELP);

      printf(">> ");
    }
  }
  return 0;
}
