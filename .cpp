// Explanation of the code..
//                    
//                      ^            
// half plane 1 -----  / \    ---------->     Plane1 m= 0   Nmaxx= 1 triangle --> 4 bit
//                    *---*  
// half plane 2 ---- / \ / \  ---------->     Plane2 m= 1   Nmaxx= 3 triangles--> 4x3  bit
//                  *---*---*           
// half plane 3----/ \ / \ / \  -------->     Plane3 m= 2   Nmaxx= 5 triangles--> 4x5 bit
//                *---*---*---*
// half plane 4- / \ / \ / \ / \ ------->     Plane4 m= 3   Nmaxx= 7 triangles--> 4x7 bit  <--lower plane--> Nmaxx=Nmax triangles
//              *---*---*---*---*        ----------------------------------------------------
//                                          Total triangles: totalTriangles= 16  Total bit--> totalBit= 64 bit
//                                          Total planes = 4--> [0;P-1]
//----------------------------| 
//STEP 1 PYRAMID CONSTRUCTION |
//----------------------------|                               
//               STANDARD PYRAMID                           PYRAMID FROM MY OUTPUT ALGORITHM               SEQUENCE OUT OF MY ALGORITHM 
//                                             (straight triangles before and overturned triangles after)   (start sequence from vertex)
//
//Upper                ^                                                ^
//half plane 1        /0\ <-->vertex of triangle(1 bit)                /0\  <--->vertex of triangle                           
//Lower              *---*   ---------------->  Plane1 m= 0 ---->     *---*  --------------------------------->   0110 
//half plane 1      /1\1/0\ <-->base of triangle(3 bit)              /1\1/0\ <---->base of triangle
//Upper            *---*---*                                        *---*---*     *---*---*
//half plane 2    /0\1/0\1/1\                                      /0\     /1\     \1/0\1/
//Lower          *---*---*---*  ------------>  Plane2 m= 1 -----> *---*   *---*     *---* ----------------------> 0011 1010 1101
//half plane 2  /0\1/1\1/0\1/0\         straight triangle----->  /0\1/1\ /0\1/0\     \1/  <---overturned triangle
//             *---*---*---*---*                                *---*---*---*---*     *
//                                                                       
//// \\\\\\\\\\\\\\\\\\\\\\\\\\                    
//STEP 2 PYRAMID TRASFORMATION\ (Transformation of triangles trough karnaugh's map)
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                                                     
//
//Sequence out from algorithm in Step 1 is the input sequence for Step 2.
//NOTE: As the output sequence in STEP 1 is inverted I have construct karnaugh's map of 4 variables in this way:
// Input           Output                                                                          
// z w y x  ---->  X Y W Z   So after STEP 2, output sequence is in the correct order for each plan of the pyramide
//TRANSFORMATION:
// x -->X 
// y-->Y
// w-->W
// z-->Z
//
////\\\\\\\\\\\\\\\\\\\\\\\                  
//STEP 3 PYRAMID REDUCTION\  
//\\\\\\\\\\\\\\\\\\\\\\\\\
//
//I control for each plan all triangles. If they are all 1 or all 0 I reduct the pyramide.
//If they aren't I write pyramide in a vector to iterate algorithm
//

#include <stdio.h>   
#include <stdlib.h>

char inputChars;//input characters
int totalTriangles;//Total triangles
int totalBit ;//Total bit
int copia;// copy of M
int controllo =0;//iteration control

char *inputVector=(char*) malloc (sizeof(char));//dinamic memory for input characters


