#include <iostream>
#include <vector>

using namespace std;

struct Point {
        int x, y;
};

int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;
    if (val > 0) {
        return 2;
    }
    return 1;
}

vector<Point> convexHull(vector<Point> &points) {
    int n = points.size();
    if (n < 3)
        return {};

    int start = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[start].x ||
            (points[i].x == points[start].x && points[i].y < points[start].y)) {
            start = i;
        }
    }

    vector<Point> hull;
    int current = start;
    do {
        hull.push_back(points[current]);
        int next = (current + 1) % n;

        for (int i = 0; i < n; i++) {
            if (orientation(points[current], points[i], points[next]) == 1) {
                next = i;
            }
        }
        current = next;
    } while (current != start);

    return hull;
}

int main() {
    int n;
    std::cout << "Введите количество точек: ";
    std::cin >> n;
    std::cout << "Вводите точки в формате \"x y\"" << std::endl;
    vector<Point> points;
    int x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        points.push_back({x, y});
    }

    vector<Point> hull = convexHull(points);

    cout << "Выпуклая оболочка (против ЧС):\n";
    for (auto p : hull) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << endl;

    return 0;
}
