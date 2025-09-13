#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

template <typename T> struct Queue {
  T inf;
  Queue<T> *next;
};

template <typename T> void push(Queue<T> *&h, Queue<T> *&t, T x) {
  Queue<T> *r = new Queue<T>;
  r->inf = x;
  r->next = nullptr;
  if (!h && !t) {
    h = t = r;
  }

  else {
    t->next = r;
    t = r;
  }
}

template <typename T> T pop(Queue<T> *&h, Queue<T> *&t) {
  T i = h->inf;
  Queue<T> *r = h;
  h = h->next;
  if (!h) {
    t = nullptr;
  }
  delete r;
  return i;
}

template <typename T> T top(Queue<T> *&h) {
  T i = h->inf;
  return i;
}

template <typename T> bool empty(Queue<T> *&h) { return (h == nullptr); }

int main() {

  std::string line;
  getline(std::cin, line);
  // line = "h k o n a e t m l z e t";
  std::stringstream ss(line);
  int tmp;
  Queue<int> *queueH = nullptr;
  Queue<int> *queueT = nullptr;
  while (ss >> tmp) {
    push(queueH, queueT, tmp);
  }

  int min = top(queueH);
  Queue<int> *queueTmpH = nullptr;
  Queue<int> *queueTmpT = nullptr;
  while (!empty(queueH)) {
    int inf = pop(queueH, queueT);
    if (inf < min) {
      min = inf;
    }
    push(queueTmpH, queueTmpT, inf);
  }

  // reverse_queue(queueH, queueT);
  bool found = false;
  int index = 0;
  int i = 0;
  while (!empty(queueTmpH)) {
    int inf = pop(queueTmpH, queueTmpT);
    if (inf == min) {
      index = i;
    }
    ++i;
    if (!found && inf == min) {
      found = true;
      continue;
    }
    push(queueH, queueT, inf);
  }
  --index;
  i = 0;
  while (!empty(queueH)) {
    int inf = pop(queueH, queueT);
    if (i != index) {
      push(queueTmpH, queueTmpT, inf);
    }
    ++i;
  }

  // reverse_queue(queueTmpH, queueTmpT);

  while (!empty(queueTmpH)) {
    int inf = pop(queueTmpH, queueTmpT);
    std::cout << inf << " ";
  }
}
