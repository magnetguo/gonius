#! /usr/bin/env python
import subprocess

## Set initial parameters
games=100
MaxDepth = 11

## Run single test
def run_test(i, d):
	##process = subprocess.Popen(['test'])
	##returncode = process.wait()
   	##print('returned {0}'.format(returncode))
    out_bytes = str(i) + '\t'
    out_bytes += subprocess.check_output(['./test', str(d)])
    return out_bytes

if __name__  == "__main__":
    for d in range(MaxDepth):
        result = ""
        f = open("result"+"_depth "+str(d+1)+".txt", "w")
        for i in range(games):
    	    print ("depth:"+str(d+1)+"run test:" + str(i+1) + "/" + str(games))
            result += run_test(i, d+1)
            result += "\n"
        print >> f, result
        f.close()
    