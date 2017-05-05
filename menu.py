import subprocess
import os
from termios import tcflush, TCIFLUSH
import sys

def main():
    readfile = open("games.txt", "r")
    options = []
    for line in readfile:
        options.append(line.split(":"))

    for option in options:
        option[1] = option[1].rstrip("\n")
    
    while(True):
        tcflush(sys.stdin, TCIFLUSH)
        choice = None
        print("Enter the program to run:")
        
        num = 1
        for option in options:
            print(str(num) + ": " + option[0])
            num += 1

        choice = str(input(">"))
        if(choice == None or choice == ""):
            print("Enter a choice!")
            
        elif(choice[0] == "q" or choice[0] == "Q"):
            print("Exiting...")
            readfile.close()
            return(0)
        
        elif(not choice.isnumeric()):
            print("Invalid choice!")
            
        elif(int(choice) >= 1 and int(choice) < num):
            process = subprocess.Popen(option[int(choice) - 1], shell=True)
            process.wait()
            process = subprocess.Popen("clear", shell=True)
            process.wait()
            
        else:
            print("Invalid choice!")
            
main()
