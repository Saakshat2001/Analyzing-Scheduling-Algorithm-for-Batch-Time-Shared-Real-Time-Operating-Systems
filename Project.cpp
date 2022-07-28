#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm>
using namespace std;
struct Process
{
    int pid;
    int bt;
    int priority;
};

bool comparison(Process a, Process b)
{
    return (a.priority>b.priority);
}

void findWaitingTimeP(Process proc[], int n, int wt[]){
	
   wt[0] = 0;
   for (int i=1;i<n;i++)
      wt[i] = proc[i-1].bt + wt[i-1];
}

void findTurnAroundTimeP( Process proc[], int n, int wt[], int tat[])
{
   for (int i = 0; i< n ; i++)
   tat[i] = proc[i].bt + wt[i];
}

void findavgTimeP(Process proc[], int n)
{
   int wt[n], tat[n], total_wt = 0, total_tat = 0;
   findWaitingTimeP(proc, n, wt);
   findTurnAroundTimeP(proc, n, wt, tat);
   cout<< "\nProcesses "<< " Burst time "<< " Waiting time " << " Turn around time\n";
   for (int i=0; i<n; i++)
   {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout<< " " << proc[i].pid<< "\t\t"<< proc[i].bt<< "\t " <<wt[i]<< "\t\t " << tat[i] <<endl;
   }
   cout<< "\nAverage waiting time: " << (float)total_wt / (float)n;
   cout<< "\nAverageturn around time: "<< (float)total_tat / (float)n;
} 

