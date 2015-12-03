#The script reads data from /dev/random N bytes at a time
#Then it dumps the N bytes at the end of file /home/students/rxd158/numbers
#It will continue doing so until 1mb of numbers are dumped 

import struct

chunk_size = 100
current_read = 0;
total_size = 1024 
output_folder = '/media/pi/Seagate Expansion Drive/'

print 'Starting...'
f=open('/dev/urandom')

while current_read < total_size :
    current_read = current_read + chunk_size
    print 'Reading %d/%d (%f%%) bytes' % ( current_read, total_size , float(current_read)*100/float(total_size) )
    aux = f.read(chunk_size)

print 'Finished'
f.close()