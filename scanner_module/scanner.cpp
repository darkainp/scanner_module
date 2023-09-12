#include <iostream>
#include <fstream>

using namespace std;

struct Token
{
	string lexem;				//Lexem of the Token
	string name;			//name of the Token
};

enum TokenList
{
	stringLitToken = 0, stringDecToken = 1, stringToken = 2, charLitToken = 3, charToken = 4, charDecToken = 5, intLitToken = 6,
	intDecToken = 7, intToken = 8, realLitToken = 9, realDecToken = 10, boolLitToken = 11, boolDecToken = 12, boolToken = 13,
	hexLitToken = 14, hexDecToken = 15, hexToken = 16, endOfLineToken = 17, commentToken = 18, multiCommentToken = 19, addToken = 20,
	subToken = 21, multToken = 22, divToken = 23, modToken = 24, incToken = 25, decToken = 26, negToken = 27, equalToToken = 28,
	notEqualToToken = 29, greaterThanToken = 30, lessThanToken = 31, greaterThanEqualToken = 32, lessThanEqualToken = 33, orToken = 34,
	andToken = 35, thisToken = 36, thatToken = 37, loopToken = 38, rptToken = 39, tilToken = 40, cacToken = 41, optToken = 42,
	normToken = 43, defToken = 44, callToken = 45, rtToken = 46, ptrToken = 47, arrayToken = 48, noneToken = 49, getToken = 50,
	sendToken = 51, escToken = 52, stopToken = 53, leftBlockToken = 54, rightBlockToken = 55, leftParenthesisToken = 56,
	rightParenthesisToken = 57, leftSquareBracketToken = 58, rightSquareBracketToken = 59, assignmentToken = 60,
	semicolonToken = 61, msgToken = 62, errorToken = 63, idToken = 64, yesToken = 65, noToken = 66
};


//Global const list
const int TOKEN_LIST_SIZE = 70;
const string TOKEN[TOKEN_LIST_SIZE] = { "stringLitToken", "stringDecToken", "stringToken", "charLitToken", "charToken", "charDecToken",
"intLitToken", "intDecToken", "intToken", "realLitToken", "realDecToken", "boolLitToken", "boolDecToken", "boolToken", "hexLitToken",
"hexDecToken", "hexToken", "endOfLineToken", "commentToken", "multiCommentToken", "addToken", "subToken", "multToken", "divToken",
"modToken", "incToken", "decToken", "negToken", "equalToToken", "notEqualToToken", "greaterThanToken", "lessThanToken", "greaterThanEqualToken",
"lessThanEqualToken", "orToken", "andToken", "thisToken", "thatToken", "loopToken", "rptToken", "tilToken", "cacToken", "optToken",
"normToken", "defToken", "callToken", "rtToken", "ptrToken", "arrayToken", "noneToken", "getToken", "sendToken", "escToken", "stopToken",
"leftBlockToken", "rightBlockToken", "leftParenthesisToken", "rightParenthesisToken", "leftSquareBracketToken", "rightSquareBracketToken",
"assignmentToken", "semicolonToken", "msgToken" , "errorToken","idToken","yesToken","noToken"};

const string RESEVERD_WORD[TOKEN_LIST_SIZE] = { "", "STR", "", "", "", "CHAR",
"", "INT", "", "", "REAL", "", "YN", "", "",
"HEX", "", "", "", "", "", "", "X*", "",
"MOD", "INC", "DEC", "NT", "E2", "NE2", "GT", "LT", "GTE2",
"LTE2", "OR", "AND", "THIS", "THAT", "LOOP", "RPT", "TIL", "CAC", "OPT",
"NORM", "DEF", "CALL", "RT", "PTR", "ARR", "NONE", "GET", "SEND", "", "STOP",
"", "", "", "", "", "",
"", "", "MSG" , "","", "YES", "NO" };

//prototype list
Token scanner(ifstream&);
void ignore_comment(ifstream&);
char get_next(ifstream&);
int isReservedWord(string);
bool isGoodToEnd(char);
string get_rest(ifstream&);
bool isspace(char);

int main()
{
	ifstream source;
	string name = "source.txt";
	char next_char;

	Token token;
	//cout << "Please enter the source code file's name (including .txt): "; cin >> name;
	
	source.open(name);

	if (!source) //file not open
	{
		cout << "File didn't open correctly!!!" << endl;
		exit(EXIT_FAILURE);
	}
	else //file open
	{
		//run till meet end of file
		while (source)
		{
			next_char = get_next(source);

			//check if it is a comment
			if (next_char == '?')
			{
				source.unget();
				ignore_comment(source);
			}
			//check if it is a blank
			else if (isspace(next_char) || !source);
			else
			{
				source.unget();
				token = scanner(source);
				cout << token.lexem << "\t\t" << token.name << endl;
			}
		}
		source.close();
	}

	return 0;
}