main ()
{     
     printf("Tribit PROGRAM \n");
     printf("\n");
     printf("Insert binary number..\n");  
     printf("Note...  Number of digits must be a power of 4..\n");
     int contat=0;
       while((inputChars = getchar()) != '\n'  ){ //save input
       inputVector[contat] =(int(inputChars) - 48);         //conversion from character to integer  (Vector of total bits insert)
       char *inputVector=(char*) malloc (contat*sizeof(char));    //dinamic memory allocation
       contat=contat+1;                  //increment to calculate digits
       }
       totalBit=contat; //Total bits insert
        printf("Number of digits insert: %d\n", totalBit);
        int contacicli =0 ; 
        copia =totalBit;
     //Number of digits control
      while (((copia % 4) == 0) && copia > 1){ /* While x is multiple of 4 and  > 1 */           
        copia /= 4;       
          }
     if ((copia!=1)|| totalBit==1){
             controllo =1;
             printf("Note...  Number of digits must be a power of 4....\n");   
                }
        int revinputVector[totalBit]; //Declaration  Vector of total bits insert
                 
     while(controllo==0){      //Loop to alghorithm convergence                   
      contacicli = contacicli+1; 
      //printf("\n");
      printf("CICLE NUMBER......................... %d\n",contacicli);
      // V is an inversion of Vector R to fill Matrix T[ir][jr] from the top
       for(int i=0; i<=totalBit-1; i++)
        {        
       revinputVector[i]=inputVector[totalBit-i-1];
       }     
       printf("\n");
     
        int ir,jr;
      //I calculate dimensions of pyramid
      int local1=1; int local2=0; int S=1; int local3=0;  int local4; totalTriangles=0;
       while( S >0){           //until S>0 do..       
           S = (totalBit/4)-local1-local2;  //when I calculate total planes S became zero
            local2=local1+local2;
            local1=local1+2;
            local3=local3+1;    //total planes
            local4=local1-2;   //lower plane triangles
            totalTriangles=local4 +totalTriangles;    //total triangles
                 } 
       int  P = local3;//I save total planes
       int Nmax =  local4; //I save number of triangles in the lower plane  
                  
      //printf("Number of total triangles of the Pyramid=%d\n", tr);
      //printf("The Pyramid has a number of planes P=%d\n",P);
      //printf("Number of triangles in the lower plane Nmax=%d\n", Nmax);                
         
        int start=0;  int T[ir][jr];//Matrix: ir= plane; jr= position of a bit in that plane
        // I save the first four bits of the plane number 1 in the Matrix
T[0][0]=revinputVector[0];
T[0][1]=revinputVector[1];
T[0][2]=revinputVector[2];
T[0][3]=revinputVector[3];
             //I fill the matrix T with all the others plans from the second to the lower plan
      for(int m = 1; m < P; m++) {//from the second plan (m=1) to the lower plan (m=P-1)
            int pippo =4*(2*(m-1)+1);//number of bits of each plane (m)
            start =start+ pippo;//start position of the next plane
            for(int n = start; n < (4*(2*m+1)+start);n++) {  //from the start to the end of each plane            
                  T[m][n-start]=revinputVector[n];                        //I fill the matrix T
                     }                                                                                
                     }  
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\                    
//STEP 1 PYRAMID CONSTRUCTION\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\                                   
//Statements vectors to fill them with triangles 
int z;
int w;
int vertex[ir][jr];
int a3[ir][jr];
int base[ir][jr];
int F[ir][jr];
int E[ir][jr];
int A[ir][jr];
int U[jr];
//I save the first four bits (plane1) in a new matrix F that I will order with triangles 
F[0][0]=T[0][0];
F[0][1]=T[0][1];    
F[0][2]=T[0][2];    
F[0][3]=T[0][3];
for (w=0; w<3;w++){
vertex[0][w]=0;
a3[0][w]=0;
base[0][w]=0;
}  
int q =1;
  for(z = 1; z < P; z++) {// from the second (z=1) plan to the lower plan (P-1)
        q=q+1;            //counter
        int Nmaxx =(2*(q-1))+1;  //number of triangles in the plan z
    for(w = 0; w < Nmaxx; w++) { //vectors of all vertex of triangles in the plane z          
           vertex[z][w]= T[z][4*w];   //bit 0,4,8,12..  in the plane z
            }                               
            for(int x = 0; x < Nmaxx; x++) { //vectors of all bases of triangles in the plane z        
           a3[z][3*x]= T[z][4*x+1];   //bit 1,5,9... in the plane z       
           a3[z][3*x+1]= T[z][4*x+2]; //bit 2,6,10...in the plane z          
           a3[z][3*x+2]= T[z][4*x+3]; //bit 3,7,11...in the plane z                                         
            }  
            //Now vertex sequence are ordered like straight triangles and after overturned triangles
            //So I arrange bases sequence of triangles in the same order..
                                 
            int ss=3*(((Nmaxx+1)/2)-1);//shift position to straight triangles bases in the plane z
            int sh=3*((Nmaxx+1)/2);    //number of bits of bases for straight triangles in the plane z
            for(int x = 0; x <sh; x++) {//straight triangles bases in the plane z
                   base[z][x]=a3[z][x+ss];
                  } 
             for(int x = 0; x < ss; x++) {//overturned triangles bases            
                   base[z][x+sh]=a3[z][x];
                   }                                      
                     for(int x= 0; x<Nmaxx; x++){//Now I can join sequence of vertex and sequence of bases and fill matrix F
                         int c =3*x;             //I obtain straight triangles before and overturned triangles after in matrix F
                        F[z][4*x]=vertex[z][x];
                        F[z][4*x+1]=base[z][c];
                        F[z][4*x+2]=base[z][c+1];
                        F[z][4*x+3]=base[z][c+2];
                             }                                                                                 
        }   
                                                                 
printf("\n");
printf ("STEP 1................. ");
//printf ("PYRAMIDE CONSTRUCTION.. ");
printf("\n");
int p =0; 

for(int m=0; m<P; m++) { 
//printf("Plane %d\n",m+1);
p=p+1;      
int r =(2*(p-1))+1;
for(int i=0; i<r; i++)
{
printf("%d ", F[m][4*i]) ;
printf("%d ", F[m][4*i+1]) ;
printf("%d ", F[m][4*i+2]) ;
printf("%d  ", F[m][4*i+3]) ;
}
printf("\n");
}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                    
//STEP 2 PYRAMID TRASFORMATION\  (Transformation of triangles trough karnaugh's map)
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  

p=0;
for(int m=0; m<P; m++) { // from the first (z=0) plan to the lower plan (P-1)
p=p+1;      
int r =(2*(p-1))+1;    //number of triangles in the plane m
for(int i=0; i<r; i++)
{
int c =4*i;//vector shift

//AT THE END OF THE CODE I SHOW THE CALCULATION OF Karnaugh's MAP FOR X (E[m][4*i])

E[m][4*i] = (!(F[m][1+c])&&(F[m][2+c])&&(F[m][3+c]))||((F[m][c])&&(F[m][1+c])&&(F[m][3+c]))||((F[m][1+c])&&(F[m][2+c])&&(!F[m][3+c]))||((F[m][c])&&(!F[m][1+c])&&(!F[m][2+c])&&(!F[m][3+c]));
//X= y'zw+xyw yzw'+xy'z'w'
E[m][4*i+1] = (F[m][3+c]);
//Y= w
E[m][4*i+2] = ((F[m][c])&&(F[m][1+c]))||((F[m][1+c])&&(F[m][3+c]))||((F[m][1+c])&&(F[m][2+c]))||((F[m][c])&&(F[m][2+c]));
//Z= xy+ yw+ yz + xz
E[m][4*i+3] = ((!F[m][c])&&(F[m][2+c])&&(F[m][3+c]))||((F[m][c])&&(!F[m][2+c])&&(F[m][3+c]))||((!F[m][c])&&(F[m][1+c]))||((F[m][1+c])&&(F[m][2+c]));
//W= x'zw+xz'w+x'y+yz
}
//printf("\n");
}
printf("\n");
printf ("STEP 2.................. ");
//printf ("TRANSFORMATION OF BITS.. ");
printf("\n");
p=0;

for(int m=0; m<P; m++) { //PRINT OF MATRIX E (straight triangles before and overturned triangles after for each plane)
//printf("Plane %d\n",m+1);
p=p+1;      
int r =(2*(p-1))+1; //number of triangles in the plan m
for(int i=0; i<r; i++){
printf("%d ", E[m][4*i]) ;
printf("%d ", E[m][4*i+1]) ;
printf("%d ", E[m][4*i+2]) ;
printf("%d  ", E[m][4*i+3]) ;
}
printf("\n");
}
printf("\n");
//\\\\\\\\\\\\\\\\\\\\\\\\\                    
//STEP 3 PYRAMID REDUCTION\  
//\\\\\\\\\\\\\\\\\\\\\\\\\
//printf("\n");
//printf ("STEP 3............................... ");
//printf ("PYRAMIDE REDUCTION................... ");
printf("\n");
p=0;
int u=0;     //local counter
int s=0;    //global counter
int tz =0; //if this varable is set to one all bits of pyramide are zeros
int t1 =0; //if this varable is set to one all bits of pyramide are 1

for(int m=0; m<P; m++) { 
p=p+1;      
int r =(2*(p-1))+1;    //number of triangles in the plane m
s=s+r;                 //global counter
for(int i=0; i<r; i++)
{
if((E[m][4*i] ==0)&&(E[m][4*i+1]==0)&&(E[m][4*i+2]==0)&&(E[m][4*i+3]==0)){//I control if in plane m there are only zeros
u=u+1;            //local counter in the planes of pyramide
tz = tz+1;       //local counter
A[m][i]=0;       //reduction of a triangle to a single bit
}
else if((E[m][4*i] ==1)&&(E[m][4*i+1]==1)&&(E[m][4*i+2]==1)&&(E[m][4*i+3]==1)){//I control if in plane m there are only ones
u=u+1;           //local counter in the planes of pyramide
t1 = t1+1;      //local counter
A[m][i]=1;      //reduction of a triangle to a single bit
     }
else{
u=0;
}
}
}
int AA[z][w];
int Nmaxx=0; 
//CASE 1
if ((u==s) && (tz!=s) && (t1!=s)){//in this case we have a reduction of pyramide because in each plane and in each triangle we have 4 equals bits
         //printf("Cycle Number %d\n",contacicli);
         //printf ("The Pyramide is reducible at cicle Number..%d\n",contacicli);
         p=0; 
         int salva =0;        
             for(int m=0; m<P; m++) {
                  //   printf("\n");
                   //  printf("Plane %d\n",m+1); 
                     p=p+1;      
                    int r =(2*(p-1))+1; //number of triangles in the plan m
                    int s = r-1;
                    int a = s-m+1;
              //Now A is a reduced matrix  but it has a single bit for each triangle in each plane (after reduction)              
               for(int i=0; i<s/2; i++){//So I order bits in A matrix and put them in matrix AA 
                     AA[m][2*i]= A[m][i];
                     AA[m][2*i+1]= A[m][a+i];
                       }
                     AA[m][s]= A[m][s/2];
                      for(int i=0; i<r; i++){                
                      U[i+salva] = AA[m][i];  //Vector construction to iterate alghorithm
               }  
               salva=salva+r;    //plane increment jump to the next lower plane (m)        
               }       
                   printf("\n");
                   printf("\n");         
                   totalBit=totalBit/4;
                   printf("Binary string in one line result from reduction at cycle Number %d\n",contacicli);
                   for(int i=0; i<=totalBit-1; i++){// I reverse vector U and I put it in R vector to continue to the next iteration
                   //printf("%d ", U[i]);
                   inputVector[i]=U[totalBit-i-1];
                   }
                    for(int i=0; i<=totalBit-1; i++){ //vector for next iteration
                    printf("%d ", inputVector[i]);
                   }                  
                printf("\n");              
              }                
//CASE 2                      
         else if (tz==s){//in this case  alghorithm convergence to 1 bit and the cicle END
              controllo =1; //END of iteration
          printf("\n");    
          //printf("The Pyramide decreases after %d cycles to.. %d\n",contacicli,0);
          printf("Result.. %d\n",0);
         // printf ("End of algorithm");
      }
       else if (t1==s){//in this case  alghorithm convergence to 1 bit and the cicle END
            controllo =1;//END of iteration
          printf("\n");
          //printf("The Pyramide decreases after %d cycles to.. %d\n",contacicli,1);
           printf("Result.. %d\n",1);
          //printf ("End of algorithm");
      } 
 //CASE 3             
         else{//in this case we haven't a reduction of pyramide
         Nmaxx=Nmax; 
         p=0;
        // printf("\n");
        // printf ("The Pyramide is not reducible at cycle Number..%d\n",contacicli);
        // printf("\n");
//we haven't a reduction of pyramide so I have reordered Matrix E in a single string U to iterate algorithm
//I start from the lower plane of pyramide from the right to the left and for each plan of E matrix (pyramide) and I fill  vector U 
int sh=0;
int ss=0;
int conta=0;
for (int m=P-1;m>=0;m--){//from the last plane (P-1) to the first (m=0)
int r = Nmaxx-conta;       //number of triangles in the plane m    
conta=conta+2;
 p=m+1;
 int k=4*r-1;
 int x=k-4*(r-p);
 int a=4*(p-1)+4;
 int n =r-p;
  for(int i=0;i<p;i++){//I fill U vector with lower half plane (from right)and first bit(from right)of upper half plane(plane m)
         int y=x-4*i;//first element of base
         int z=4*r-1;//next vertex
       U[4*i+sh]= E[m][y-3];                                                                                                                                                                                     
       U[4*i+sh+1]= E[m][y-2];                         //      
       U[4*i+sh+2]= E[m][y-1];    //after 2 cicles--> //           *    ---> upper half plane2
       U[4*i+sh+3]= E[m][z-4*i];                     //     *** * ***   ---> lower half plane2
       } 
   for(int i=0;i<n;i++){//I fill U vector with remaining  upper half plane (plane m)
         int y=k-4*i;//first element of base
         int ff=(4*(p-1)-4*i)-1;//next vertex
         int jj=4*i+(a+sh); //jump to order U vector
       U[jj]  = E[m][y-3];
       U[jj+1]= E[m][y-2];
       U[jj+2]= E[m][y-1];
       U[jj+3]= E[m][ff];
       }
       ss=4*r;           
       sh=sh+ss;         //jump to the next upper plane (m)
}         
                                  
//printf("Binary string in one line result at cycle Number %d\n",contacicli);
for(int i=0; i<totalBit; i++){ //I put U (from case3)in R vector to continue to the next iteration
      // printf("%d ", U[i]);
       inputVector[i]=U[i];
       }
   // printf("\n");
}                
}
         printf("\n");
 system("PAUSE");    
} 
//CALCULATION OF Karnaugh's MAP FOR X

