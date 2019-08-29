#include <stdio.h> 
#include <bits/stdc++.h> 
#include <stdlib.h>

using namespace std;

 int main (){
 
 const int bins=400;
 
//RUN EXECUTABLE FILE COMMAND
 char command[80];
 char command1[80];
 char command2[80];
 char command3[80];
 char command4[80];
 
 //MOVE COMMANDS TO FILL FOLDERS
 char mv[80];
 char mv1[80];
 char mv2[80];
 char mv3[80];
 char mv4[80];
 //delete commands TO FREE FOLDERS
 char rv[80];
 char rv1[80];
 char rv2[80];
 char rv3[80];
 char rv4[80];

//DELETE POSSIBLE EXISTING FILES TO AVOID DATA MIXUP

remove("ParticleFieldBF_HSG_LEMIII_LQparameters_LEMIII.csv");
remove("ParticleFieldBG_HSG_LEMIII_LQparameters_LEMIII.csv");
remove("ParticleFieldEM_HSG_LEMIII_LQparameters_LEMIII.csv");
remove("ParticleFieldQF_HSG_LEMIII_LQparameters_LEMIII.csv");
remove("ParticleFieldQG_HSG_LEMIII_LQparameters_LEMIII.csv");
 
 
for (int i=0;i<bins; i++) //RUN FOR EACH FILE
       {
sprintf (command, "./mixedField_example_EM.sh %d",i);
system (command);
sprintf (rv, "rm -f EM/ParticleFieldEM%d.mixedField",i);
system(rv);
sprintf (mv, "mv ParticleFieldEM%d.mixedField EM",i);
system(mv);
       }
       
 for (int i=0;i<bins; i++) //RUN FOR EACH FILE
       {
sprintf (command1, "./mixedField_example_BF.sh %d",i);
system (command1);
sprintf (rv1, "rm -f BF/ParticleFieldBF%d.mixedField",i);
system(rv1);
sprintf (mv1, "mv ParticleFieldBF%d.mixedField BF",i);
system(mv1);
       }
       
 for (int i=0;i<bins; i++) //RUN FOR EACH FILE
       {
sprintf (command2, "./mixedField_example_BG.sh %d",i);
system (command2);
sprintf (rv2, "rm -f BG/ParticleFieldBG%d.mixedField",i);
system(rv2);
sprintf (mv2, "mv ParticleFieldBG%d.mixedField BG",i);
system(mv2);
       }
       
 for (int i=0;i<bins; i++) //RUN FOR EACH FILE
       {
sprintf (command3, "./mixedField_example_QF.sh %d",i);
system (command3);
sprintf (rv3, "rm -f QF/ParticleFieldQF%d.mixedField",i);
system(rv3);
sprintf (mv3, "mv ParticleFieldQF%d.mixedField QF",i);
system(mv3);
       }
       
  for (int i=0;i<bins; i++) //RUN FOR EACH FILE
       {
sprintf (command4, "./mixedField_example_QG.sh %d",i);
system (command4);
sprintf (rv4, "rm -f QG/ParticleFieldQG%d.mixedField",i);
system(rv4);
sprintf (mv4, "mv ParticleFieldQG%d.mixedField QG",i);
system(mv4);
       }
       
       
 //system("root");
 
 //system(".X rd.C");
 
return 0;

             }