void priorityScheduling(Process proc[], int n)
{
   std::sort(proc, proc + n, comparison);
   cout<< "Order of execution of processes: \n";
   for (int i = 0 ; i< n; i++)
      cout<< proc[i].pid<<" " ;
   findavgTimeP(proc, n);
}

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum){
   int rem_bt[n];
   for (int i = 0 ; i< n ; i++)
      rem_bt[i] = bt[i];
   int t = 0;
   while (1)
   {
      bool done = true;
      for (int i = 0 ; i< n; i++)
      {
        if (rem_bt[i] > 0)
        {
          done = false;
          if (rem_bt[i] > quantum)
          {
            t += quantum;
            rem_bt[i] -= quantum;
          } 
		  else
          {
          t = t + rem_bt[i];
          wt[i] = t - bt[i];
          rem_bt[i] = 0;
          }
        }
      }
      if (done == true)
      break;
   }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
   for (int i = 0; i< n ; i++)
   tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int quantum){
   int wt[n], tat[n], total_wt = 0, total_tat = 0;
   findWaitingTime(processes, n, bt, wt, quantum);
   findTurnAroundTime(processes, n, bt, wt, tat);
   cout<< "Processes "<< " Burst time " << " Waiting time " << " Turn around time\n";
   for (int i=0; i<n; i++)
   {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout<< " " << i+1 << "\t\t" <<bt[i] <<"\t "<<wt[i] <<"\t\t " <<tat[i] <<endl;
   }
   cout<< "Average waiting time: "<< (float)total_wt / (float)n;
   cout<< "\nAverageturn around time: "<< (float)total_tat / (float)n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int ch;
    cout<<"1.Time Shared Systems\n2.Batch Systems\n3.Real time systems"<<endl;
    cout<<"Enter your choice: ";
    cin>>ch;
    switch(ch)
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 
   {
   	
    case 3:
    {
        int n;
        cout<<"Enter the no of processes: ";
        cin>>n;
        int bt[n],p[n],s[n],wt[n],tat[n],ts,its[n],tq[n][n],rbt[n],ord[n];
        for(int i=0; i<n; i++)
        {
        	
            wt[i]=tat[i]=0;
            s[i]=1;
            for(int j=0; j<n; j++)
			   tq[i][j]=0;
        }
        cout<<"Enter the initial time slice: ";
        cin>>ts;
        for(int i=0; i<n; i++)
        {
            ord[i]=i+1;
            cout<<"Enter the burst time for process "<<i+1<<": ";
            cin>>bt[i];
            cout<<"Enter the priority of process "<<i+1<<": ";
            cin>>p[i];
        }
        int flag=0,j=0;
        for(int i=0; i<n-1; i++)
            for(int j=0; j<n-1; j++)
                if(bt[j]>bt[j-1])
                {
                    int t=bt[j];bt[j]=bt[j+1];
                    bt[j+1]=t;
                    t=p[j];
                    p[j]=p[j+1];
                    p[j+1]=t;
                    t=ord[j];
                    ord[j]=ord[j+1];
                    ord[j+1]=t;
                }
        for(int i=0; i<n; i++)
            p[i]+=i;
        for(int i=0; i<n-1; i++)
            for(int j=0; j<n-1; j++)
                if(p[j]>p[j+1])
                {
                    int t=bt[j];
                    bt[j]=bt[j+1];
                    bt[j+1]=t; t=p[j];
                    p[j]=p[j+1];
                    p[j+1]=t;
                    t=ord[j];
                    ord[j]=ord[j+1];
                    ord[j+1]=t;
                }
        for(int i=0; i<n; i++)
            rbt[i]=bt[i];
        while(!flag)
        {
            for(int i=0; i<n; i++)
            {
                if(p[i]>0.67*n) 
				    p[i]=0;
                else if(p[i]>0.33*n) 
				    p[i]=1;
                else 
				    p[i]=2;
                if(i!=0)
                    if((bt[i]-bt[i-1])>0) s[i]=0;
                        its[i]=ts+bt[i]+s[i]+p[i];
                    if(j==0)
                    {
                        if(s[i]==1)
                            tq[j][i]=its[i];
                        else
                            tq[j][i]=ceil(0.5*(float)its[i]);
                        if(rbt[i]<tq[j][i])
                            tq[j][i]=rbt[i];
                        rbt[i]=rbt[i]-tq[j][i];
                    }
                    else
                    {
                        if(rbt[i]<=0)
                            tq[j][i]=0;
                        else if(s[i]==1)
                            tq[j][i]=2*tq[j-1][i]; 
						else
                            tq[j][i]=1.5*tq[j-1][i];
                        if(rbt[i]<tq[j][i])
                            tq[j][i]=rbt[i];
                        rbt[i]=rbt[i]-tq[j][i];
                    }
            } 
            j++;
            flag=-1;
            for(int i=0; i<n; i++)
                if(rbt[i]>0)
                    flag=0;
        }
        cout<<"\nProcess no.:\n";
        for(int i=0; i<n; i++)
            cout<<setw(5)<<ord[i];
        cout<<"\nBurst Times for the processes:\n";
        for(int i=0; i<n; i++)cout<<setw(5)<<bt[i];
            cout<<"\nIntelligent Time Slices for the processes:\n";
        for(int i=0; i<n; i++)
            cout<<setw(5)<<its[i];
        cout<<"\nDynamic Time Quantums for the processes:\n";
        for(int x=0; x<j; x++)
        {
            cout<<"Round no "<<x+1<<": "<<endl;
            for(int y=0; y<n; y++)
                cout<<setw(5)<<tq[x][y];
            cout<<endl;
        }
        for(int x=0; x<n; x++)
        {
            flag=-1;
            for(int y=0; y<j; y++)
            {
                for(int z=0; z<n; z++) {
                    if(z!=x)
                        wt[x]+=tq[y][z];
                    else if(z==x&&tq[y+1][z]==0)
                    {
                        flag=0;
                        break;
                    }
                }
                tat[x]+=tq[y][x];
                if(flag==0)
                    break;
            }
            tat[x]+=wt[x];
        }
        cout<<"\nWT for the processes:\n";
        for(int i=0; i<n; i++)
            cout<<setw(5)<<wt[i];cout<<"\nTAT for the processes:\n";
        for(int i=0; i<n; i++)
            cout<<setw(5)<<tat[i];
        float avwt=0,avtat=0;
        for(int i=0; i<n; i++)
        {
            avwt+=wt[i];
            avtat+=tat[i];
        }
        avwt/=n;
        avtat/=n;
        cout<<"\n\nAverage waiting time: "<<avwt<<endl;
        cout<<"\nAverage turnaround time: "<<avtat<<endl;
   }
   break;
 
 //////////////////////////////////////////////////////////////////////////////////////////////////
 
    case 2:
    {
        int n;
        cout<<"Enter no of processes: ";cin>>n;
        Process proc[n];
        for(int i=0;i<n;i++)
        {
            cout<<"Enter pid: ";
            cin>>proc[i].pid;
            cout<<"Enter the burst time: ";
            cin>>proc[i].bt;
            cout<<"Enter the priority of process: ";
            cin>>proc[i].priority;
        }
        priorityScheduling(proc, n);
    }
	break;
 
 //////////////////////////////////////////////////////////////////////////////////////////////////
 
    case 1:
    {
        int n;
        cout<<"Enter no of processes: ";
        cin>>n; 
		int processes[n],burst_time[n];
        int quantum;
        for(int i=0;i<n;i++)
        {
            cout<<"Enter the burst time of process "<<(i+1)<<": ";
            cin>>burst_time[i];
        }
        cout<<"Enter Time Quantum: ";
        cin>>quantum;
        findavgTime(processes, n, burst_time, quantum);
    }
	break;
   }
}
