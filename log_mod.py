# Purpose: Modify zipped log files by adding random information to the end
# ptheodor 6/19/21


import random, sys, errno, os, gzip
import geoip2.database
import geoip2.errors
import maxminddb
#import geoip2.webservice.Client
#import geoip2.webservice.AsyncClient



def add_args(fout, line, mode):
	args_to_add = ""
	if (mode == 1): 
		#latency (rand double between 10 and 100)
		args_to_add += " " + str(random.uniform(10,100)) 

		#region (random int, 0 or 1)
		args_to_add +=  " " + str(random.randint(0,1))
	elif (mode == 2):
		with geoip2.database.Reader('GeoLite2-City_20210720/GeoLite2-City.mmdb') as reader:
			try:
				ip_addr = line.split()[1]
				response = reader.city(ip_addr)	
				args_to_add += " " + str(response.location.latitude) + " " + str(response.location.longitude)
				#print(ip_addr + args_to_add)
			#except FileNotFoundError:
			#	print("File not found.")
			#	exit()
			#except maxminddb.InvalidDatabaseError:
			#	print("Invalid Database Error")
			#	exit()
			except ValueError:
				print(line.split()[1] + "is not a valid IP address")
				args_to_add += " 0 + 0"
			except:
				print("IP address yielded an unexpected error") 
				args_to_add += " 0 + 0"
				
		#write to line
		args_to_add += '\n'
		fout.write(line.replace('\n', args_to_add))

def main():
	print("Running!")

	if len(sys.argv) != 3:
		print("Usage: log_mod.py <name of directory> <mode>")
		return

	mode = int(sys.argv[2])

	old_dir = str(sys.argv[1])
	if (mode == 1):
		name_mod = "mod_"
	elif (mode == 2):
		name_mod = "loc_"
	else:
		print("Error: Invalid Mode")
		return -1
	new_dir = name_mod + old_dir


	if not os.path.isdir(old_dir):
		print(old_dir + " is not a valid directory!")
	
	try:	
		os.mkdir(new_dir)
	except OSError as exc:
		if exc.errno != errno.EEXIST:
			raise
		pass
		
	print("New directory (" + new_dir + ") created successfully")
		
	for filename in os.listdir(old_dir):
		print("Modifying " + filename)
		#note: to use this for nonzipped log files
		if filename.endswith('.gz'):
   			with gzip.open(os.path.join(old_dir, filename), 'rt') as fin:
				with gzip.open(os.path.join(new_dir, name_mod + filename), "wt") as fout:
					for line in fin:
						add_args(fout, line, mode)
		else:
			with open(os.path.join(old_dir, filename), 'rt') as fin:
				with open(os.path.join(new_dir, name_mod + filename), "wt") as fout:
					for line in fin:
						add_args(fout, line, mode)	
	print("Output stored in " + new_dir)

if __name__ == "__main__":
	main()
