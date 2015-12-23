Openssl libs for linux :
```bash
   sudo apt-get install libssl-dev
   gcc opensshRandBytes.c -o openSSLRand -lcrypto
```

Install trousers packages and compile tpm code : 
```bash
   sudo apt-get install tpm-tools
   sudo apt-get install  libtspi-dev
   gcc tpmRand.c -o tpmRand -ltspi -Wall -Wimplicit-function-declaration
```
