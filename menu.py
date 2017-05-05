import subprocess
import os
from termios import tcflush, TCIFLUSH
import sys

def main():
    while(True):
        tcflush(sys.stdin, TCIFLUSH)
        choice = None
        print("Enter the program to run:")
        
        #Will have a way to read a file and print all file names
        
        print("1. Lander")
        choice = str(input(">"))
        if(choice == None or choice == ""):
            print("Enter a choice!")
        elif(choice[0] == "q" or choice[0] == "Q"):
            print("Exiting...")
            return(0)
        elif(choice == "1"):
            process = subprocess.Popen("cd Lander/src; ./Lander.out", shell=True)
            process.wait()
            process = subprocess.Popen("clear", shell=True)
            process.wait()
        else:
            print("Invalid choice!")
main()
