/* PROGRAMMING PROJECT

CSCI 3300 OPERATING SYSTEM  SECTION 01 
--------------------------------------

Muhammad Muhaimin Bin Mazni (leader)  (1917953)
Muhammad Nasrullah Bin Mat Radzi       (2013677) 
Aneesa Nadira Binti Aminuddin          (2016174)
Rabiatul Adawiyah Binti Mohammad Azmi  (2013214)
*/

#include <iostream>
#include<stdlib.h>
using std::cout;
using std::cin;
using std::endl;

 const int n = 5; // Number of processes
 const int m = 3; // Number of resources
 
 int alloc[n][m]; // Allocation Matrix
 int max[n][m];  // MAX Matrix
 int avail[m];  // Available Resources
 
 int need[5][3];
 int safeSeq[5];
 bool cal();
 void showResult();
 void request();
 
int main(){
 cout << "Enter the number of resources of each type:\n";
    for(int i = 0; i < m; i++){
        cin >> avail[i];
    }
 
    cout << "\nEnter the maximum matrix:\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> max[i][j];
        }
    }
 
    cout << "\nEnter the allocation matrix:\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> alloc[i][j];
        }
    }
 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
            avail[j] -= alloc[i][j];
        }
    }
    
 cal();
 showResult();
 request();

    return (0);
}




bool cal(){
    int finish[n], ind = 0;
    for (int k = 0; k < n; k++) { 
        finish[k] = 0;     
    }
  
    for (int i = 0; i < n; i++) {     //find need matrix
       for (int j = 0; j < m; j++) {
           need[i][j] = max[i][j] - alloc[i][j];
        }
   }
   	
	int y = 0;
    for (int k = 0; k < 5; k++) {
      for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
        	
           int flag = 0;
           for (int j = 0; j < m; j++) {
               if (need[i][j] > avail[j]){
               flag = 1;
               break;
            }
        }
        if (flag == 0) {
          safeSeq[ind++] = i;
          for (y = 0; y < m; y++)
            avail[y] += alloc[i][y];
          finish[i] = 1;
        }
      }
    }
  }
	if(sizeof(safeSeq)/sizeof(safeSeq[0])){
	 	return true;
	} else{
		return false;
	}	
}
	
    
void showResult(){
	if(sizeof(safeSeq)/sizeof(safeSeq[0])){
		printf("\n The system is in safe state.\n");
        printf(" -Following is the SAFE Sequence: \n");
        for (int i = 0; i < n - 1; i++) {
            printf(" Thread%d , ", safeSeq[i]);
		}
        printf(" Thread%d\n", safeSeq[n - 1]);
    }else{
    	printf("\n The following system is not safe.\n");
    	printf(" -No SAFE Sequence-\n");
	}
}


void request(){
	int resp, pid, request[5][3], i;
    printf("\n Do you want make an additional request for any of the process ? (1=Yes|0=No) ");
    scanf("%d", &resp);
    
    if (resp == 1) {
        printf("\n Enter request such as : (process_number  Request_resource_1  Request_resource_2  Request_resource_3)\n ");
        scanf("\n%d %d %d %d", &pid,&request[0][0],&request[0][1],&request[0][2]);
    
        
        for (i = 0; i < m; i++) {
            if (request[0][i] > need[pid][i]) {
            	
            	printf("\n -1\n");
                exit(0);
                
            }else {
            	
            	if (request[0][i] <= avail[i]) {
                    for (i = 0; i < m; i++) {
				        avail[i] -= request[0][i];
                        alloc[pid][i] += request[0][i];
                        need[pid][i] -= request[0][i];
                    }   
                    
                    if (cal() == true){
                    	printf("\n 0\n");
                    	showResult();
					}
				}
			}     
        }
	} 
	else {	
        exit(0);
    }
}


