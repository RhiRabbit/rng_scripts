#The script reads data from /dev/random N bytes at a time
#Then it dumps the N bytes at the end of file /home/students/rxd158/numbers
#It will continue doing so until 1mb of numbers are dumped 

import random 

chunk_size = 12
total_size = 1024   
output_folder = '/media/pi/Seagate Expansion Drive/'
source_file = 'random'
current_read = 0;

print 'Starting...'

f=open('/dev/%s'%source_file)
out = open(output_folder + source_file + str(random.random()),'w+'); 

while current_read < total_size :
    current_read = current_read + chunk_size
    print 'Reading %d/%d (%f%%) bytes' % ( current_read, total_size , float(current_read)*100/float(total_size) )
    aux = f.read(chunk_size)
    out.write(aux)
    out.flush()

f.close()
out.close()

print 'Finished (%s)' % out.name
