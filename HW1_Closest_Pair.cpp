#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point
{
    Point()
    {

    }
    Point(double xVal, double yVal)
    {
        x = xVal;
        y = yVal;
        index = -1;
    }
    double x;
    double y;
    int index;
};

bool yCompare(Point &a, Point &b)
{
    return a.y < b.y;
}

bool xCompare(Point &a, Point &b)
{
    return a.x < b.x;
}

double pointDistance(Point &a, Point &b) //return the distance without sqrt
{
    return  sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double findShortestDistance(int from, int to, Point *pointsX,  Point *pointsY)
{
    int pointCount = to-from+1;

    if(pointCount < 2)
    {
        //unreachable
        return 0;
    }
    if(pointCount == 2)
    {
        return pointDistance(pointsX[from], pointsX[to]);
    }
    if(pointCount == 3)
    {
        double minDistance =  pointDistance(pointsX[from], pointsX[from+1]);
        minDistance = min(minDistance, pointDistance(pointsX[from], pointsX[to]));
        minDistance = min(minDistance, pointDistance(pointsX[from+1], pointsX[to]));
       return minDistance;
    }

    int mid = (from+to)/2;

    Point *pointsY_Left = new Point[pointCount];
    int pointsY_LeftCount = 0;
    Point *pointsY_Right = new Point[pointCount];
    int pointsY_RightCount = 0;

    for(int i = 0; i < pointCount; i++)
    {
        if(pointsY[i].index <= mid)
        {
            pointsY_Left[pointsY_LeftCount++] = pointsY[i];
        }
        if(pointsY[i].index >= mid)
        {
            pointsY_Right[pointsY_RightCount++] = pointsY[i];
        }
    }

    double d =  min(findShortestDistance(from,mid,pointsX,pointsY_Left), findShortestDistance(mid,to,pointsX,pointsY_Right));


    Point *pointsInMid = new Point[pointCount];
    int pointsInMidCount = 0;


    for(int i = 0; i < pointCount; i++)
    {
        if(abs(pointsY[i].x - pointsX[mid].x) <= d)
        {
            pointsInMid[pointsInMidCount++] = pointsY[i];
        }
    }

    for(int i = 0; i < pointsInMidCount; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if(i+j >= pointsInMidCount)
            {
                break;
            }
            d = min(d, pointDistance(pointsInMid[i],pointsInMid[i+j]));
        }
    }

    delete[] pointsY_Left;
    delete[] pointsY_Right;
    delete[] pointsInMid;

    return d;

}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        Point *pointsX = new Point[n];
        Point *pointsY = new Point[n];

        for(int i = 0; i < n; i++)
        {
            double x;
            double y;
            cin >> x >> y;
            pointsX[i] = Point(x,y);
        }

        sort(pointsX,pointsX+n, xCompare);
        for(int i = 0; i < n; i++)
        {
            pointsY[i] = Point(pointsX[i].x,pointsX[i].y);
            pointsY[i].index = i;
        }
        sort(pointsY,pointsY+n, yCompare);


        cout << fixed << setprecision(6) << findShortestDistance(0,n-1,pointsX,pointsY) << endl;

        delete[] pointsX;
        delete[] pointsY;
    }
}

