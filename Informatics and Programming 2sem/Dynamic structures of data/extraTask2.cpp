#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

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

void add_row(std::vector<std::vector<int>> &arr) {
  int index = arr.size();
  std::cout << "Index " << index << ": " << std::flush;

  std::string input;
  getline(std::cin, input);

  std::vector<int> new_row;
  std::istringstream stream(input);
  int number;
  while (stream >> number) {
    new_row.push_back(number);
  }
  arr.push_back(new_row);
}

std::vector<std::vector<int>> createAdjMatrix(int numOfVertices) {
  std::vector<std::vector<int>> adjMatrix;
  for (int i = 0; i < numOfVertices; ++i) {
    add_row(adjMatrix);
  }
  return adjMatrix;
}

void DFS(std::vector<std::vector<int>> Gr, std::vector<int> &A, int x) {
  Stack<int> *st = nullptr;

  A[x] = true;

  push(st, x);
  std::cout << x << " ";
  bool fl = false;

  while (!empty(st)) {
    x = st->inf;
    int y;
    for (int i = 0; i < Gr[x].size(); ++i) {
      if (A[Gr[x][i]] == 0) {
        y = Gr[x][i];
        fl = true;
        break;
      }
    }
    if (fl == true) {
      A[y] = true;
      push(st, y);
      std::cout << y << " ";
      fl = false;
    } else {
      pop(st);
    }
  }
  for (int i = 0; i < Gr.size(); ++i) {
    if (!A[Gr[x][i]]) {
      DFS(Gr, A, Gr[x][i]);
    }
  }
}

void DFSHelper(std::vector<std::vector<int>> Gr) {
  int size = Gr.size();
  if (size == 0) {
    return;
  }

  std::vector<int> A(size);
  DFS(Gr, A, 0);
}

int main() {
  std::cout << "Enter number of vertices: ";
  int n;
  std::cin >> n;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  DFSHelper(createAdjMatrix(n));
  std::cout << std::endl;
}
