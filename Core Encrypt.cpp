#include <iostream.h>
#include <string.h>
#include <math.h>
#include <vector.h>
#include <fstream.h>
#include <stdlib.h>

using namespace std;

int* random_gen(int data_length)
{
  int *ra; 
  ra=(int*)malloc((127+data_length)*sizeof(int));
	 for (int i=0;i<(127+data_length);i++) 
	 {
		 ra[i]=(-31+(rand()%116));
	 }
	 return ra;
}

string encryption(string name, int index, int data_length, int* random, int flag)    //Function that encrypts
{
  if(flag%2==0)
  {
	  for(int i=index;i<(index+data_length);i++)
    {
      name[i-index]=name[i-index]+random[i];
    }  
	}
	if(flag%2==1)
	{
	  for(int i=index;i<(index+data_length);i++)
    {
        name[i-index]=name[i-index]-random[i];
    }
	}
  return(name);
}

int* ran_loc(int data_length, int key_length, int length)
{
  int *locations;
  locations=(int*)malloc((key_length)*sizeof(int));
  for(int i=0;i<key_length;i++)
  {
    locations[i]=(rand()%length);
  }
  for(int i=0;i<key_length;i++)
  {
    for(int j=(i+1);j<key_length;j++)
    {
      if(locations[i]==locations[j]||locations[i]==(locations[j]+1)||locations[i]==(locations[j]-1))
      {
        locations[i]=(rand() % length);
        i=0;
        j=(i+1);
      }
    }
  }
  return locations;
}

char* hide_pass(string data, string key, int data_length, int key_length, int* locations)
{
  char *encrypted;
  int length=(data_length+(2*key_length));
  encrypted=(char*)malloc(length*sizeof(char));
  for (int i=0; i<key_length;i++) 
	{
		encrypted[locations[i]]=(char)244;
		encrypted[locations[i+1]]=key[i];
	}
	for(int i=0;i<data_length;i++)
	{
	  for(int j=0;j<length;j++)
	  {
	    if(!encrypted[j])
	    {
	      encrypted[j]=data[i];
	    }
	  }
	}
  return encrypted;
}

int main()
{
  string data,key;
  int *random=NULL;
  data="HELLO, Niranjan!";
  key="8903716100";
  //getline (cin, data);  //get the data to be encrypted
  //getline (cin, key);   //get the passkey for encryption
  int data_length=0,key_length=0;
  data_length=data.length();
  key_length=key.length();
  random=random_gen(data_length);
  for(int i=0; i<key_length;i++)
  {
    data = encryption(data,(int) key[i],data_length,random,i);
  }
  int length=(data_length+(2*key_length));
  int *locations;
  locations=(int*)malloc((key_length)*sizeof(int));
  locations=ran_loc(data_length,key_length,length);
  char *encrypted;
  encrypted=(char*)malloc(length*sizeof(char));
  encrypted=hide_pass(data,key,data_length,key_length,locations);
  ofstream outputFile("encryption.txt");
  for(int i=0;i<length;i++)
  {
    cout<<encrypted[i];
    outputFile << encrypted[i];
  }
  cout<<'\n';
  outputFile << '\n';
  return 0;
}