/*
* Scan for lexeme
*
* @param source: file pointer of the source code file
* @return
*/
Token scanner(ifstream& source)
{
	Token token;
	char next_char;
	char this_char;
	string lexeme = "";
	bool endyet = false;
	int x;

	this_char = get_next(source);
	switch (this_char)
	{
		//single-character Tokens
	case '<':
		token.lexem = "<";
		token.name = TOKEN[leftBlockToken];
		break;
	case '>':
		token.lexem = ">";
		token.name = TOKEN[rightBlockToken];
		break;
	case '.':
		token.lexem = ".";
		token.name = TOKEN[endOfLineToken];
		break;
	case '[':
		token.lexem = "[";
		token.name = TOKEN[leftSquareBracketToken];
		break;
	case ']':
		token.lexem = "]";
		token.name = TOKEN[rightSquareBracketToken];
		break;
	case '(':
		token.lexem = "(";
		token.name = TOKEN[leftParenthesisToken];
		break;
	case ')':
		token.lexem = ")";
		token.name = TOKEN[rightParenthesisToken];
		break;
	case '+':
		token.lexem = "+";
		token.name = TOKEN[addToken];
		break;
	case '-':
		token.lexem = "-";
		token.name = TOKEN[subToken];
		break;
	case '/':
		token.lexem = "/";
		token.name = TOKEN[divToken];
		break;
	case '=':
		token.lexem = "=";
		token.name = TOKEN[assignmentToken];
		break;
	case ';':
		token.lexem = ";";
		token.name = TOKEN[semicolonToken];
		break;

		//Number literal regconition
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		next_char = this_char;
		do //get 1st number part
		{
			lexeme += this_char;
			this_char = get_next(source);
		} while (isdigit(this_char));
		token.name = TOKEN[intLitToken];
		token.lexem = lexeme;

		if (this_char == ',') //there is a comma after the 1st number part ex: 123,
		{
			lexeme += this_char;
			token.name = TOKEN[realLitToken];
			token.lexem = lexeme;

			next_char = get_next(source);
			if (isdigit(next_char)) //if next char after comma is digit
			{
				this_char = next_char;
				do //get the 2nd number part after comma ex: 123,123
				{
					lexeme += this_char;
					this_char = get_next(source);
				} while (isdigit(this_char));
				token.name = TOKEN[realLitToken];
				token.lexem = lexeme;

				if (this_char == 'E') //if after 2nd number part is 'e'
				{
					lexeme += this_char;
					next_char = get_next(source);
					if (isdigit(next_char)) //if next char after 'e' is digit
					{
						this_char = next_char;
						do //get 3rd number part ex: 123,123e123 
						{
							lexeme += this_char;
							this_char = get_next(source);
						} while (isdigit(this_char));
						token.name = TOKEN[realLitToken];
						token.lexem = lexeme;
					}
					else if (next_char == '-') //if next char after 'e' is '-'
					{
						lexeme += next_char;
						this_char = next_char;
						next_char = get_next(source);
						if (isdigit(next_char))	//if next char after '-' is digit
						{
							this_char = next_char;
							do //get the 3rd number part ex: 123,123e-123
							{
								lexeme += this_char;
								this_char = get_next(source);
							} while (isdigit(this_char));
							token.lexem = lexeme;
							token.name = TOKEN[realLitToken];
						}
						else //if next char after '-' is not digit
							token.name = TOKEN[errorToken];
					}
					else //if next char after 'e' is not digit or '-'
					{
						token.name = TOKEN[errorToken];
						lexeme += get_rest(source);
						token.lexem = lexeme;
					}
				}
			}
			else if (next_char == 'E')
			{
				this_char = next_char;
				lexeme += this_char;
				next_char = get_next(source);
				if (isdigit(next_char))
				{
					this_char = next_char;
					do
					{
						lexeme += this_char;
						this_char = get_next(source);
					} while (isdigit(this_char));
					
					if (!isGoodToEnd(this_char))
					{
						lexeme += get_rest(source);
						token.name = TOKEN[errorToken];
						token.lexem = lexeme;
					}
					else
					{
						token.name = TOKEN[realLitToken];
						token.lexem = lexeme;
					}
				}
				else if (next_char == '-')
				{
					this_char = next_char;
					lexeme += this_char;
					next_char = get_next(source);
					if (isdigit(next_char))
					{
						this_char = next_char;
						do
						{
							lexeme += this_char;
							this_char = get_next(source);
						} while (isdigit(this_char));
						if (!isGoodToEnd(this_char))
						{
							lexeme += get_rest(source);
							token.name = TOKEN[errorToken];
							token.lexem = lexeme;
						}
						else
						{
							token.name = TOKEN[realLitToken];
							token.lexem = lexeme;
						}
					}
					else
					{
						source.unget();
						source.unget();
						token.name = TOKEN[errorToken];
						token.lexem = "0,E";
					}
				}
				else if (isGoodToEnd(next_char))
				{
					token.name = TOKEN[errorToken];
					token.lexem = lexeme;
				}
				else
				{
					lexeme += get_rest(source);
					token.name = TOKEN[errorToken];
					token.lexem = lexeme;
				}
			}
			else if (!isGoodToEnd(next_char))
			{
				lexeme += get_rest(source);
				token.name = TOKEN[errorToken];
				token.lexem = lexeme;
			}
			else
			{
				token.name = TOKEN[realLitToken];
				token.lexem = lexeme;
			}
		}
		else if (this_char == 'X')
		{
			if (lexeme.length() == 1 && lexeme == "0")
			{
				lexeme += this_char; //lexeme now is 0x
				next_char = get_next(source);
				while (isdigit(next_char) || next_char >= 'A' && next_char <= 'F')
				{
					lexeme += next_char;
					next_char = get_next(source);
				}
				if (isGoodToEnd(next_char))
				{
					if (lexeme.length() >= 3)
					{
						token.name = TOKEN[hexLitToken];
						token.lexem = lexeme.substr(2, lexeme.length() - 2);
					}
					else
					{
						token.name = TOKEN[errorToken];
						token.lexem = lexeme;
					}
				}
				else
				{
					lexeme += get_rest(source);
					token.name = TOKEN[errorToken];
					token.lexem = lexeme;
				}
			}
			else //get the rest of the word and return error	
			{
				lexeme += get_rest(source);
				token.lexem = lexeme;
				token.name = TOKEN[errorToken];
			}
		}
		else if (!isGoodToEnd(this_char))
		{
			do
			{
				lexeme += this_char;
				this_char = get_next(source);
			} while (!isGoodToEnd(this_char));
			token.name = TOKEN[errorToken];
			token.lexem = lexeme;
		}
		else
		{
			source.unget();
		}
		break;

		//string lit or char lit token
		case ':': //1st char is ':'
		lexeme += this_char;
			next_char = get_next(source); //getting 2nd char
			if (next_char != ':') //if 2nd char is not ':' possible charLitToken
			{
				lexeme += next_char;
				token.name = TOKEN[charLitToken]; 
				
				if (next_char == '@')	//if 2nd char is '@' possible charLitToken of the use of an escape character
				{	
					this_char = next_char;

					next_char = get_next(source);		
					if (next_char == ':') //if 3rd char is ':' => charLitToken of :@: maybe invalid
					{
						lexeme += next_char;
						this_char = next_char;
						next_char = get_next(source);
						if (next_char == ':') //if 4th char is ':' => valid escape char used
						{
							token.lexem = ':';
							token.name = TOKEN[charLitToken];
						}
						else //invalid
						{
							token.name = TOKEN[errorToken];
							token.lexem = lexeme;
						}	
					}
					else //if 3rd char is not ':' => possible charLitToken with the use of an escape character Ex: :@@:
					{
						lexeme += next_char;
						this_char = next_char;
						if (this_char == '@') // the 2nd use of escape character atm
						{
							next_char = get_next(source);
							if (next_char == ':') //if 4th char is ':' => valid charLitToken :@@:
							{
								token.lexem = this_char; //equal the 3rd char scanned
							}
							else //if 4th char is not ':' => invalid charLitToken
							{
								this_char = next_char;
								//taking everything till seeing a ':'
								do
								{
									lexeme += this_char;
									this_char = get_next(source);
								} while (this_char != ':');
								lexeme += this_char;
								token.name = TOKEN[errorToken];
								token.lexem = lexeme;
							}
						}
						else //invalid use of escape character;
						{
							//taking everything till seeing a ':'
							do
							{
								this_char = get_next(source); 
								lexeme += this_char;
								
							} while (this_char != ':');
							lexeme += this_char;
							token.name = TOKEN[errorToken];
							token.lexem = lexeme;
						}
					}//end else
				}
				else //if 2nd char is not '@' => possible charLitToken
				{
					this_char = next_char;

					next_char = get_next(source);
					if (next_char == ':') //if 3rd char is ':' => valid charLit Ex: :x:
					{
						token.lexem = this_char; //return the 2nd char
					}
					else //if 3rd char is not ':' => invalid charLit
					{
						this_char = next_char;
						//taking everything till seeing a ':'
						do
						{
							lexeme += this_char;
							this_char = get_next(source);
						} while (this_char != ':' || !source);
						lexeme += this_char;
						token.lexem = lexeme;
						token.name = TOKEN[errorToken];
					}
				}
			}
			else //2nd char is another ':' => possible string lit
			{
				token.name = TOKEN[stringLitToken];
				this_char = next_char;

				//take things till see '::' => means endyet = true or meet end of file
				do {
					//keep getting things till see ':' or '@' or end of fike
					do
					{
						lexeme += this_char;
						this_char = get_next(source);
					} while (this_char != ':' && this_char != '@' && source);
					
					switch (this_char)
					{
					case ':': //3rd ':'
						lexeme += this_char;

						next_char = get_next(source);
						if (next_char == ':') //4th ':'
						{
							endyet = true;
							token.lexem.assign(lexeme, 2, lexeme.length() - 3); //wtf is valid string
						}
						else
						{
							token.name = TOKEN[errorToken]; //invalid use of ':' without an escape character
							endyet = true;

							token.lexem = lexeme;
						}
						break;
					case '@': //possible use of escape character
						next_char = get_next(source);

						switch (next_char)
						{
						case '@':
							this_char = next_char;
							break;
						case ':':
							this_char = next_char;
							break;
						default:
							lexeme += '@';
							lexeme += next_char;
							token.name = TOKEN[errorToken]; //invalid use of an escape character
							token.lexem = lexeme;
							endyet = true;
							break;
						}
						break;
					default:
						if (!source) //source end without 2nd "::"
							token.name = TOKEN[errorToken];
						break;
					}
				} while (!endyet && source);
			}

			break;

		//idToken recognition
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			do
			{
				lexeme += this_char;
				this_char = get_next(source);
			} while (!isGoodToEnd(this_char));
			source.unget();
			x = isReservedWord(lexeme);
			if (x == -1)
			{
				token.name = TOKEN[idToken];
				token.lexem = lexeme;
			}
			else
			{
				token.name = TOKEN[x];
				token.lexem = lexeme;
			}
			break;
		default:
			do
			{
				lexeme += this_char;
				this_char = get_next(source);
			} while (!isGoodToEnd(this_char));
			token.name = TOKEN[errorToken];
			token.lexem = lexeme;
	}

	return token;
}

