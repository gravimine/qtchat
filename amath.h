#ifndef AMATH
#define AMATH
#include <QMatrix>
#include <qmath.h>
int GetOstatok(float x,float k)
{
    float x1=x/k;
    if((int)x1==(float)x1) return 0;
    else
    {
        int x2=(int)x1*(int)k;
        return x-x2;
    }
}
double GradusToRadian(double grad)
{
    return grad*M_PI/180;
}

#endif // AMATH

