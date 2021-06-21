# Purpose: Modify zipped log files by adding random information to the end
# ptheodor 6/19/21


import random, sys, errno, os, gzip

def add_args(fout, line):
	args_to_add = ""
 
	#latency (rand double between 10 and 100)
	args_to_add += " " + str(random.uniform(10,100)) 

	#region (random int, 0 or 1)
	args_to_add +=  " " + str(random.randint(0,1))
	
	#write to line
	args_to_add += '\n'
	fout.write(line.replace('\n', args_to_add))

def main():
	print("Running!")

	if len(sys.argv) != 2:
		print("Usage: log_mod.py <name of directory>")
		return

	old_dir = str(sys.argv[1])
	new_dir = "mod_" + old_dir

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
				with gzip.open(os.path.join(new_dir, "mod_" + filename), "wt") as fout:
					for line in fin:
						add_args(fout, line)
		else:
			with open(os.path.join(old_dir, filename), 'rt') as fin:
				with open(os.path.join(new_dir, "mod_" + filename), "wt") as fout:
					for line in fin:
						add_args(fout, line)	
	print("All done!")

if __name__ == "__main__":
	main()
