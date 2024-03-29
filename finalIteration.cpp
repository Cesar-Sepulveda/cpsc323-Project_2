/*------------------------------------------------------------------------------
Cesar Sepulveda
CPSC 323 Section 4
Project #2
11/18/2019
------------------------------------------------------------------------------*/
//Including libraries for the program
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

//------------------------------------------------------------------------------
//Class that holds the different keywords.
class Keywords{
  private:
    string key1 = "int";
    string key2 = "float";
    string key3 = "bool";
    string key4 = "if";
    string key5 = "else";
    string key6 = "then";
    string key7 = "endif";
    string key8 = "while";
    string key9 = "whileend";
    string key10 = "do";
    string key11 = "doend";
    string key12 = "for";
    string key13 = "forend";
    string key14 = "input";
    string key15 = "output";
    string key16 = "and";
    string key17 = "or";
    string key18 = "function";
    vector<string> key;
  public:
    void addKeyword(){
      key.push_back(key1);
      key.push_back(key2);
      key.push_back(key3);
      key.push_back(key4);
      key.push_back(key5);
      key.push_back(key6);
      key.push_back(key7);
      key.push_back(key8);
      key.push_back(key9);
      key.push_back(key10);
      key.push_back(key11);
      key.push_back(key12);
      key.push_back(key13);
      key.push_back(key14);
      key.push_back(key15);
      key.push_back(key16);
      key.push_back(key17);
      key.push_back(key18);
  }
  void getKeys(vector<string>& temp){
    for(int i = 0; i < key.size(); i++){
      temp.push_back(key.at(i));
    }
  }
};

//------------------------------------------------------------------------------
//Class that holds the different separators.
class Separators{
  private:
    string sep1 = "'";
    string sep2 = "(";
    string sep3 = ")";
    string sep4 = "{";
    string sep5 = "}";
    string sep6 = "[";
    string sep7 = "]";
    string sep8 = ",";
    string sep9 = ".";
    string sep10 = ":";
    string sep11 = ";";
    string sep12 = "!";
    string sep13 = " ";
    vector<string> separator;
  public:
    void addSeparator(){
      separator.push_back(sep1);
      separator.push_back(sep2);
      separator.push_back(sep3);
      separator.push_back(sep4);
      separator.push_back(sep5);
      separator.push_back(sep6);
      separator.push_back(sep7);
      separator.push_back(sep8);
      separator.push_back(sep9);
      separator.push_back(sep10);
      separator.push_back(sep11);
      separator.push_back(sep12);
      separator.push_back(sep13);
    }
    void getSeparators(vector<string>& temp){
      for(int i =0; i < separator.size(); i++){
        temp.push_back(separator.at(i));
      }
    }
};

//------------------------------------------------------------------------------
//Class that holds the different operators.
class Operators{
  private:
    string op1 = "*";
    string op2 = "+";
    string op3 = "-";
    string op4 = "=";
    string op5 = "/";
    string op6 = ">";
    string op7 = "<";
    string op8 = "%";
    vector<string> ope;
  public:
    void addOperator(){
      ope.push_back(op1);
      ope.push_back(op2);
      ope.push_back(op3);
      ope.push_back(op4);
      ope.push_back(op5);
      ope.push_back(op6);
      ope.push_back(op7);
      ope.push_back(op8);
    }
    void getOperators(vector<string>& temp){
      for(int i = 0; i < ope.size(); i++){
        temp.push_back(ope.at(i));
      }
    }
};

//------------------------------------------------------------------------------
//Function that reads in the input file and stores it in a vector.
vector<string> readFile(vector<string> input, string filename){
  fstream myFile;
  string in;
  string blank;
  myFile.open(filename);
  while(myFile >> in){
      input.push_back(in);
  }
  myFile.close();
  return input;
}

