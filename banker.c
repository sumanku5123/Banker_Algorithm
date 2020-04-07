#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//----------------------Variable declaration-------------------------

int n;
int r;
int i,j,k,c,cnt;
int available[15],p[15];
int needed[15][15],allocate[15][15],maximum[15][15];
void *input();
void *output();
pthread_mutex_t s;


//-----------------------Main method------------------------


int main()
{
pthread_mutex_init(&s,NULL);
pthread_t p1,p2;
pthread_create(&p1,NULL,&input,NULL);
pthread_create(&p2,NULL,&output,NULL);
pthread_join(p1,NULL);
pthread_join(p2,NULL);
}
void *input()
{
pthread_mutex_lock(&s);                                //mutex lock for smooth handle of data variable
printf("\nEnter number of process :");                 //input no. of process
scanf("%d",&n);
printf("\nEnter  resources available : ");
scanf("%d",&r);
printf("\nEnter insatnces for resources :\n");
for(i=0;i<r;i++)
{
printf("Resource %d\t ",i+1);
scanf("%d",&available[i]);
}

//           ----------------allocation of resource to process                


printf("\n Enter allocation of resource followed by space  \n");
for(i=0;i<n;i++)
{
printf("process  %d\t ",i+1);
p[i]=0;
printf("\t");
for(j=0;j<r;j++)
{
scanf("%d",&allocate[i][j]);
}
}
printf("\nEnter max allocated resource followed by space  \n");
for(i=0;i<n;i++)
{
printf("process  %d",i+1);
printf("\t");
for(j=0;j<r;j++)
{
scanf("%d",&maximum[i][j]);
}
}

//--------------------------------------------needed resources by process -------------------------


printf("needed resource matrix\n");
for(i=0;i<n;i++)
{
printf("process %d",i+1);
printf("\t");
for(j=0;j<r;j++)
{
needed[i][j]=maximum[i][j]-allocate[i][j];
printf("\t%d",needed[i][j]);
}
printf("\n");
}
k=0;
cnt=0;
printf("\n\n safe sequence\n");
pthread_mutex_unlock(&s);
}
void *output()
{
pthread_mutex_lock(&s);

//-----------------------------------------check if needed is less than available---------------------------------


while(k<15)
{
for(i=0;i<n;i++)
{
c=0;
for(j=0;j<r;j++)
{
if(p[i]==1)
break;
if(needed[i][j]<=available[j])
{
c++;
}


//--------------------------------------if procees complete then added the release resource to available resource---------------


if(c==r)
{
for(j=0;j<r;j++)
{
available[j]+=allocate[i][j];
}
printf("process%d\t",i+1);
p[i]=1;
cnt++;
}
}
}
k++;
}
printf("\n");

// ----------------------------------------if deadlock occur----------------------------------
if(cnt<n-1)
{
printf("\n not found i.e. deadlock\n ");
}
}