/*  ORIGINAL TRASFORMATION OF BITS  --->  inversion of input (input sequence from Step1)
  abcd    ABCD                             dcba    ABCD
  0000 -> 0000 ............................0000 -> 0000
  0001 -> 1000  ...........................1000 -> 1000
  0010 -> 0001  .......................... 0100 -> 0001
  0011 -> 0010   ........................  1100 -> 0010
  0100 -> 0000  .........................  0010 -> 0000
  0101 -> 0010  .........................  1010--> 0010
  0110 -> 1011  .........................  0110--> 1010
  0111 -> 1011 ..........................  1110--> 1011
  1000 -> 0100 ..........................  0001--> 0100
  1001 -> 0101  .........................  1001--> 0101
  1010 -> 0111..........................   0101--> 0111
  1011 -> 1111 ........................    1101--> 1111
  1100 -> 1101  .......................    0011--> 1101
  1101 -> 1110  ........................   1011--> 1110
  1110 -> 0111 .........................   0111--> 0111
  1111 -> 1111 .......................     1111 -> 1111

So after STEP 2, output sequence is in the correct order for each plan of the pyramide
I named the new input xyzw and output XYZW
d: x -->X
c: y-->Y
b: w-->W
a: z-->Z
 Karnaugh's map for X (first variable output)
 xy/zw |00  |01  |10  | 11 |
   00             (1
   11                   (1
   11        (1    1)    1 )
   10  (1)         1)
Minimal form of function like sum of  minterms
X= y'zw+xyw yzw'+xy'z'w'   product is an logic and (&&), sum is a logic or (||), negation (x') is logic not(!x)
c is the shift in that plane of 4 bits at a time

In Step Number 2
in each plane m -->F[m][c] is the variable x
in each plane m -->F[m][1+c] is the variable y
in each plane m -->F[m][2+c] is the variable z
in each plane m -->F[m][3+c] is the variable w

So for X output we have:

y'zw -->  !(F[m][1+c])&&(F[m][2+c])&&(F[m][3+c]
xyw  -->  F[m][c])&&(F[m][1+c])&&(F[m][3+c]
yzw'  --> F[m][1+c])&&(F[m][2+c])&&(!F[m][3+c]
xy'z'w'-->F[m][c])&&(!F[m][1+c])&&(!F[m][2+c])&&(!F[m][3+c]

So 4 bits at a time in the first positon of matrix (E[m][4*i])--> E[m][0,4,8,12..]  we obtain x-->X tranformation:

E[m][4*i] = (!(F[m][1+c])&&(F[m][2+c])&&(F[m][3+c]))||((F[m][c])&&(F[m][1+c])&&(F[m][3+c]))||((F[m][1+c])&&(F[m][2+c])&&(!F[m][3+c]))||((F[m][c])&&(!F[m][1+c])&&(!F[m][2+c])&&(!F[m][3+c]));

Such proceedings to obtain Y, Z, W tranformation
*/

