#include <iostream>
#include <sstream>

struct list {
  int inf;
  list *next = nullptr;
  list *prev = nullptr;
};

void push(list *&h, int x) {
  if (h->next == nullptr) {
    h->next = h;
    h->prev = h;
    h->inf = x;
    return;
  }
  list *r = new list;
  list *tmp = new list;
  r = h->next;
  h->next = tmp;
  tmp->inf = x;
  tmp->next = r;
  tmp->prev = h;
  r->prev = tmp;
}

void del_node(list *p) {
  list *prev;
  list *next;
  prev = p->prev;
  next = p->next;
  prev->next = p->next;
  next->prev = p->prev;
  // free(p);
}
void print(list *h, list *t) {
  list *p = h;
  while (p) {
    std::cout << p->inf << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

void init(list *&h, int x) {
  h->inf = x;
  h->prev = h;
  h->next = h;
}

int main() {
  list *h;
  // push(h, 0);
  // push(h, 1);
  // push(h, 2);
  // push(h, 3);

  std::cout << "Input list: ";
  std::string line;
  getline(std::cin, line);
  std::stringstream ss(line);
  int tmp;
  while (ss >> tmp) {
    push(h, tmp);
  }

  int k;
  std::cout << "Input k: ";
  std::cin >> k;

  list *p = h;
  do {
    for (int i = 0; i < k - 1; ++i) {
      p = p->next;
    }
    p = p->next;
    del_node(p->prev);

  } while (p->next != p);

  std::cout << p->inf << std::endl;
}
