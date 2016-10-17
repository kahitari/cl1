#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

int main(){
    ifstream is("try.csv");

    int a[1000][3];

    int i=0;

    string line;

    while(getline(is,line)){
        stringstream ss(line);
        string cell;

        int k=0;

        while(getline(ss,cell,',')){
            a[i][k]=atoi(cell.c_str());
            k++;
        }
        i++;

    }

    /*while (is>>fileRow) {
        a[i][0]=atoi(fileRow[0].c_str());
        a[i][1]=atoi(fileRow[1].c_str());
        a[i][2]=0;
        i++;
    }*/

    int n =i;

    int k;
    cout<<"k ?";
    cin>>k;

    int centroid[k][2],clusters[k][1000],sizeofcluster[k];

    for(int i=0;i<k;i++){
        centroid[i][0]=a[i][0];
        centroid[i][1]=a[i][1];
        a[i][2]=i;
    }

    for(int i=0;i<n;i++){
        int dist = 99999;
        int p=0;
        int q;

        for(int j=0;j<k;j++){
            int x = sqrt( (centroid[j][0]-a[i][0])*(centroid[j][0]-a[i][0])+(centroid[j][1]-a[i][1])*(centroid[j][1]-a[i][1]));

            if(x<dist){
                p=j;
                dist=x;
            }
        }

        q=sizeofcluster[p]++;
        clusters[p][q]=i;
        a[i][2]=p;
    }


    int check=1;
    int iter=0;

    while(check){
        check=0;
	cout<<"Iteration"<<++iter<<endl;
		check=0;
		for(int i=0;i<n;i++)
		{
			cout<<a[i][0]<<"\t"<<a[i][1]<<"\t"<<a[i][2]<<"\t";

		}


        for(int i=0;i<k;i++){
            int x=0;
            int y=0;

            for(int j=0;j<sizeofcluster[i];j++){
                int off = clusters[i][j];

                x+=a[off][0];
                y+=a[off][1];

            }

            centroid[i][0]=x/sizeofcluster[i];
            centroid[i][1]=y/sizeofcluster[i];
            sizeofcluster[i]=0;

        }

        for(int i=0;i<n;i++){
            int dist = 99999;
            int p=0;
            int q;

            for(int j=0;j<k;j++){
                int x = sqrt( (centroid[j][0]-a[i][0])*(centroid[j][0]-a[i][0])+(centroid[j][1]-a[i][1])*(centroid[j][1]-a[i][1]));

                if(x<dist){
                    p=j;
                    dist=x;
                }
            }

            if(a[i][2]!=p)
                check=1;

            q=sizeofcluster[p]++;
            clusters[p][q]=i;
            a[i][2]=p;
        }


    }

    ofstream of("output.csv");

    for(int i=0;i<k;i++){

        for(int j=0;j<sizeofcluster[i];j++){
            int off = clusters[i][j];

            of<<a[off][0];

            for(int k=0;k<=i;k++)
                of<<",";

            of<<a[off][1];
            of<<"\n";

        }


    }
    of.close();


    return 0;
}

