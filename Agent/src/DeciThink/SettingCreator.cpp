#include <iostream>
#include "Configure.h"
using namespace std;

int main()
{
  string Filename , Formation , Kicker , NonKicker;
  cout<<"\nEnter FileName : ";
  cin>>Filename;
  cout<<"\nEnter Formation : ";
  cin>>Formation;
  cout<<"\nEnter Kicker Flags : ";
  cin>>Kicker;
  cout<<"\nEnter NonKicker Flags : ";
  cin>>NonKicker;

  Configure().CreateConfigureFile(Filename , Formation , Kicker , NonKicker);
}
