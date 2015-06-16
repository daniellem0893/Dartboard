#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>

using namespace std;

double elapsed;
int hitcount=0;
void *dartboard (void * darts_thrown)
{
	srand((int)clock());
	float x,y,r; int hits=0;
	for (int i=0; i<(long)darts_thrown; i++){
	x=(rand()*2.0/RAND_MAX)-1;
	y=(rand()*2.0/RAND_MAX)-1;
	float r = sqrt((x*x)+(y*y));
	if(r<=1.0){hits++;} }
	hitcount= hitcount+hits;
	pthread_exit(0);
}


timespec diff (timespec start, timespec end)
{timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0)
	{temp.tv_sec=end.tv_sec-start.tv_sec-1;
	temp.tv_nsec= 1000000000+end.tv_nsec-start.tv_nsec;}
	else
	{ temp.tv_sec=end.tv_sec-start.tv_sec;
	temp.tv_nsec=end.tv_nsec-start.tv_nsec;}
	return temp;
}

int main()
{

	int count=0;
	for (int z=0; z<3;z++)
	{
	timespec begin, end; clock_gettime(CLOCK_MONOTONIC, &begin);
	int rc; int threadz[3]={1,2,10}; int total_throws[3]={2500,1000000,10000000};
	int num_threads = threadz[count]; int darts_thrown=total_throws[count];
	pthread_t thread[num_threads]; pthread_attr_t attr;
	void *status;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	for( int i=0; i<num_threads; i++)
	{
	rc= pthread_create(&thread[i], NULL, &dartboard, (void *)darts_thrown);
	if (rc) {cout<< "Error"<< rc<<endl; exit(-1);}
	}

	pthread_attr_destroy(&attr);
        for(int y=0; y<num_threads; y++)
	{ rc=pthread_join(thread[y],&status);
	if (rc){cout<<"Error"<< rc<<endl; exit(-1);}
	}

	float pi;
	pi = 4.0 * hitcount/(darts_thrown * num_threads);
	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed= diff(begin,end).tv_sec + ((double)(diff(begin,end).tv_nsec/1000000000.0));
	cout<< "Number of throws: "<<darts_thrown<<endl;
	cout<< "Number of threads: "<<num_threads<<endl;
	cout<< "Number of hits: "<<hitcount<<endl;
	cout<< "Number of misses: "<<(darts_thrown * num_threads)-hitcount<<endl;
	cout<< "Executing time: " <<elapsed<<endl;
	cout<< "Estimate of pi: "<<pi<<"\n"<<endl;
	count++;

	}

}




