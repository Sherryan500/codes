# include <iostream>
# include <iomanip> // allows for set precision and fixed values.
# include <string> // allows for getline function and other string functions.
using namespace std;

// stored variables:
string expression;
// variable array for invalid characters:
char Invalidchars[14] = { ':' , ';' , ',' ,'?', '!', '$', '*',
						  '_' , '=', '@', '&', '^', '#', '%'};
// variable array to store numbers to compare:
char numerics[10] = { '0','1','2','3','4','5','6','7','8','9' };

// variable to store num of uses:
int use_counter = 0;
// variable to store num of operatorss:
int opnums = 0;
bool bracketsfound = false;
bool opbrac = false;
int opbracpos, closebracpos;

// Invalid value checker function:
bool checkvalidinput(string expression)
{
	//Firstly, Check for possible undefined error. (any value attempted to divide by 0):
	for (int i = 0; i < expression.length(); i++)
	{
		//if "/" is found and the next index beside "/" is "0":
		if (expression[i] == '/' && expression[i + 1] == '0')
		{
			cout << "value error: no numerals can be divided by 0,"
				"\n the expression becomes undefined.\n";
			return true;
			break; break;
		}
		
	}
	
	//Secondly, check for invalid characters in expression such as "?!@" :
	for (int i = 0; i < expression.length(); i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (expression[i] == Invalidchars[j])
			{
				cout << "expression cannot contain invalid characters"
					" such as -> : ; , ? ! _ = @ and etc. \n";
				return true;
				break;
			}
		}
	}
	// Finally, check for spaces within expression:
	if (expression.find(" ") != string::npos)
	{
		cout << "error: no spaces allowed in expression.\n";
		return true;
	}

}
// End of input checker function.

void checkbrackets(string expression)
{
	opbracpos = expression.find('(');
	closebracpos = expression.find(')');
	if (expression.find('(') != string::npos)
	{
		cout << "open brac: " << opbracpos;
		opbrac = true;
	}
	if ((expression.find(')') != string::npos) 
		&& (opbrac == true))
	{
		cout << " close brac: " << closebracpos;
		bracketsfound = true;
	}
}

void checkops(string expression)
{
	int oparraypos[2] = {};
	checkbrackets(expression);
	
	// use pos of brackets in switch for op precedence.
	// counts for the number of operators in the expression:
	for (int i = 0; i < expression.length(); i++)
	{
		if ((expression[i] == '+' || expression[i] == '-')
			|| (expression[i] == 'x' || expression[i] == '/'))
		{
			opnums++;
			cout << "op found at: " << i << "\n";
			if (opnums == 1) {
				oparraypos[0] = i;
			}
			else if (opnums == 2)
			{
				oparraypos[1] = i;
			}
		}
	}
	switch (opnums)
	{
		case 0: // no operators
			cout << expression << "\n";
			break;
		case 1: // one operator caught

			if (bracketsfound == true)
			{	
				float com_res;
				string firstnumbrac = expression.substr(opbracpos+1, oparraypos[0]-1);
				string secondnumbrac = expression.substr(oparraypos[0]+1, expression.length() - oparraypos[0]-2);
				if(expression[oparraypos[0]] == '+')
				{
					com_res = stof(firstnumbrac) + stof(secondnumbrac);
				}
				else if (expression[oparraypos[0]] == '-')
				{
					com_res = stof(firstnumbrac) + stof(secondnumbrac);
				}
				else if (expression[oparraypos[0]] == 'x')
				{
					com_res = stof(firstnumbrac) * stof(secondnumbrac);
				}
				else
				{
					com_res = stof(firstnumbrac) / stof(secondnumbrac);
				}
				cout << "\nresult of expression: " << com_res << "\n";
			}
			else
			{

			}
		break;

		case 2: // two operators caught
			cout << " two ops\n";
			break;
		
		default:
			cout << "\nsystem error: Overloaded operator or invalid input.";
			break;
	}
	cout << "there are " << opnums << " operators\n";
	opnums = 0;
}

int main(void)
{
	do
	{
	cout << "Enter your expression: ";
	getline(cin, expression);
	if (checkvalidinput(expression) == true)
	{
		goto end;
	}
	try
	{
		// in this case, checking for index of str. so, use size_t:
		size_t pos = expression.find('.');
		string posLength = to_string(pos); //if pos is 5 this change it to "5"
		bool dotCheck = expression.find('.');
		string third_dp = expression.substr(pos + 3, 1);
		string two_dp = expression.substr(pos + 2, 1);
		string one_dp = expression.substr(pos + 1, 1);
		string one_digit = expression.substr(0, 1);
		string one_Addon = expression.substr(1, 1);

		// length will always be more than 2 because when print error,
		// even with the '.', somewhere exists a '.' which gives u a huge length.
		// Thus, use this to force the condition:
		if (posLength.length() > 2) {
			goto accept;
		}
		
		if (one_digit == "")
		{
			goto accept;
		}
		// accepts values after the first int value such as brackets and ops:
		// if condition not applied, third_dp condition will flag error.:
		else if ((one_Addon == "+" || one_Addon == "-" ||
			one_Addon == "x" || one_Addon == "/")
			|| (one_Addon == "(" || one_Addon == ")"))
		{
			goto accept;
		}
		// just to check then program ignore. So, if 2 dp found, program let it go on.:
		else if (two_dp == "")
		{
			goto accept;
		}
		// if the third decimal place is not empty and not an operator, inform error.:
		else if ((third_dp != "" ) && (third_dp != "+" && third_dp != "-"
			&& third_dp != "x" && third_dp != "/"))
		{
			cout << "value error: not more than 2.dp allowed";
			goto end;
		}

	}
	catch (exception)
	{
		//ignore exception;
	}
	
	checkvalidinput(expression);
accept:
	checkops(expression);
end:
	cout << endl;
	use_counter++;
	if (expression == "quit" or expression == "Quit")
	{
		use_counter--;
		cout << "you have used me for " << use_counter << " times";
		break;
	}
	} while (expression != "quit" or expression != "Quit");

	return 0;
}