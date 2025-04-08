#include <iostream>
#include <sstream>

struct list {
  int inf;
  list *next;
  list *prev;
};

void push(list *&h, list *&t, int x) {
  list *r = new list;
  r->inf = x;
  r->next = nullptr;
  if (!h && !t) {
    r->prev = nullptr;
    h = r;
  } else {
    t->next = r;
    r->prev = t;
  }
  t = r;
}

void print(list *h, list *t) {
  list *p = h;
  while (p) {
    std::cout << p->inf << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

list *find(list *h, list *t, int x) {
  list *p = h;
  while (p) {
    if (p->inf == x) {
      break;
    }
    p = p->next;
  }
  return p;
}

void insert_after(list *&h, list *&t, list *r, int x) {
  list *p = new list;
  p->inf = x;
  if (r == t) {
    p->next = nullptr;
    p->prev = r;
    r->next = p;
    t = p;
  } else {
    r->next->prev = p;
    p->next = r->next;
    p->prev = r;
    r->next = p;
  }
}

void del_node(list *&h, list *&t, list *r) {
  if (r == h && r == t) {
    h = t = nullptr;
  } else if (r == h) {
    h = h->next;
    h->prev = nullptr;
  } else if (r == t) {
    t = t->prev;
    t->next = nullptr;
  } else {
    r->next->prev = r->prev;
    r->prev->next = r->next;
  }
  delete r;
}

void del_list(list *&h, list *&t) {
  while (h) {
    list *p = h;
    h = h->next;
    h->prev = nullptr;
    delete p;
  }
}

int main() {
  list *h;
  list *t;

  std::string line;
  getline(std::cin, line);
  std::stringstream ss(line);
  char tmp;
  while (ss >> tmp) {
    push(h, t, tmp);
  }

  int first = h->inf;
  int max = first;

  list *p = h;
  while (p) {
    if (p->inf > max) {
      max = p->inf;
    }
    p = p->next;
  }

  while (p) {
    if (p->inf == first) {
      insert_after(h, t, p, max);
    }
    p = p->next;
  }

  print(h, t);
}
