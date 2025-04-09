#include <iostream>
#include <sstream>

struct list {
  int inf;
  list *next;
  list *prev;
};

void push_back(list *&h, list *&t, int x) {
  list *r = new list;
  r->inf = x;
  r->next = NULL;

  if (!h && !t) {
    r->prev = NULL;
    h = r;
  } else {
    t->next = r;
    r->prev = t;
  }
  t = r;
}

void push_front(list *&t, list *&h, int x) {
  list *r = new list;
  r->inf = x;
  r->prev = NULL;

  if (!h && !t) {
    r->next = NULL;
    h = r;
  } else {
    t->prev = r;
    r->next = t;
  }
  t = r;
}

list *find(list *h, list *t, int x) {
  list *p = h;
  while (p) {
    if (p->inf == x)
      break;
    p = p->next;
  }
  return p;
}

void insert_after(list *&h, list *&t, list *r, int y) {
  list *p = new list;
  p->inf = y;
  if (r == t) {
    p->next = NULL;
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
  if (r == h && r == t)
    h = t = NULL;
  else if (r == h) {
    h = h->next;
    h->prev = NULL;
  } else if (r == t) {
    t = t->prev;
    t->next = NULL;
  } else {
    r->next->prev = r->prev;

    r->prev->next = r->next;
  }
  delete r;
}

void print(list *h, list *t) {
  list *p = h;
  while (p) {
    std::cout << p->inf << " ";
    p = p->next;
  }
  std::cout << std::endl;
}

int main() {
  list *h = nullptr;
  list *t = nullptr;

  std::string line;
  getline(std::cin, line);
  std::stringstream ss(line);
  int tmp;
  while (ss >> tmp) {
    push_back(h, t, tmp);
  }

  list *p = h;
  int max = h->inf;
  while (p) {
    int inf = p->inf;
    if (inf > max) {
      max = inf;
    }
    p = p->next;
  }

  list *hTmp1 = nullptr;
  list *tTmp1 = nullptr;
  list *hTmp2 = nullptr;
  list *tTmp2 = nullptr;

  p = h;
  bool flag = false;
  while (p) {
    int inf = p->inf;
    if (inf == max) {
      flag = true;
    }
    if (!flag) {
      push_back(hTmp1, tTmp1, inf);
    } else {
      push_back(hTmp2, tTmp2, inf);
    }
    p = p->next;
  }

  list *h3 = nullptr;
  list *t3 = nullptr;
  p = hTmp2;
  while (p) {
    int inf = p->inf;
    push_back(h3, t3, inf);
    p = p->next;
  }

  p = hTmp1;
  while (p) {
    int inf = p->inf;
    push_back(h3, t3, inf);
    p = p->next;
  }

  print(h3, t3);
}
