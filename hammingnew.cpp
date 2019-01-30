#include<iostream>
using namespace std;

int main()
{
    int m;
    int r;
    int input[30];

    cout<<"Frame size:\n";
    cin>>m;

    int i,j,k;

    cout<<"Enter Frame Bits :\n";
    for (i=0;i<m;i++)
    {
        cin>>input[i];
    }

    cout<<"Enter number of redundant bits to be introduced:\n";
    cin>>r;

    cout<<"\nFrame :\n ";
    for(i=0;i<m;i++)
    {
        cout<<input[i]<<" ";
    }

    //Reverse input[] for further processing
    int temp[30];
    for (i=m-1,j=0;i>=0;i--,j++)
    {
        temp[j]=input[i];
    }
    for (i=0;i<m;i++)
    {
        input[i]=temp[i];
    }

    /* Redundancy bits */
    int nrb=0;      // Counter for number of redundancy bit
    int rb[8];      // Array to hold redundancy bits

    /* New Frame after introducing redundancy bits */
    int l=0;        // Length of new frame = l = m+r
    int transmit[30];     // New frame

    // Introduce redundancy bits and construct new frame
    k=1;
    for(i=1,j=0;j<m;i++)
    {
        //If it is location of redundancy bit
        if(i==k)
        {
            transmit[i]=-1;
            k=k*2;
            nrb++;
        }
        //If it is location of data bit
        else
        {
            transmit[i]=input[j];
            j++;
        }
        l++;
    }

    cout<<"\n";
    cout<<"\n Frame initialised with redundancy bits :\n ";
    for(i=l;i>0;i--)
    {
        cout<<transmit[i]<<" ";
    }

    //Some more temp variables and arrays
    int i1,i2,i3,i4,i5,i6,i7;
    int a1[4],a2[4];

    i5=0;       //Holds position of rb[]

    //Scan Whole frame and calculate all redundancy bits
    for(i1=1;i1<=l;i1++)
    {
        //check if it is redundancy bit which is to be calculated
        if(transmit[i1]==-1)
        {
            //Get the position of 1 from binary representation
            i4 = -1;    //Hold position of 1

            //Converting redundancy bit position into binary form and get position of 1
            i7=i1;
            while (i7>0)
            {
                i4++;
                if(i7==1)
                {
                    break;
                }
                else
                {
                    i7=i7/2;
                }
            }

            i3=0; // Consider even parity

            //Calculating redundancy bit and parity
            for(i2=1;i2<=l;i2++)
            {
                //reset a1 frame
                for(i6=0;i6<4;i6++)
                {
                    a1[i6]=-1;
                }

                //find binary conversion for each position
                i7=i2;
                i6=0;
                while(i7>0)
                {
                    if(i7==1)
                    {
                        a1[i6]=1;
                        break;
                    }
                    else if(i7==0)
                    {
                        a1[i6]=0;
                    }
                    else
                    {
                        a1[i6]=i7%2;
                        i7=i7/2;
                    }
                    i6++;
                }

                //check that the binary conversion is having bit at specific position or not
                //if yes calculate parity

                if(a1[i4]==1)
                {
                    if(transmit[i2]==1)
                    {
                        i3++;
                    }
                }

            }

            //Display Parity
            //Add redundancy bit in data frame
            //odd parity -> 1 :: even parity -> 0

            if(i3%2==0)
            {
                transmit[i1]=0;
                rb[i5]=0;
            }
            else
            {
                transmit[i1]=1;
                rb[i5]=1;
            }
            i5++;

            //Print current frame
            cout<<"\n r"<<i5<<" = "<<rb[i5-1];

        }

    }
    cout<<"\n\nFrame to be transmitted:\t";
    for(i2=l;i2>0;i2--)
    {
        cout<<" "<<transmit[i2];
    }

    //Get the error bit
    int eb;
    cout<<"\n";
    cout<<"\n Enter bit number to invert (simulate error): ";
    cin>>eb;

    cout<<"\n Bit at position "<<eb<<" is "<<transmit[eb];

    //Change bit
    if(transmit[eb]==1)
    {
        transmit[eb]=0;
    }
    else
    {
        transmit[eb]=1;
    }

    cout<<" and now changed to "<<transmit[eb];

    // Print new frame after changing the bit
    cout<<"\n New Frame is";
    for(i=l;i>0;i--)
    {
        cout<<" "<<transmit[i];
    }



    i5=0;
    k=1;

    for(i1=1;i1<=l;i1++)
    {

        if (i1==k)
        {

            i4 = -1;

            //Converting redundancy bit into binary form and get position of 1
            i7=i1;
            while (i7>0)
            {
                i4++;
                if(i7==1)
                {
                    break;
                }
                else
                {
                    i7=i7/2;
                }
            }

            i3=0; // Consider even parity

            //Calculating redundancy bit and parity
            for(i2=1;i2<=l;i2++)
            {
                //reset a1 frame
                for(i6=0;i6<4;i6++)
                {
                    a1[i6]=-1;
                }

                //find binary conversion
                i7=i2;
                i6=0;
                while(i7>0)
                {
                    if(i7==1)
                    {
                        a1[i6]=1;
                        break;
                    }
                    else if(i7==0)
                    {
                        a1[i6]=0;
                    }
                    else
                    {
                        a1[i6]=i7%2;
                        i7=i7/2;
                    }
                    i6++;
                }

                //check that the binary conversion is having bit at specific position or not
                //if yes calculate parity

                if(a1[i4]==1)
                {
                    if(transmit[i2]==1)
                    {
                        i3++;
                    }
                }

            }

            //Display Parity
            //Add redundancy bit in data frame
            //odd parity -> 1 :: even parity -> 0

            if(i3%2==0)
            {
                transmit[i1]=0;
                rb[i5]=0;
            }
            else
            {
                transmit[i1]=1;
                rb[i5]=1;
            }

            i5++;

            k=k*2;
        }

    }

    cout<<"\n Redundancy bits:";
    for(i=0;i<nrb;i++)
    {
        cout<<" "<<rb[i];
    }

    //Calculate error position
    int ep=0;
    for(i=0,j=1;i<nrb;i++)
    {
        if(rb[i]==1)
        {
            ep=ep+j;
        }
        j=j*2;
    }

    cout<<"\n Error is at : "<<ep;

    return 0;
}
