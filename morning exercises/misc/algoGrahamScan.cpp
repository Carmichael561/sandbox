#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <functional>
#include <stack>

struct Point2D
{
    Point2D(int x, int y) : x(x), y(y){}
    friend std::ostream& operator<< (std::ostream &os, const Point2D& p)
    {
        return os << " {" << p.x << ", " << p.y << "} ";
    }
    int x;
    int y;
};



using point = Point2D;
point p0{0, 0};

#define clockwise         1
#define counterclockwise -1
#define colinear          0
int orientation(const point *p1, const point *p2, const point *p3)
{
    int orien = (p2->y - p1->y) * (p3->x - p2->x) - (p2->x - p1->x) * (p3->y - p2->y);

    if (orien > 0)
        return clockwise;
    
    if (orien < 0)
        return counterclockwise;

    return colinear;
}

int squareDistance(const point *p1, const point *p2)
{
    return (p1->y - p2->y)*(p1->y - p2->y) + (p1->x - p2->x)*(p1->x - p2->x);
}

int angle_compare(const void *p1, const void *p2)
{
    const point *a = static_cast<const point*>(p1);
    const point *b = static_cast<const point*>(p2);

    int orien = orientation(&p0, a, b);

    if (orien == 0)
        return (squareDistance(&p0, a) <= squareDistance(&p0, b)) ? -1 : 1;
    else if (orien == -1)
        return -1;
    else
        return 1;
    
}

point nextToTop(std::stack<point> S)
{
    point p = S.top();
    S.pop();
    point n = S.top();
    S.push(p);
    return n;
}

void grahamScan(point *A, int N)
{
    std::vector<point> v1(A, A + N);
    for_each(v1.begin(), v1.end(), [&v1](point p){std::cout << " {" << p.x << ", " << p.y << "} ";});
    std::cout << std::endl;
    
    
    int min_i;
    point min_p = A[0];
    for (int i = 1; i < N; i++)
    {
        if (A[i].y < min_p.y || (A[i].y == min_p.y && A[i].x < min_p.x))
            min_p = A[i], min_i = i;
    }
    p0 = min_p;
    std::cout << "Start point: {" << min_p.x << ", " << min_p.y << "}" << std::endl;

    
    std::cout << "Sorted by angle:" << std::endl;
    std::qsort(A, N, sizeof(A[0]), angle_compare);
    std::vector<point> v2(A, A + N);
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<point>(std::cout));
    std::cout << std::endl;


    int m = 1;
    int i = 1;
    for (i = 1; i < N - 1; i++)
    {
        while (i < N - 1 &&  orientation(&p0, &A[i], &A[i + 1]) == 0)
            i++;
        A[m++] = A[i];
    }
    A[m] = A[i];
    std::vector<point> v3(A, A + m + 1);
    std::cout << "Remove points with similar angle:" << std::endl;
    std::copy(v3.begin(), v3.end(), std::ostream_iterator<point>(std::cout));


    std::stack<point> convex;
    convex.push(A[0]);
    convex.push(A[1]);
    convex.push(A[2]);
    for (int i = 3; i <= m; i++)
    {
        point p1 = nextToTop(convex);
        point p2 = convex.top();
        point p3 = A[i];
        while (not convex.empty() && orientation(&p1, &p2, &p3) != counterclockwise)
        {
            convex.pop();
            p1 = nextToTop(convex);
            p2 = convex.top();
        }
        convex.push(A[i]);
    }



    
    std::cout << std::endl << "Number of convex points is: " << convex.size() << std::endl;
    while (not convex.empty())
    {
        point p = convex.top();
        convex.pop();
        std::cout << " {" << p.x << ", " << p.y << "} ";
    }
 }

int main()
{
    point points[] = {{-1, -5}, {0, 3}, {1, 1}, {2, 2}, {100, 87}, {4, 4},
                      {0, 0}, {20, 0}, {1, 2}, {3, 1}, {3, 3}, {-1, 200}};
    int n = sizeof(points)/sizeof(points[0]);
    grahamScan(points, n);

    std::cout << std::endl << std::endl;

    point points2[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n2 = sizeof(points2)/sizeof(points2[0]);
    grahamScan(points2, n2);

    
    return 0;
}
