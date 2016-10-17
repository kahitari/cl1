/*
 * try.cpp
 *
 *  Created on: 16-Oct-2016
 *      Author: flash
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class file_row
{
	vector <string> data;
public:
	string operator[](int index)
		{
			return data[index];
		}
	
	void readNextRow(istream& str)
	{
		string line;
		getline(str,line);
		stringstream linestream(line);
		string cell;
		data.clear();
		while(getline(linestream,cell,','))
		{
			data.push_back(cell);
		}

	}
};

istream& operator >>(istream& str,file_row& row)
{
	row.readNextRow(str);
	return str;
}

int main()
{

	ifstream infile("/home/flash/Documents/be/CL1/CL1_he bagha/A6/try.csv");
	ofstream out_file;
	file_row r;
	int a[1000][3],i=0;
	while(infile>>r)
	{
		a[i][0]=atoi(r[0].c_str());
		a[i][1]=atoi(r[1].c_str());
		a[i++][2]=0;
	}

	stringstream ss;
	string str_a;
	int k;
	cout<<"Enter the value of k>>>>"<<endl;
	cin>>k;
	int n=i,sum=0,p,q;
	int centroid[k][2],clusters[k][100],size_of_cluster[k];

	for(int i=0;i<k;i++)
	{
		centroid[i][0]=a[i][0];
		centroid[i][1]=a[i][1];
		a[i][2]=i;
		size_of_cluster[i]=1;
		clusters[i][0]=i;
	}

	for(int i=0;i<n;i++)
	{
		int dis=9999;
			for(int j=0;j<k;j++)
			{
				int x=sqrt((centroid[j][0]-a[i][0])*(centroid[j][0]-a[i][0])+(centroid[j][1]-a[i][1])*(centroid[j][1]-a[i][1]));
				if(x<=dis)
				{
					p=j;
					dis=x;
				}

			}
			q=size_of_cluster[p]++;
			clusters[p][q]=i;
			a[i][2]=p;
	}

	int check=1;
	int iter=0;
	while(check)
	{
		cout<<"Iteration"<<++iter<<endl;
		check=0;
		for(int i=0;i<n;i++)
		{
			cout<<a[i][0]<<"\t"<<a[i][1]<<"\t"<<a[i][2]<<"\t";

		}

		for(int i=0;i<k;i++)
		{
			int x=0,y=0;
			for(int j=0;j<size_of_cluster[i];j++)
			{
				p=clusters[i][j];
				x+=a[p][0];
				y+=a[p][1];

			}

			centroid[i][0]=x/size_of_cluster[i];
			centroid[i][1]=y/size_of_cluster[i];
			size_of_cluster[i]=0;
		}

		for(int i=0;i<n;i++)
			{
				int dis=9999;
					for(int j=0;j<k;j++)
					{
						int x=sqrt((centroid[j][0]-a[i][0])*(centroid[j][0]-a[i][0])+(centroid[j][1]-a[i][1])*(centroid[j][1]-a[i][1]));
						if(x<=dis)
						{
							p=j;
							dis=x;
						}

					}
					q=size_of_cluster[p]++;
					clusters[p][q]=i;
					if(a[i][2]!=p)
						check=1;
					a[i][2]=p;

				
			}
	}
		out_file.open("out.csv");
		for(int i=0;i<k;i++)
		{
			for(int j=0;j<size_of_cluster[i];j++)
			{
				q=clusters[i][j];
				\
				out_file<<a[q][0];
				for(int p=0;p<=i;p++)
				{
					out_file<<",";
				}
				out_file<<a[q][1]<<"\n";
			}
		}
		infile.close();
		out_file.close();

	return 0;
}



