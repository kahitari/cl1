#include <bits/stdc++.h>
using namespace std;

struct Item{
	float weight;
	int value;
};

struct Node{
	int level,bound,profit;
	float weight;
};

bool cmp(Item a,Item b)
{
	double r1=(double)a.value/a.weight;
	double r2=(double)b.value/b.weight;
	return r1>r2;
}

int bound(Node v, int n,int W,Item arr[])
{
	if(v.weight >= W)
		return 0;
	int profit_bount=v.profit;
	int j=v.level+1;
	int totalweight=v.weight;
	while((j<=n) && (totalweight+arr[j].weight <=W))
	{
		totalweight+=arr[j].weight;
		profit_bount+=arr[j].value;
		j++;
	}

	if(j<n)	
		profit_bount+= (W-totalweight) * arr[j].value / arr[j].weight;

	return profit_bount;
}
int knapsack(int W,Item arr[],int n)
{
	sort(arr,arr + n,cmp);
	queue<Node> q;
	Node v,w;
	v.level=-1;
	v.profit=v.weight=0;
	q.push(v);
	int maxprofit=0;
	while(!q.empty())
	{
		v=q.front();
		q.pop();

		if(v.level == n-1)	continue;

		w.level=v.level+1;
		w.weight=v.weight+arr[w.level].weight;

		w.profit=v.profit+arr[w.level].value;

		if(w.weight<=W && w.profit>maxprofit)	
			maxprofit=w.profit;

		w.bound=bound(w,n,W,arr);
		cout<<"Level"<<w.level<<endl;
		if(w.bound>maxprofit){
			q.push(w);
			cout<<"current node"<<endl;
			cout<<"wt"<<w.weight<<"profit"<<w.profit<<endl;
		}
		else{
			cout<<"discard the node"<<endl;

		}

		w.weight=v.weight;
		w.profit=v.profit;
		w.bound=bound(w,n,W,arr);
		if(w.bound>maxprofit){
			q.push(w);
			cout<<"current node"<<endl;
			cout<<"wt"<<w.weight<<"profit"<<w.profit<<endl;
		}
		else{
			cout<<"discard the node"<<endl;
		}

	}
	return maxprofit;
}

int main()
{
	int W=10;
	Item arr[]={{2, 40}, {3.14, 50}, {1.98, 100},
                  {5, 95}, {3, 30}};

    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<"max profit"<<knapsack(W,arr,n)<<endl;
	return 0;
}
