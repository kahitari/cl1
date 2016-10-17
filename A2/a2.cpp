#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;

vector<int>A;

class Arg
{
	public:
		Arg(){}
		int first,last;
};

class QSort
{
	public:
		QSort(){}
		~QSort(){}
		void print();
		static void* sort(void*);
	private:
		static int divide(int,int);

};

void QSort::print()
{
		cout<<"Sorted Array ahe:>>>"<<endl;
		for(int i=0;i<A.size();i++)  cout<<A[i]<<endl;
}

int QSort::divide(int pahila,int shevat)
{
	int i=pahila,ata=pahila;
	int pivot=A[shevat];
	int tatpurta;

	while(ata<shevat)
	{
		if(A[ata] <= pivot)
		{
			tatpurta=A[ata];
			A[ata]=A[i];
			A[i]=tatpurta;
			i++;
		}
		ata++;
	}

	tatpurta=A[shevat];
	A[shevat]=A[i];
	A[i]=tatpurta;
	return i;
}

void* QSort::sort(void* args)
{
	int pahila,shevat;
	pahila=((Arg*)args)->first;
	shevat=((Arg*)args)->last;

	if(pahila >= shevat) return NULL;

	int pos=divide(pahila,shevat);


	pthread_t thread[2];
	Arg* obj[2];
	obj[0]=new Arg;
	obj[1]=new Arg;

	obj[0]->first=pahila;
	obj[0]->last=pos-1;
	obj[1]->first=pos+1;
	obj[1]->last=shevat;

	pthread_create(&thread[0],NULL,&QSort::sort,(void*)obj[0]);
	pthread_create(&thread[1],NULL,&QSort::sort,(void*)obj[1]);

	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);


}

int main()
{
	int n;
	cout<<"Kiti Elements pahije>>>"<<endl;
	cin>>n;

	int x;
	QSort q;
	cout<<"Elements sanga>>"<<endl;
	while(n!=0)
	{
		cin>>x;
		A.push_back(x);
		n--;
	}
	Arg *obj_main=new Arg;

	obj_main->first=0;
	obj_main->last=A.size()-1;

	q.sort((void*)obj_main);
	q.print();

	return 0;

}