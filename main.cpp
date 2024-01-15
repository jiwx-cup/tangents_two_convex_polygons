#include <bits/stdc++.h>

using namespace std;

// store the center of polygon
pair<int, int> mid;

// quadrant of point
int quad(pair<int, int> p)
{
    if (p.first >= 0 && p.second >= 0) return 1;
    if (p.first <= 0 && p.second >= 0) return 2;
    if (p.first <= 0 && p.second <= 0) return 3;
    return 4;
}

// compare for sorting
bool compare(pair<int, int> p1, pair<int, int> q1)
{
    pair<int, int> p = make_pair(p1.first - mid.first,
                                 p1.second - mid.second);
    pair<int, int> q = make_pair(q1.first - mid.first,
                                 q1.second - mid.second);

    int one = quad(p);
    int two = quad(q);

    if (one != two) return (one < two);

    return (p.second * q.first < q.second * p.first);
}

// check whether the line is crossing the polygon
int orientation(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    int val = (b.second - a.second) * (c.first - b.first) -
              (c.second - b.second) * (b.first - a.first);

    if (val == 0) return 0;
    if (val > 0) return 1;
    return -1;
}

// find upper tangent of two polygons
// represented as two vectors
void upper_tangent(vector<pair<int, int>> a,
                   vector<pair<int, int>> b)
{
    int n_a = a.size(), n_b = b.size();

    // max_a and min_b are used to check if
    // polygon a is left of b
    int max_a = INT_MIN;
    for (int i = 0; i < n_a; ++i) {
        max_a = max(max_a, a[i].first);
        mid.first += a[i].first;
        mid.second += a[i].second;
        a[i].first *= n_a;
        a[i].second *= n_a;
    }
    // sorting the points in counterclockwise order
    // for polygon a
    sort(a.begin(), a.end(), compare);
    for (int i = 0; i < n_a; ++i) {
        a[i].first /= n_a;
        a[i].second /= n_a;
    }

    mid = {0, 0};

    int min_b = INT_MIN;
    for (int i = 0; i < n_b; ++i) {
        min_b = min(min_b, b[i].first);
        mid.first += b[i].first;
        mid.second += b[i].second;
        b[i].first *= n_b;
        b[i].second *= n_b;
    }
    // sorting the points in counterclockwise order
    // for polygon b
    sort(b.begin(), b.end(), compare);
    for (int i = 0; i < n_b; ++i) {
        b[i].first /= n_b;
        b[i].second /= n_b;
    }

    // if a is to the right of b, swap and b
    // this makes sure a is left of b
    if (min_b < max_a)
    {
        a.swap(b);
        n_a = a.size();
        n_b = b.size();
    }

    // i_a -> rightmost point of a
    int i_a = 0, i_b = 0;
    for (int i = 1; i < n_a; ++i) {
        if (a[i].first > a[i_a].first)
        {
            i_a = i;
        }
    }
    // i_b = leftmost point of b
    for (int i = 1; i < n_b; ++i) {
        if (b[i].first < b[i_b].first)
        {
            i_b = i;
        }
    }

    // finding the upper tangent
    int idx_a = i_a, idx_b = i_b;
    bool done = false;
    while (!done)
    {
        done = true;
        while (orientation(b[idx_b], a[idx_a], a[(idx_a + 1) % n_a]) > 0)
        {
            idx_a = (idx_a + 1) % n_a;
        }

        while (orientation(a[idx_a], b[idx_b], b[(n_b + idx_b - 1) % n_b]) < 0)
        {
            idx_b = (n_b + idx_b - 1) % n_b;
            done = false;
        }
    }

    cout << "upper tangent (" << a[idx_a].first << ","
    << a[idx_a].second << ") (" << b[idx_b].first
    << "," << b[idx_b].second << ")\n";
}

// find lower tangent of two polygons
// represented as two vectors
void lower_tangent(vector<pair<int, int>> a,
                   vector<pair<int, int>> b)
{
    int n_a = a.size(), n_b = b.size();

    // max_a and min_b are used to check if
    // polygon a is left of b
    int max_a = INT_MIN;
    for (int i = 0; i < n_a; ++i) {
        max_a = max(max_a, a[i].first);
        mid.first += a[i].first;
        mid.second += a[i].second;
        a[i].first *= n_a;
        a[i].second *= n_a;
    }
    // sorting the points in counterclockwise order
    // for polygon a
    sort(a.begin(), a.end(), compare);
    for (int i = 0; i < n_a; ++i) {
        a[i].first /= n_a;
        a[i].second /= n_a;
    }

    mid = {0, 0};

    int min_b = INT_MIN;
    for (int i = 0; i < n_b; ++i) {
        min_b = min(min_b, b[i].first);
        mid.first += b[i].first;
        mid.second += b[i].second;
        b[i].first *= n_b;
        b[i].second *= n_b;
    }
    // sorting the points in counterclockwise order
    // for polygon b
    sort(b.begin(), b.end(), compare);
    for (int i = 0; i < n_b; ++i) {
        b[i].first /= n_b;
        b[i].second /= n_b;
    }

    // if a is to the right of b, swap and b
    // this makes sure a is left of b
    if (min_b < max_a)
    {
        a.swap(b);
        n_a = a.size();
        n_b = b.size();
    }

    // i_a -> rightmost point of a
    int i_a = 0, i_b = 0;
    for (int i = 1; i < n_a; ++i) {
        if (a[i].first > a[i_a].first)
        {
            i_a = i;
        }
    }
    // i_b = leftmost point of b
    for (int i = 1; i < n_b; ++i) {
        if (b[i].first < b[i_b].first)
        {
            i_b = i;
        }
    }

    // finding the upper tangent
    int idx_a = i_a, idx_b = i_b;
    bool done = false;
    while (!done)
    {
        done = true;
        while (orientation(a[idx_a], b[idx_b], b[(idx_b + 1) % n_b]) > 0)
        {
            idx_b = (idx_b + 1) % n_b;
        }

        while (orientation(b[idx_b], a[idx_a], a[(n_a + idx_a - 1) % n_a]) < 0)
        {
            idx_a = (n_a + idx_a - 1) % n_a;
            done = false;
        }
    }

    cout << "lower tangent (" << a[idx_a].first << ","
         << a[idx_a].second << ") (" << b[idx_b].first
         << "," << b[idx_b].second << ")\n";
}

int main() {
    vector<pair<int, int>> convex_a;
    convex_a.push_back({2, 2});
    convex_a.push_back({3, 1});
    convex_a.push_back({3, 3});
    convex_a.push_back({5, 2});
    convex_a.push_back({4, 0});

    vector<pair<int, int>> convex_b;
    convex_b.push_back({0, 1});
    convex_b.push_back({1, 0});
    convex_b.push_back({0, -2});
    convex_b.push_back({-1, 0});

//    upper_tangent(convex_a, convex_b);

    lower_tangent(convex_a, convex_b);

    return 0;
}