/*
* Move the file pointer pass the comment
* 
* @param source: the file pointer
* @return a character if it is not a comment or the character at the end of the comment.
*/
void ignore_comment(ifstream& source)
{
	char ch;				//most recent char
	char lookahead;			//the one right next to ch, to determine valid end multi-line comment
	bool endyet = false;	//is the comment end yet

	source >> noskipws >> ch;
	if (ch == '?')	//is this a start of a comment
	{
		source >> noskipws >> ch;

		if (ch == '?') //multiline comment
		{
			source >> noskipws >> ch;
			while (!endyet)
			{
				while (ch != '?')
				{
					source >> noskipws >> ch;
				}
				source >> noskipws >> lookahead;
				if (lookahead == '?') 
				{
					source >> noskipws >> ch;
					endyet = true;
				}
				if (!endyet)
					source >> noskipws >> ch;
			}
			source.unget();
			//cout << "end multiline comment!" << endl;
			//cout << "This is the return char--" << ch << "--" << endl;
		}
		else //this is a single-line comment
		{
			do
			{
				source >> noskipws >> ch;
			} while (ch != '\n');
			//cout << "end single-line comment!" << endl;
		}
	}
}

/*File pointer get updated after the function
* 
* @param source: file pointer
* @return The next character in the file 
*/
char get_next(ifstream& source)
{
	char ch;
	source >> noskipws >> ch;
	ch = (char)toupper(ch);
	return ch;
}

