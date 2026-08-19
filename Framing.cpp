#include<iostream>
#include<string>
using namespace std;
int main()
{
    string data,result="";
    cin>>data;
    int count=0;
    for(int i=0;i<data.length();i++)
{
    result+=data[i];
    if(data[i]=='1')
    {
        count++;
        if (count==5)
        {
            result+='0';
            count=0;
        }
    }
    else
    {
        count=0;
    }
}
cout<<result<<endl;
return 0;
}