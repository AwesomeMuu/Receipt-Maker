#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>

using namespace std;

void dash() {
  for (int i = 0; i < 16; i++) {
    std::cout << "-";
  }
  std::cout << '\n';
}

// Make sure a thing is the thing
bool isQuit(string x){
  return x == "q" || x == "Q"
  || x == "quit" || x == "Quit" || x == "QUIT";
}
bool isSell(string x){
  return x == "sell" || x == "Sell"
  || x == "s" || x == "S";
}
bool isCash(string x){
  return x == "Cash" || x == "cash"
  || x == "C" || x == "c";
}
bool isCard(string x){
  return x == "e" || x == "E"
  || x == "card" || x == "Card";
}
bool isList(string x){
  return x == "list" || x == "List"
  || x == "ls" || x == "Ls" || x == "LS"
  || x == "l" || x == "L";
}
bool isHelp(string x){
  return x == "help" || x == "Help"
  || x == "H" || x == "h";

}

//  Lists the items in products.txt
void listItems() {
  ifstream a;
  a.open("products.txt");
  string word;
  while(!a.eof()){
    a >> word;
    if( a.eof()){
      break;
    }
    cout << word << " ";
    if (word == "$") {
      std::cout << '\n';
    }
  }
  a.close();
}
//  Lists options for tools to use
void listHelp(){
  std::cout << '\n';
  std::cout << "Use:-" << '\n';
  std::cout << "l / list / ls" << setw(20) << "To list Items"<< '\n';
  std::cout << "c / cash" << setw(30) << "when they pay cash" << '\n';
  std::cout << "e / card" << setw(30) << "when they pay card" << '\n';
  std::cout << "s / sell" << setw(49) << "To make a sell and post write receipt" << '\n';
}
//  Returns "Cash" or "Card"
string paymentMethod(string x){
  while(!isCard(x) || !isCash(x)){
    if(isCard(x)){
      return "Card";
    }else if(isCash(x)){
      return "Cash";
    }
    std::cout << "Choose [C] for cash and [E] for Card" << '\n';
    std::cin >> x;
  }
  return "not declared";
}

//  Get product name and price
// TODO: make it get only name
string getProductName(int x){
  ifstream a;
  a.open("products.txt");
  string word;
  string sentence = "";

  while(!a.eof()){
    a >> word;
    if( a.eof()){
      break;
    }
    if (word == to_string(x) ){
      a >> word;
      while (word != "$") {
        a >> word;
        sentence.append(word);
        sentence.append(" ");
      }
      return sentence;
    }
  }
  a.close();
  return "Product does not exist";
}

//  Gets prices
// int getPrice(int x){
//   ifstream a;
//   a.open("products.txt");
//   string word;
//   int sentence;
//
//   while(!a.eof()){
//
//     a >> word;
//     if( a.eof()){
//       break;
//     }
//     if (word == to_string(x) ){
//       std::cout << "x: " << x << '\n';
//       std::cout << "x+1: " << x+1 << '\n';
//       streampos oldpos = a.tellg();  // stores the position
//       a.seekg (oldpos);   // get back to the position
//       std::cout << "oldpos: " << oldpos << '\n';
//       std::cout << "seekg: " << a.seekg(100) << '\n';
//
//       // while (word != "$") {
//       //   a >> word;
//       //   sentence.append(word);
//       //   sentence.append(" ");
//       // }
//
//     }
//   }
//   a.close();
//
//   return sentence;
// }

//  Print out a full receipt in receipts.txt
void makeReceipt(string pay, int x){
  std::fstream a;
  a.open ("receipts.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  // a << "Sold a [" << getProductName(x) << "] for " << getPrice(x) << "$ by "<< paymentMethod(pay) << '\n' ;
  a << "Sold a item# " << x << " [" << getProductName(x) << "] by "<< paymentMethod(pay) << '\n' ;
  std::cout << "RECEIPT HAS BEEN MADE" << '\n';
  a.close();
}


int main(int argc, char const *argv[]) {

  bool ok;
  string A = "";

  while(1){
    ok = false;
    std::cout << '\n';
    std::cout << "Choose a command:" << '\n';
    std::cin >> A;

    if (isList(A)) {
      listItems();
    }else if(isHelp(A)){
      listHelp();
    }else if(isSell(A)){
      std::cout << "What is the product number" << '\n';

      //makes sure input is a number
      int num = 0;
      while(!ok){
        std::cin >> num;
        if(!cin.fail() && (cin.peek() == EOF || cin.peek() == '\n')){
          ok = true;
        }
        else{
          cout << "Product number is invalid. Choose a number" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }

      std::cout << "What is the payment method" << '\n';
      string pay;
      std::cin >> pay;
      makeReceipt(pay, num);
    }else if(isQuit(A)){
      string x;
      while(x != "y" || x != "Y" || x != "n" || x != "N"){
        std::cout << "are you sure? (Y or N)" << '\n';
        std::cin >> x;
        if (x == "y" || x == "Y") {
          break;
        }else if (x == "n" || x == "N") {
          continue;
        }
      }
    }
    else{
      std::cout << "Bad Command, type H for help" << '\n';
    }

    dash();
  }
  return 0;
}
