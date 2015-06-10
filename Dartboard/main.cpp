#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Dartboard
{
    public:
        Dartboard();
        void throwDart(float t);
        float calculatePi(float hit, float total);
        float piApprox;
        float x, y;
        float hits = 0;
        float misses = 0;
        const float factor = 2.0 / RAND_MAX;
};

Dartboard::Dartboard()
{
    //
}

void Dartboard::throwDart(float t)
{
    if(t <= 0)
        cout << "Error, cannot throw 0 darts" << endl;

    srand((int)clock());

    for(int i=0; i<t; i++)
    {
        x=(rand()*2.0/RAND_MAX)-1;
        y=(rand()*2.0/RAND_MAX)-1;

        float r = sqrt(x*x+y*y);

        if(r <= 1.0)
            hits++;

        else
            misses++;
    }
}

float Dartboard::calculatePi(float hit, float total)
{
    piApprox = (4.0 * hit) / total;

    return piApprox;
}

int main()
{
    float throws = 2500;
    float h;
    float m;

    Dartboard * d = new Dartboard();

    d->throwDart(throws);

    h=d->hits;
    m=d->misses;

    d->calculatePi(h, throws);

    cout << "Number of threads: " << 1 << endl;
    cout << "Number of throws: " << throws << endl;
    cout << "Number of hits: " << h << endl;
    cout << "Number of misses: " << m << endl;
    cout << "Approximation of pi: " << d->piApprox << endl;

    clock_t t1,t2;
    t1=clock();
    t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;

    cout << "Running time: " << seconds << endl;

    delete d;

    return 0;
}
