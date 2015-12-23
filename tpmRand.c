#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <tss/tss_error.h>
#include <tss/platform.h>
#include <tss/tss_defines.h>
#include <tss/tss_typedef.h>
#include <tss/tss_structs.h>
#include <tss/tspi.h>
#include <trousers/trousers.h>

#define DBG(message, tResult) printf("Line%d, %s)%s returned 0x%08x.  %s.\n",__LINE__, __func__   ,message, tResult,(char *)Trspi_Error_String(tResult))

int main(int argc,char **argv)
{
    TSS_HCONTEXT hContext;
    TSS_HTPM hTPM;
    TSS_RESULT result;

    //setup TPM context and connect to TPM chip
    result = Tspi_Context_Create( &hContext);
    DBG("Create Context",result);

    result = Tspi_Context_Connect(hContext, NULL);
    DBG("Context Connect",result);

    result=Tspi_Context_GetTpmObject(hContext,&hTPM);
    DBG("Get TPM Handle",result);


    //read random bytes from tpm chip
    int numRandomBytesOut = 100;
    BYTE *randomBytes;
    FILE *fout;

    if((randomBytes=(BYTE *)malloc(numRandomBytesOut))==NULL)
    {
    	printf("ERROR ALLOCATING randomBytes\n");
    	return 1;
    }
    
    // Ask the TPM for a random number and put it in the random
    // Bytes Variable
    result = Tspi_TPM_GetRandom(hTPM,numRandomBytesOut,&randomBytes);
    DBG("Get Random number from TPM", result);

    fout = fopen("random.out","wb");
    write(fileno(fout),	randomBytes,	numRandomBytesOut);
    fclose(fout);

    // Clean up
    Tspi_Context_Close(hTPM);
    Tspi_Context_FreeMemory(hContext,NULL);
    // This frees up memory automatically allocated for you.
    Tspi_Context_Close(hContext);
    return 0;
}