/*
* @param id: string identifier
* @return -1 if identifier is not a reserved word
* @return a number from 0 to TOKEN_LIST_SIZE if it is a reserved word
*/
int isReservedWord(string id)
{
	int x = -1;
	for (int i = 0; i <= TOKEN_LIST_SIZE; i++)
	{
		if (RESEVERD_WORD[i] == id)
		{
			x = i;
			break;
		}
	}

	return x;
}

/*
* @return true if the passed character is a single-character token
* or a start of a comment
* or a space
* @return false otherwise
*/
bool isGoodToEnd(char this_char)
{
	bool yes = false;
	if (isspace(this_char) || this_char == '.' || this_char == '?'
		|| this_char == '<' || this_char == '>' || this_char == '[' || this_char == ']'
		|| this_char == '{' || this_char == '}' || this_char == '(' || this_char == ')'
		|| this_char == '+' || this_char == '-' || this_char == '/'
		|| this_char == '=' || this_char == ';')
		yes = true;
	return yes;
}


string get_rest(ifstream& source)
{
	string str;
	char ch;
	source.unget();
	ch = get_next(source);
	do 
	{
		str += ch;
		ch = get_next(source);
	} while (!isGoodToEnd(ch));
	source.unget();

	return str;
}

bool isspace(char h)
{
	bool result = false;
	switch (h)
	{
	case '\n':
	case '\t':
	case ' ':
	case '\v':
	case '\r':
	case '\f':
		result = true;
		break;
	default:
		break;
	}
	return result;
}
