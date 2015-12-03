#The script reads data from /dev/random N bytes at a time
#Then it dumps the N bytes at the end of file /home/students/rxd158/numbers
#It will continue doing so until 1mb of numbers are dumped 

import struct

f=open('/dev/urandom')
a= f.read(4)

