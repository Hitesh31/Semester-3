#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
vector<string> vec;	//vector for cache stroring/cache table 
vector<string> resvec; //vector containing all different entries, for compulsory misses
vector<string> fullvec; //vector containing all data addresses (for optimal case only)
int n;
int total=0;
int comp_miss=0,cap_miss=0;
string text_file;
fstream fn;
void LRU(string k)
{
	total++;
	int j=0;
	bool b=false;
	for(int i=0;i<vec.size();i++)
	{
		if(k==vec[i])
		{
			b=true;
			break;
		}
		else
			b=false;
		j++;
	}
	if(b==true)
	{
		vec.erase(vec.begin()+j);
		vec.insert(vec.begin(),k);
		resvec.push_back("HIT");
	}
	if(b==false)
	{
		vec.insert(vec.begin(),k);
		if(vec.size()>n) vec.pop_back();
		resvec.push_back("MISS");
		bool y=false;
		for(int i=0;i<fullvec.size();i++)
		{
			if(k==fullvec[i])
			{
				y=true;
				break;
			}
			else
				y=false;
		}
		if(y==false)
		{
			comp_miss++;
			fullvec.push_back(k);
		}
		else
		{
			cap_miss++;
		}
	}
}
void FIFO (string k)
{
	total++;
	bool b=false;
	int j=0;
	for(int i=0;i<vec.size();i++)
	{
		if(k==vec[i])
		{
			b=true;
			break;
		}
		else
			b=false;
		j++;
	}
	if(b==true)
		resvec.push_back("HIT");
	if(b==false)
	{
		vec.push_back(k);
		if(vec.size()>n) vec.erase(vec.begin());
		resvec.push_back("MISS");
		bool y=false;
		for(int i=0;i<fullvec.size();i++)
		{
			if(k==fullvec[i])
			{
				y=true;
				break;
			}
			else
				y=false;
		}
		if(y==false)
		{
			comp_miss++;
			fullvec.push_back(k);
		}
		else
		{
			cap_miss++;
		}
	}
}
void OPTIMAL ()
{
	vector <string> newvec;
	string data;
	int arr[n]={0};
	while(fn>>data)
	{ 
	  total++;
	  newvec.push_back(data);
	}
	bool b=false,go=false;
	int pos;
	for(int i=0;i<newvec.size();i++)
	{
		for(int j=0;j<vec.size();j++)
		{
			if(vec[j]==newvec[i])
			{
				b=true;
				pos=j;
				arr[j]=0;
				break;
			}
			else 
				b=false;
		}
		if(b==true)
		{
			resvec.push_back("HIT");
			if(vec.size()==n)
			{
				arr[pos]=0;
				for(int f=i+1;f<newvec.size();f++)
				{
					if(vec[pos]==newvec[f])
						break;
					arr[pos]++;
				}
				for(int f=0;f<n;f++)
				{
					if(f!=pos) arr[f]--;
				}
			}
		}	
		if(b==false)
		{
			resvec.push_back("MISS");
			bool y=false;
			for(int m=0;m<fullvec.size();m++)
			{
				if(newvec[i]==fullvec[m])
				{
					y=true;
					break;
				}
				else
					y=false;
			}
			if(y==false)
			{
				comp_miss++;
				fullvec.push_back(newvec[i]);
			}
			else
			{
				cap_miss++;
			}
			if(vec.size()<=n && go==false) vec.push_back(newvec[i]);
			int index=0;
			if(vec.size()==n && go==true)
			{
				int max=arr[0];
				for(int v=0;v<n-1;v++)
				{
					if(max<arr[v+1])
					{
						max=arr[v+1];
						index=v+1;
					}
				}
				vec.erase(vec.begin()+index);
				arr[index]=0;
			}
			
			if(go==true) vec.insert(vec.begin()+index,newvec[i]);
			if(vec.size()==n && go==true)
			{
				for(int g=i+1;g<newvec.size();g++)
				{
					if(vec[index]==newvec[g])
						break;
					arr[index]++;
				}
				for(int g=0;g<n;g++)
				{
					if(g!=index) arr[g]--;
				}
			}
			if(vec.size()==n && go==false)
			{
				for(int h=0;h<n;h++)
				{
					for(int g=i+1;g<newvec.size();g++)
					{
						if(vec[h]==newvec[g])
							break;
						arr[h]=arr[h]+1;
					}
				}
				go=true;
			}

		}
	}
}
int main(int argc, char const *argv[])
{
	n=atoi(argv[3]);
	text_file=argv[2];
	if((string)argv[1]=="LRU")
	{
	  fn.open(text_file);
	  string data;
	  while(fn>>data)
	  {
	  	LRU(data);
	  }  
	}
	if((string)argv[1]=="FIFO")
	{ 
	  fn.open(text_file);
	  string data;
	  while(fn>>data)
	  {
	  	FIFO(data);
	  }
	}
	if((string)argv[1]=="OPTIMAL")
	{
	 fn.open(text_file);
	 OPTIMAL();
	}
	ofstream fo;
	string out;
	string p;
	for(int i=0;i<text_file.size();i++)
	{
		p=p+text_file[i];
		if(text_file[i+1]=='.')
			break;
	}
	out="MA17BTECH11004_"+(string)argv[1]+"_"+ p +"_"+(string)argv[3]+".out";
	fo.open(out);
	fo<<"TOTAL_ACCESSES = "<<total<<endl;
	fo<<"TOTAL_MISSES = "<<comp_miss+cap_miss<<endl;
	fo<<"COMPULSORY_MISSES = "<<comp_miss<<endl;
	fo<<"CAPACITY_MISSES = "<<cap_miss<<endl;
	for(int i=0;i<resvec.size();i++)
	  	fo<<resvec[i]<<endl;
}