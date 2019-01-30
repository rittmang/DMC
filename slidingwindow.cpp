#include<iostream>
using namespace std;


int main()
{
  int w,f;
  input: cout<<"\nEnter size of window:";
  cin>>w;

  cout<<"Enter number of frames:";
  cin>>f;

  if(w>f)
  {
    cout<<"Window size larger. Choose a smaller window size.";
    goto input;
  }
  int frame[f+1];


  cout<<"Enter "<<f<<" elements:\n";
  for(int i=1;i<=f;i++)
  {
enter:   cin>>frame[i];

      for(int j=1;j<i;j++)
      {
        if(frame[j]==frame[i])
        {
          cout<<"Frame number already present. Re-enter:";
          goto enter;
        }
      }
  }
  cout<<"------------------------------------\n\n";
  for(int i=1;i<=f;i++)
  {
    if(i%w==0)
    {
      cout<<frame[i]<<"\t";
      cout<<"\nAcknowledgement of above frames sent is received by sender\n---------------------\n";

    }
    else
      cout<<frame[i]<<"\t";

  }
  if(f%w!=0)
    cout<<"\nAcknowledgement of above frames sent is received by sender\n\n";

  return 0;
}
