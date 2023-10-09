#include<iostream>
#include<cstdlib>
#include<bits/stdc++.h>
#include<windows.h> 
using namespace std;

void gbn(int ws,int nf)
{
    ws =pow(2,ws)-1;
    cout<<"Window size: "<<ws<<endl;
	int tr(0);
	srand(100);
     
	int i=1;

	while(i<=nf)
	{
		int inc=0;

		for(int j=i;j<i+ws && j<=nf;j++)
		{
			cout<<"Sent frame "<<j<<endl;
			tr++;
            Sleep(1000);
		}

		for(int j=i;j<i+ws && j<=nf;j++)
		{
			int flag = rand()%2;

			if(!flag)
			{
				cout<<"Ack. received for "<<j<<endl;
				tr++;
				inc++;
                Sleep(1000);
			}
			else{
				cout<<"Ack failed for "<<j<<endl;
                Sleep(1000);
				cout<<"Restransmitting the window"<<endl;
                Sleep(1000);
				break;
			}
		}
		i = i +inc;
		cout<<endl;
        cout<<"<---Window slided--->"<<endl;
		cout<<endl;

	}

//	cout<<"Total transmissions"<<tr;
}
void selective(int ws, int nf)
{
     ws =pow(2,ws-1);
    cout<<"Window size: "<<ws<<endl;
		int MAX_INPUT=1000;
	srand(100);
	
	int drop_pack[nf+1];
	int ack_rec =0;
	int last_pack =0;
	int last_pack_ack = last_pack;
	int insertHere = 1;
	int i=1;

	for(int i=0;i<=nf+1;i++)
	{
		drop_pack[i]=MAX_INPUT;
	}

	while(ack_rec < nf)
	{

		for (int i = 1; i <= ws && ack_rec < nf; i++) {
    if (drop_pack[i] != MAX_INPUT) {
        // Frame has not been acknowledged, so it can be retransmitted.
        cout << "Sent frame " << drop_pack[i] << endl;
        Sleep(1000);
    } else {
        // All frames within the window have been acknowledged, so don't send new frames.
        if (last_pack == nf) {
            continue;
        }
        cout << "Sent frame " << last_pack + 1 << endl;
        last_pack++;
        insertHere++;
        Sleep(1000);
    }
}



		for(int i=1;i<=ws && ack_rec<nf;i++)
		{
			int flag = rand()%2;
			if(!flag)
			{
				if(drop_pack[i]!=MAX_INPUT)
			{
				cout<<"Ack received for frame "<<drop_pack[i]<<endl;
                Sleep(1000);
				drop_pack[i]=MAX_INPUT;
			}
			else{
				if(last_pack_ack==nf)
					continue;
				cout<<"Ack received for frame "<<last_pack_ack+1<<endl;
                Sleep(1000);
				last_pack_ack++;
			}
			ack_rec++;
			cout<<endl;
			cout<<"<---Window slides--->"<<endl;
			cout<<endl;
			}
			else{
				if(drop_pack[i]!=MAX_INPUT)
			{
				cout<<"Ack failed for frame "<<drop_pack[i]<<endl;
                Sleep(1000);
			}
			else{
				if(last_pack_ack==nf)
					continue;
				cout<<"Ack failed for frame "<<last_pack_ack+1<<endl;
                Sleep(1000);
				drop_pack[insertHere]=last_pack_ack+1;
				last_pack_ack++;
				insertHere++;
			}
			}
		}

		sort(drop_pack+1,drop_pack+nf+1);
		for(int i=1;i<=nf+1;i++)
		{
			if(drop_pack[i]==MAX_INPUT)
			{
				insertHere=i;
				break;
			}
		}

	}
}

int main()
{
	int choice;
    int nf,ws;
    cout<<"Enter the no of frames :";
	cin>>nf;
	cout<<"Enter the no of bits :";
	cin>>ws;
	
	while(1)
	{
		cout<<"\n1.Go-Back-N\n2.Selective Repeat\n3.Exit"<<endl;
		cin>>choice;
		if(choice==1)
		{
			gbn(ws,nf);
		}
		else if(choice==2)
		{
			selective(ws,nf);
		}
		else if(choice==3)
		{
			exit(0);
		}
	}
}