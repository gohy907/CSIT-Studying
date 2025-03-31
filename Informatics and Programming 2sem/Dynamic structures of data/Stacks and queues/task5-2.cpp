#include <iostream>
#include <sstream>
#include <string>

template <typename T> struct Stack {
  T inf;
  Stack<T> *next;
};

template <typename T> void push(Stack<T> *&h, T x) {
  Stack<T> *r = new Stack<T>;
  r->inf = x;
  r->next = h;
  h = r;
}

template <typename T> T pop(Stack<T> *&h) {
  T i = h->inf;
  Stack<T> *r = h;
  h = h->next;
  delete r;
  return i;
}

template <typename T> T top(Stack<T> *&h) {
  T i = h->inf;
  return i;
}

template <typename T> bool empty(Stack<T> *&stack) {
  return (stack == nullptr);
}

template <typename T> void reverse_stack(Stack<T> *&stack) {
  Stack<T> *reversedStack = nullptr;

  while (!empty(stack)) {
    T tmp = pop(stack);
    push(reversedStack, tmp);
  }
  stack = reversedStack;
}

// Merges stack2 to stack1
template <typename T> void merge_stacks(Stack<T> *&stack1, Stack<T> *&stack2) {
  while (!empty(stack2)) {
    T tmp = pop(stack2);
    push(stack1, tmp);
  }
}

int main() {

  std::string line;
  getline(std::cin, line);
  // line = "h k o n a e t m l z e t";
  std::stringstream ss(line);
  int tmp;
  Stack<int> *stack = nullptr;
  while (ss >> tmp) {
    push(stack, tmp);
  }

  Stack<int> *stackTmp = nullptr;
  int max = top(stack);
  int min = top(stack);

  while (!empty(stack)) {
    int inf = pop(stack);
    if (inf > max) {
      max = inf;
    }

    if (inf < min) {
      min = inf;
    }

    push(stackTmp, inf);
  }

  while (!empty(stackTmp)) {
    int inf = pop(stackTmp);
    if (inf == max) {
      push(stack, min);
    }
    push(stack, inf);
  }

  reverse_stack(stack);

  while (!empty(stack)) {
    int tmp = pop(stack);
    std::cout << tmp << " ";
  }
}