//------------------------------------------------------------------------------
//Function that separates operators/separators from keywords and idetifiers.
//Stores inside a new vector.
vector<string> lexer(vector<string> input){
  vector<string> newInput;
  vector<string> separator;
  vector<string> operators;
  Separators sep;
  Operators op;
  sep.addSeparator();
  sep.getSeparators(separator);
  op.addOperator();
  op.getOperators(operators);
  int size = 0;
  int find;
  int count = 0;
  string str1, str2, str3;
  for(int i = 0; i < input.size(); ++i){
    for(int s = 0; s < separator.size(); s++){
      if(input.at(i).find(separator.at(s)) != -1 && input.at(i).size() > 1){
        count++;
        find = input.at(i).find(separator.at(s));
        str1 = input.at(i).substr(0, find);
        newInput.push_back(str1);
        str2 = input.at(i).substr(find);
        if(str2.size() > 1 && input.at(i).find(separator.at(s)) < input.at(i).size()-1){
          str3 = str2.substr(1);
          str2 = str2.substr(0,1);
          newInput.push_back(str2);
          newInput.push_back(str3);
        }else{
          newInput.push_back(str2);
        }
      }
    }
    if(count == 0){
      newInput.push_back(input.at(i));
      //newInput.push_back("!!!!!!!!!!!!!!!!!");
    }
    count = 0;
  }
  return newInput;
}

//------------------------------------------------------------------------------
//Function that checks for an assignment statement
bool assignment(int num, vector<int> lex, vector<string> input){
  bool match = false;
  if(num+3 < lex.size()){
    if(lex.at(num) == -12){
      if(input.at(num+1).compare("=") == 0){
        if(lex.at(num+2) == -12){
          if(input.at(num+3).compare(";") == 0){
            match = true;
          }
        }
      }
    }
  }
  return match;
}

//------------------------------------------------------------------------------
//Function that check for an addition statement
bool addition(int num, vector<int> lex, vector<string> input){
  bool match = false;
  if(num+5 < lex.size()){
    if(lex.at(num) == -12){
      if(input.at(num+1).compare("=") == 0){
        if(lex.at(num+2) == -12){
          if(input.at(num+3).compare("+") == 0){
            if(lex.at(num+4) == -12){
              if(input.at(num+5).compare(";") == 0){
                match = true;
              }
            }
          }
        }
      }
    }
  }
  return match;
}

