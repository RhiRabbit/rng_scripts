#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<tss/tss error.h>
#include<tss/platform.h>
#include<tss/tss defines.h>
#include<tss/tss typedef.h>
#include<tss/tss structs.h>
#include<tss/tspi.h>
#include<trousers/trousers.h>

int main(int argc,char **argv)
{
TSS HCONTEXT hContext;
TSS HTPM hTPM;
TSS RESULT result;
TSS HKEY hSRK=0;
TSS HPOLICY hSRKPolicy=0;
TSS UUID SRK UUID=TSS UUID SRK;
BYTE wks[2]; //For the well known secret

// Set wks to the well known secret: 20 bytes of all 0.s 

memset(wks,0,20);

//Pick the TPM you are talking to.
// In this case, it is the system TPM (indicated with NULL).

result = Tspi Context Create( &hContext);
DBG(.Create Context.,result);

result = Tspi Context Connect(hContext, NULL);
DBG(.Context Connect.,result);

// Get the TPM handle
result=Tspi Context GetTpmObject(hContext,&hTPM);
    DBG(.Get TPM Handle.,result);

// Get the SRK handle
result=Tspi Context LoadKeyByUUID(hContext,TSS PS TYPE SYSTEM,SRK UUID,&hSRK);
    DBG(.Got the SRK handle., result);

//Get the SRK policy
result = Tspi GetPolicyObject(hSRK,TSS POLICY USAGE,&hSRKPolicy);
    DBG(.Got the SRK policy.,result);

//Then set the SRK policy to be the well known secret
result=Tspi Policy SetSecret(hSRKPolicy,TSS SECRET MODE SHA1,20,wks);

//Note: TSS SECRET MODE SHA1 says .Don.t hash this.
// Use the 20 bytes as they are.

    DBG(.Set the SRK secret in its policy.,result);


// MAIN BODY VARIABLES BYTE *randomBytes;
FILE *fout;
int i;
int numRandomBytesOut=atoi(argv[1])




// ENTER MAIN BODY


if((randomBytes=(BYTE *)malloc(numRandomBytesOut))==NULL)
    {
	printf(.ERROR ALLOCATING randomBytes\n.);
	return 1;
    }
// Ask the TPM for a random number and put it in the random
// Bytes Variable
result=Tspi TPM GetRandom(hTPM,numRandomBytesOut,&randomBytes);
  DBG(.Get Random number from TPM., result);

fout = fopen(.random.out.,.wb.);
    write(fileno(fout),	randomBytes,	numRandomBytesOut);
fclose(fout);

// Clean up
Tspi Context Close(hobjects you have created);
Tspi Context FreeMemory(hContext,NULL);
// This frees up memory automatically allocated for you.
Tspi Context Close(hContext);
return 0;
}
