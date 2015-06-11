#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Dartboard
{
    public:
        Dartboard();
        void throwDart(int t);
        float calculatePi(float hit, int total);
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

void Dartboard::throwDart(int t)
{

    cout << "Throwing darts" << endl;
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

float Dartboard::calculatePi(float hit, int total)
{
    piApprox = (4.0 * hit) / total;

    return piApprox;
}

struct thread_struct {
    int throws;
    Dartboard *d;
};

void *dartThread(void *arguments)
{
    struct thread_struct *args = (struct thread_struct*)arguments;
    int throws = args->throws;
//    throws = args->throws;
    cout << "in thread" << endl;

    args->d->throwDart(throws);

    pthread_exit(NULL);
}


int main()
{
    int rc;
    int i;
    int numThreads = 1;
    pthread_t threads[numThreads];
    pthread_attr_t attr;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    Dartboard dartboard;
    Dartboard *d = &dartboard;

    int totalthrows = 2500;
    struct thread_struct args;
    args.throws = totalthrows;
    args.d = d;



     for( i=0; i < numThreads; i++ ){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, &dartThread, (void *)&args );
      if (rc)
      {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }


    pthread_attr_destroy(&attr);
    for( i=0; i < numThreads; i++ )
    {
        rc = pthread_join(threads[i], &status);
        if (rc)
        {
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }
        cout << "Main: completed thread id :" << i ;
        cout << "  exiting with status :" << status << endl;

        cout << "Number of throws: " << totalthrows << endl;
        cout << "Number of threads: " << numThreads << endl;
        cout << "Number of hits: " << d->hits << endl;
        cout << "Number of misses: " << d->misses << endl;
        d->calculatePi(d->hits, totalthrows);
        cout << "Estimate of pi: " << d->piApprox << endl;
    }



}