//------------------------------------------------------------------------------
//Function that check for a subtraction statement
bool subtraction(int num, vector<int> lex, vector<string> input){
  bool match = false;
  if(num+5 < lex.size()){
    if(lex.at(num) == -12){
      if(input.at(num+1).compare("=") == 0){
        if(lex.at(num+2) == -12){
          if(input.at(num+3).compare("-") == 0){
            if(lex.at(num+4) == -12){
              if(input.at(num+5).compare(";") == 0){
                match = true;
              }
            }
          }
        }
      }
    }
  }
  return match;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Function that check for a multiplication statement
bool multiplication(int num, vector<int> lex, vector<string> input){
  bool match = false;
  if(num+5 < lex.size()){
    if(lex.at(num) == -12){
      if(input.at(num+1).compare("=") == 0){
        if(lex.at(num+2) == -12){
          if(input.at(num+3).compare("*") == 0){
            if(lex.at(num+4) == -12){
              if(input.at(num+5).compare(";") == 0){
                match = true;
              }
            }
          }
        }
      }
    }
  }
  return match;
}

//------------------------------------------------------------------------------
//Function that check for a division statement
bool division(int num, vector<int> lex, vector<string> input){
  bool match = false;
  if(num+5 < lex.size()){
    if(lex.at(num) == -12){
      if(input.at(num+1).compare("=") == 0){
        if(lex.at(num+2) == -12){
          if(input.at(num+3).compare("/") == 0){
            if(lex.at(num+4) == -12){
              if(input.at(num+5).compare(";") == 0){
                match = true;
              }
            }
          }
        }
      }
    }
  }
  return match;
}

//------------------------------------------------------------------------------
//Print Function
void print(int lines, string op, vector<string> input, int i,fstream& myFile){
  myFile << "Line #" << lines << ":" << endl;
  myFile << "Token: Identifier" << setw(10) << "Lexeme: " << input.at(i) << endl;
  myFile << "<Statement> -> <Assign>" << endl;
  myFile << "<Assign> -> <Identifier> = <Expression> ;" << endl;
  myFile << "Token: Operator" << setw(13) << "Lexeme: =" << endl;
  myFile << "Token: Identifier" << setw(10) << "Lexeme: " << input.at(i+2) << endl;
  myFile << "<Expression> -> <Term> <Expression Prime>" << endl;
  myFile << "<Term> -> <Factor> <Term Prime>" << endl;
  myFile << "<Factor> -> <Identifier>" << endl;
  myFile << "Token: Operator" << setw(13) << "Lexeme: " << op << endl;
  myFile << "<Term Prime> -> ε" << endl;
  myFile << "<Expression Prime> -> + <Term> <Expression Prime>" << endl;
  myFile << "Token: Identifier" << setw(10) << "Lexeme: " << input.at(i+4) << endl;
  myFile << "<Term> -> <Factor> <Term Prime>" << endl;
  myFile << "<Factor> -> <Identifier>" << endl;
  myFile << "Token: separator" << setw(12) << "Lexeme: ;" << endl;
  myFile << "<Term Prime> -> ε" << endl;
  myFile << "<Expression Prime> -> ε" << endl;
  myFile << endl;
}

//------------------------------------------------------------------------------
//Function that checks the inputs syntax
void identify(vector<int> lex, vector<string> input, fstream& myFile){
  int match = 0;
  int lines = 1;
  for(int i = 0; i < lex.size(); ++i){
    match = -1;
    if(lex.at(i) == -14 && input.at(i).compare("!") == 0){
      match = 0;
    }else if(assignment(i,lex,input)){
      myFile << "Line #" << lines << ":" <<endl;
      myFile << "Token: Identifier" << setw(10) << "Lexeme: " << input.at(i) << endl;
      myFile << "Token: Operator" << setw(13) << "Lexeme: =" << endl;
      myFile << "Token: Identifier" << setw(10) << "Lexeme: " << input.at(i+2) << endl;
      myFile << "Token: Separator" << setw(12) << "Lexeme: ;" << endl;
      i = i+3;
      match = 1;
      ++lines;
    }else if(addition(i,lex,input)){
      print(lines, "+", input,i,myFile);
      i = i+5;
      match = 1;
      ++lines;
    }else if(subtraction(i,lex,input)){
      print(lines, "-", input,i,myFile);
      i = i+5;
      match = 1;
      ++lines;
    }else if(multiplication(i,lex,input)){
      print(lines, "*", input,i,myFile);
      i = i+5;
      match = 1;
      ++lines;
    }else if(division(i,lex,input)){
      print(lines, "/", input,i,myFile);
      i = i+5;
      match = 1;
      ++lines;
    }
    if(match == -1){
      myFile << "Line #" << lines << ":" << endl;
      myFile << "syntax error" << endl;
      lines++;
      break;
    }
  }
}

//------------------------------------------------------------------------------
//Main function that hands input, comparisons, and writing to the output file.
int main(){
  string filename1, filename2;
  Keywords key;
  Operators op;
  Separators sep;
  key.addKeyword();
  op.addOperator();
  sep.addSeparator();
  vector<string> input;
  vector<string> keyterms;
  vector<string> operators;
  vector<string> separators;
  int find = 0;
  int found = 0;
  int comment = 0;
  vector<int> vec;
  cout << "Enter the input filename: ";
  cin >> filename1;
  cout << endl;
  input = readFile(input, filename1);
  sep.getSeparators(separators);
  op.getOperators(operators);
  key.getKeys(keyterms);
  vector<string> newInput = lexer(input);
  for(int i = 0; i < newInput.size(); ++i){
    cout << newInput.at(i) << endl;
  }
  cout << "Enter the output filename: ";
  cin >> filename2;
  cout << endl;
  fstream myFile;
  myFile.open(filename2);
  for(int i = 0; i < newInput.size(); ++i){
    if(comment == 1){
      while(i < newInput.size() && newInput.at(i) != "!"){
        ++i;
        vec.push_back(-14);             //comments = -14
      }
      vec.push_back(-10);               //separators = -10
      comment = 0;
    }else if(isalpha(newInput.at(i)[0])){
      for(int j = 0; j < keyterms.size();++j){
        if(keyterms.at(j).compare(newInput.at(i)) == 0){
          vec.push_back(-11);           //keyterms = -11
          found = 1;
        }
      }
      if(found == 0){
        vec.push_back(-12);             //identifiers = -12
      }
      found = 0;
    }else if(ispunct(newInput.at(i)[0])){
      for(int k = 0; k < operators.size();++k){
        if(operators.at(k).compare(newInput.at(i)) == 0){
          vec.push_back(-13);           //operators = -13
        }
      }
      for(int l = 0; l < separators.size(); ++l){
        if(separators.at(l).compare(newInput.at(i)) == 0){
          vec.push_back(-10);
          if(newInput.at(i) == "!"){
            comment = 1;
          }
        }
      }
    }
  }
  identify(vec, newInput, myFile);
  myFile.close();
  return 0;
}
