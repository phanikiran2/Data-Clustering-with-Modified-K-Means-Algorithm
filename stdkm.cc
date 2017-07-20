#include<iostream>
#include<climits>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include <fstream>
using namespace std;

#define NP 50

int max_x=0,max_y=0,min_x=INT_MAX,min_y=INT_MAX,k;
int CH_X[10],CH_Y[10];
struct point
{
  int x;    //X Co-ordinate
  int y;    //Y Co-ordinate
  int g;    //Segment Number
  int c;    //Cluster Number
  int dist;
};

void cluster(struct point data[NP],int cfrequency[],int frequency[])
{
	//cout<<"Into Cluster Function"<<endl;
	int i=0,c=0,bound_k=k,right=0,left=0,up=0,down=0;
	while(i!=bound_k && c<k)
	{
  		//cout<<"in while\n";
  		int j;
  		for(j=0;j<k*k;j++)
  		{
    			if(frequency[j]==cfrequency[i])
    			{
      				frequency[j]=-1;
      				break;
    			}
  		}
  		if(j<(k*k))
  		{
    			//cout<<"cluster:"<<c<<endl;
    			for(int m=0;m<NP;m++)
    		        {
      				if(j+1>0 && frequency[j+1]<=cfrequency[bound_k])
      				{
        				frequency[j+1]=0;
        				bound_k++;
        				if(data[m].g==j || data[m].g==j+1)
        				{
          					data[m].c=c;
        				}
      				}
      				if(j-1>0 && frequency[j-1]<=cfrequency[bound_k])
      				{
        				frequency[j-1]=0;
        				bound_k++;
        				if(data[m].g==j || data[m].g==j-1)
        				{
          					data[m].c=c;
        				}
      				}
      				if(j+k<k && frequency[j+k]<=cfrequency[bound_k])
      				{
                                        frequency[j+k]=0;
          			        bound_k++;
        				if(data[m].g==j || data[m].g==j+k)
        				{
          					data[m].c=c;
        				}
      				}
      				if(j-k>0 && frequency[j-k]<=cfrequency[bound_k])
      				{
        				frequency[j-k]=0;
        				bound_k++;
        				if(data[m].g==j || data[m].g==j-k)
        				{
          					data[m].c=c;
        				}
      				}
      				if(data[m].g==j)
      				{
        				data[m].c=c;
 					//cout<<data[m].x<<","<<data[m].y<<endl;
      				}
    			}
    			c++;
    			i++;
  		}

	}
}

void ClusterHead_Update(struct point data[NP])
{
        int count;
        cout<<"New Cluster Heads"<<"\n";
	for(int j=0;j<k;j++)
	{
                count=0;
		CH_X[j]=0;CH_Y[j]=0;
		for(int i=0;i<NP;i++)
		{
			if(data[i].c==j)
			{ 
				CH_X[j]+=data[i].x; 
				CH_Y[j]+=data[i].y;
				count++;
			}
		}
		CH_X[j]/=count;
		CH_Y[j]/=count;
		cout<<CH_X[j]<<","<<CH_Y[j]<<endl;
	}
     

}

bool UpdateCluster(struct point data[NP],bool terminate)
{
	int xdiff,ydiff,temp;
        bool flag=true;
	for(int j=0;j<k;j++)
	{
		for(int i=0;i<NP;i++)
		{ 
			xdiff=data[i].x-CH_X[j];
			ydiff=data[i].y-CH_Y[j];
			int r=(xdiff*xdiff)+(ydiff*ydiff);
			temp=sqrt(r);
			//cout<<"r:"<<r<<endl;
                        //cout<<"j,"<<"i"<<temp<<endl;
			if(temp<data[i].dist)
			{
				data[i].dist=temp;
				data[i].c=j;
				flag=false;
			}
		}
	}
        if(flag)
		terminate=true;
return terminate;
}
			

void segment(struct point data[NP], int frequency[], int x_length, int y_length, int k)
{
  int p=0,q=0;
  for(int i=0;i<NP;i++)
  {
    //cout<<data[i].x<<","<<data[i].y<<"  x_length:"<<x_length<<" y_length:"<<y_length<<endl;
    p=(data[i].x)/x_length;
    q=(data[i].y)/y_length;
    //cout<<"p ,q:"<<p<<","<<q<<endl;
    if(q>=k&&p>=k)
      data[i].g=(k-1)*k+(k-1);
    else if(q>=k)
      data[i].g=((k-1)*k)+p;          
    else if(p>=k)
      data[i].g=(q*k)+(k-1);
    else
      data[i].g=(q*k)+p;
    //cout<<data[i].g<<endl;
    frequency[data[i].g]++;
  }
}

void random(struct point data[NP])
{
  for(int i=0;i<NP;i++)
  {
    data[i].x=rand()%300;
    data[i].y=rand()%300;
    data[i].g=0;
    data[i].c=-1;
    data[i].dist=INT_MAX;
    if(data[i].x>max_x)
    { 
       max_x=data[i].x;
    }
    else if(data[i].x<min_x)
    { 
       min_x=data[i].x;
    }
    
    if(data[i].y>max_y)
    { 
       max_y=data[i].y;
    }
    else if(data[i].y<min_y)
    { 
       min_y=data[i].y;
    }
  }
}

int main()
{
  int x_length,y_length,sum=0;
  bool terminate=false;
  ofstream output,input;
  input.open("input.txt");
  output.open("output.txt");
  cin>>k;
  int frequency[k*k],cfrequency[k*k];
  struct point data[NP];
  random(data);
  for(int i=0;i<NP;i++)
  {
     input<<data[i].x<<","<<data[i].y<<endl;;
  }
  //cout<<"maximum x co-ordinate:"<<max_x<<endl;
  //cout<<"maximum y co-ordinate:"<<max_y<<endl;
  //cout<<"minimum x co-ordinate:"<<min_x<<endl;
  //cout<<"minimum y co-ordinate:"<<min_y<<endl;
  x_length=(max_x-min_x)/k;
  y_length=(max_y-min_y)/k;
  //cout<<x_length<<"   "<<y_length<<endl;
  
  for(int i=0;i<k*k;i++)
    frequency[i]=0;
  //segment(data,frequency,x_length,y_length,k);
  //cout<<"Frequencies of each segment:"<<endl;
  for(int i=0;i<k*k;i++)
  {
    cfrequency[i]=frequency[i];
    //cout<<"frequency"<<frequency[i]<<endl;
    sum+=frequency[i];
  }
  //cout<<sum<<endl;
  //sort(cfrequency,cfrequency+k*k,greater<int>());
   /*for(int i=0;i<k*k;i++)
  {
    cout<<"cfrequency"<<cfrequency[i]<<endl;
  }*/
  //cluster(data,cfrequency,frequency);
  for(int i=0;i<k;i++)
  {
    CH_X[i]=rand()%300;
    CH_Y[i]=rand()%300;
    cout<<CH_X[i]<<","<<CH_Y[i]<<"\n";
  }
  while(!terminate)
  {
  terminate=UpdateCluster(data,terminate);
  ClusterHead_Update(data);
  }
  //cout<<"FinalClusters\n";
  for(int j=0;j<k;j++)
  {
    output<<"Cluster"<<j<<endl;
    for(int i=0;i<NP;i++){
	if(data[i].c==j)
		output<<data[i].x<<","<<data[i].y<<"\n";
    }
    output<<"\n \n";
  }
  return 0;
} 
