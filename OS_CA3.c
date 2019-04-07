#include<stdio.h> 
void longest_remaining_time_first(int num,int remaining_time[10],int Current_time,int arrival_time[10], int burst_time[10],int wait_time,int tut_time);
int wait_time=0,tut_time=0,Current_time1=0;
main() 
{
	int Process_no,num,Current_time,Remaining_process,flag=0,time_quantum,wait_time=0,tut_time=0,arrival_time[10],burst_time[10],remaining_time[10],x=1;
	printf("Enter the number of processes "); 
	scanf("%d",&num);
	Remaining_process = num;
	
	//LOOP FOR TAKING USER INPUTS FOR ARRIVAL TIME AND BURST TIME OF PROCESSES
	for(Process_no = 0;Process_no < num;Process_no++) 
	{
	printf("\nEnter arrival time and burst time of Process %d\n",Process_no+1);
	printf("Arrival time : ");
	scanf("%d",&arrival_time[Process_no]);
	printf("Burst time : ");
	scanf("%d",&burst_time[Process_no]);
	remaining_time[Process_no]=burst_time[Process_no];	
	} 
	
	time_quantum=6;
	Current_time=0;
	printf("\nOrder of processes in queue and their remaining CPU Bursts\n");
	printf("\nTime Quantum = 6\n");
	printf("\nPROCESS\t\tREMAINING BURST TIME\t\tCURRENT TIME");
	
	//LOOP FOR FIRST AND SECOND ITERATION HAVING TIME QUANTUM 6 AND 10 RESPECTIVELY
	for(Process_no=0;Remaining_process!=0;) 
	{
		if(remaining_time[Process_no]<=time_quantum && remaining_time[Process_no]>0)		//IF BURST TIME IS LESS THAN TIME QUANTUM
		{ 
			Current_time+=remaining_time[Process_no]; 	
			remaining_time[Process_no]=0; 																			
			flag=1; 
		} 
		else if(remaining_time[Process_no]>0)												//IF BURST TIME IS GREATER THAN TIME QUANTUM
		{ 
			remaining_time[Process_no]-=time_quantum; 
			Current_time+=time_quantum; 	
			printf("\nP%d",Process_no+1); 
			printf("\t\t\t%d",remaining_time[Process_no]);
			printf("\t\t\t%d",Current_time);
		} 
		if(remaining_time[Process_no]==0 && flag==1)					//IF BURST TIME IS EQUAL TO ZERO i.e. PROCESS FINISHED ITS EXECUTION
		{ 
			Remaining_process--;	
			printf("\nP%d",Process_no+1); 
			printf("\t\t\t%d",remaining_time[Process_no]);
			printf("\t\t\t%d",Current_time);
			Current_time1=Current_time;
			wait_time+=Current_time-arrival_time[Process_no]-burst_time[Process_no]; 
			tut_time+=Current_time-arrival_time[Process_no]; 
			flag=0;            
		} 
		if(Process_no==num-1)									//IF PROCESS NUMBER IS EQUAL TO NUMBER OF PROCESSES CHANGE TIME QUANTUM TO 10
		{
			x++;
			if(x==2)
			{
				Process_no=0;
				time_quantum=10;
				printf("\n\nTime quantum = 10. \n");
			}
			else
			{
				break;
			}
		}
		else if(Current_time >= arrival_time[Process_no+1])			//IF CURRENT TIME BECOMES GREATER THAN THE ARRIVAL TIME OF NEXT PROCESS
		{
			Process_no++;
		}
		else
		{
			Process_no=0;
		}
	}
	longest_remaining_time_first(num,remaining_time,Current_time,arrival_time,burst_time,wait_time,tut_time);
	return 0;
}
void longest_remaining_time_first(int num,int remaining_time[10],int Current_time,int arrival_time[10], int burst_time[10],int wait_time,int tut_time)
{	
	float avg_wait,avg_tut;
    int i,j,n=num,temp,btime[20],bur_time[20],Process_no[20],w_time[20],tut_t[20],sum=0,total=0,loc;
    printf("\n\nThird iteration in which that process is executed which requires more time to go in termainated state is\n");
    
    //LOOP FOR CALCULATING WAITING TIMES AND REMAINING BURST TIME OF ALL THE PROCESSES AFTER SECOND ITERATION
    for(i=0;i<n;i++)
    {
    	bur_time[i]=remaining_time[i];
        btime[i]=burst_time[i];
        w_time[i]=Current_time-arrival_time[i]-btime[i];
		Process_no[i]=i+1;
    }
    
    //LOOP FOR GIVING PROCESSOR TO PROCESS WHICH NEEDS MORE TIME TO GO IN TERMINATED STATE
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(bur_time[j+1]>bur_time[j])
			{
            	temp=bur_time[j];
       			bur_time[j]=bur_time[j+1];
        		bur_time[j+1]=temp;
        		temp=burst_time[j];
       			burst_time[j]=burst_time[j+1];
        		burst_time[j+1]=temp;
        		temp=Process_no[j];
        		Process_no[j]=Process_no[j+1];
        		Process_no[j+1]=temp;
        		temp=arrival_time[j];
        		arrival_time[j]=arrival_time[j+1];
        		arrival_time[j+1]=temp;
            }
        }    
    }

    printf("\nPROCESS\t\t  REMAINING BURST TIME\t\tCURRENT TIME\t\tWAITING TIME\t\tTURNAROUND TIME");
    
    //CALCULATING TURNAROUND TIME AND WAITING TIME OF ALL PROCESSES AFTER THIRD ITERATION
    for(i=0;i<n;i++)
    {
    	
        if(bur_time[i]==0)
        {
        	Current_time=Current_time1;
        	w_time[i]=wait_time;
        	tut_t[i]=tut_time;
		}
		
		else{
		btime[i]=burst_time[i];
    	Current_time+=bur_time[i];
    	tut_t[i]=Current_time-arrival_time[i];
        sum=sum + tut_t[i];
        w_time[i]=tut_t[i]-burst_time[i];
        total=total+w_time[i];
    	
    	}
    	printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",Process_no[i],bur_time[i],Current_time,w_time[i],tut_t[i]);
    }
    avg_tut=(float)sum/n;
    avg_wait=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\nAverage turnaround time = %f\n",avg_tut);	
}
