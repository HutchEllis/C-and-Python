import re
import string                       

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def read(): #This will read our input file

    groceryList = open("ProjectThreeInputFile.txt") #opens text file
    grocery = groceryList.read().split() #creates object that holds each line info from groceryList
    
    uniqueGrocery = sorted(set(grocery))
    for item in uniqueGrocery:
        print(grocery.count(item),  item)

    groceryList.close() #closes groceryList

    

def itemCount(v): #Takes user input and searches for item
    groceryList = open("ProjectThreeInputFile.txt", "r") #Opens our input file in read mode
    grocery = groceryList.read().split() 
    uniqueGrocery = sorted(set(grocery)) #sorts groceries
    groceryList.close() #closes groceryList

    total = 0
    totalInv = 0 
    invCount = 0 

    for item in uniqueGrocery: # get total amount of items in list
        invCount += 1

    for item in uniqueGrocery: #finds item user requested
        productName = item
        totalInv += 1
        if (productName == v):
            total = grocery.count(item)
            totalInv -= 1
            print("There were",total,productName,"sold.")
        if (productName != v and totalInv == invCount):
            print("Item not found.") # if user input not found in text file returns -1


def itemFreq(): #Writes a .dat file that displays items as well as how many times they are present

    groceryList = open("ProjectThreeInputFile.txt")
    freq = open("frequency.dat", "w") #Opens file in write mode
    grocery = groceryList.read().split() 
    uniqueGrocery = sorted(set(grocery)) #sorts 

    for item in uniqueGrocery:
        freq.write(item)
        freq.write(" ")
        freq.write(str(grocery.count(item))) #convert to string to write to .dat file
        freq.write("\n")
    
    freq.close() #closes file