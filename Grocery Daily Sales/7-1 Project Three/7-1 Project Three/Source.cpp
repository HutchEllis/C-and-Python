#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main()
{
	int choice; //Declares choice as an integer
	string userSearch; //Declares userSearch as a string
	ifstream fileInput("frequency.dat");

	string item;
	int itemCount;

	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);
	cout << ("Chada Tech Corner Grocer Menu\n");
	cout << ("1: Produce a list of all items purchased in a given day along with the number of times each item was purchased.\n");//Gives user choice to display number of items purchased in a day
	cout << ("2: Produce a number representing how many times a specific item was purchased in a given day.\n");//Gives user choice to see how many times a specific item was purchased in a given day.
	cout << ("3: Produce a text based histogram of items purchased in a given day.\n");//Gives user choice to create a text based histogram representing the number of items purchased in a day as well as the number to accompany it
	cout << ("4: Exit Program.\n"); //If user selects 4 then they wish to exit the program
	cin >> choice;
	if (choice == 1) { //If user selects to display multiplication table they are then prompted to enter a number for the multiplication table
		CallProcedure("read");
	}
	else if (choice == 2) { //If user selects 3 program will tell user how many times a specific item was purchase in a day
		cout << "Enter the item name of the item you'd like to look up.\n";
		std::cin >> userSearch;
		cout << callIntFunc("itemCount", userSearch) << endl;
	}
	else if (choice == 3) {//If user selects 3 a text based histogram will be displayed as well as a number to label it
		while (fileInput >> item >> itemCount) {
			std::string stuff(itemCount, '*');
			std::cout << item << " " << stuff << std::endl;
		}
	}

	else if (choice == 4) { //If user selects choice 3 then they wish to exit the program
		exit;//Exits program
	}
	else { //If user input is anything other than 1, 2, 3, or 4 displays this error message
		cout << "Please enter a valid choice; 1, 2, 3, or 4" << endl;
	}
}

