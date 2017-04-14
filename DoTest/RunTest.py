#! /usr/bin/env python
import subprocess

## Set initial parameters
games=100

## Run single test
def run_test(i):
	##process = subprocess.Popen(['test'])
	##returncode = process.wait()
   	##print('returned {0}'.format(returncode))
    out_bytes = str(i) + '\t'
    out_bytes += subprocess.check_output(['./test'])
    return out_bytes

if __name__  == "__main__":
    result = ""
    for i in range(games):
    	print ("run test:" + str(i+1) + "/" + str(games))
        result += run_test(i)
    f = open("result.txt", "w")
    print >> f, result
    f.close()