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
  char tmp;
  Stack<char> *stack = nullptr;
  while (ss >> tmp) {
    push(stack, tmp);
  }

  std::string vowels = "eyuioa";
  Stack<char> *stackVowels = nullptr;
  Stack<char> *stackConsonants = nullptr;

  while (!empty(stack)) {
    char tmp;
    tmp = pop(stack);
    if (vowels.find_first_of(tmp) != std::string::npos) {
      push(stackVowels, tmp);
    } else {
      push(stackConsonants, tmp);
    }
  }

  merge_stacks(stack, stackVowels);
  merge_stacks(stack, stackConsonants);

  reverse_stack(stack);

  while (!empty(stack)) {
    char tmp;
    tmp = pop(stack);
    std::cout << tmp << " ";
  }
  std::cout << std::endl;
}
