// Table Driven Predictive Parser
// By: Jeremy Rico
//
// Description: This program uses a Table Driven Predictive Parser to find all
// string that adheres to the following Context Free Grammer:
// S--> F = E
// E--> E + T
// E--> E - T
// E--> T
// T--> T * F
// T--> T / F
// T--> F
// F--> ( E )
// F--> a

// Left Recursion was removed to create the following grammar:
// ('$' represents the empty string aka epsilon)
// S--> F = E
// E--> TQ
// Q--> +TQ | -TQ | $
// T--> FR
// R--> *FR | /FR | $
// F--> ( E ) | a

// The first and follow sets for the above grammar were calculated and used
// to create the LR Table in line 58

#include <iostream>
#include <stack>
#include <stdexcept>

// Recursive function to print out the contents of the stack in reverse order
void print_stack(std::stack<char> k) {
  if (k.empty()) {
    return;
  }
  char temp = k.top();
  k.pop();
  print_stack(k);
  std::cout << temp << " ";
}

// Pushes the input string into the stack one char at a time in reverse order
void push(std::stack<char> &k, const std::string &s) {
  for (int i = s.length() - 1; i >= 0; i--) {
    k.push(s.at(i));
  }
}

int main() {
  std::string input;
  std::stack<char> myStack;
  int current_row;

  std::cout << "Please input a string followed by '$': ";
  std::getline(std::cin, input);

  std::string parse_table[6][10] = {
      {"F=E", "F=E", " ", " ", " ", " ", " ", "F=E", " ", " "},
      {"TQ", "TQ", " ", " ", " ", " ", " ", "TQ", " ", " "},
      {" ", " ", " ", "+TQ", "-TQ", " ", " ", " ", "$", "$"},
      {"FR", "FR", " ", " ", " ", " ", " ", "FR", " ", " "},
      {" ", " ", " ", "$", "$", "*F", "/F", " ", "$", "$"},
      {"a", "b", " ", " ", " ", " ", " ", "(E)", " ", " "}};

  push(myStack, "S$"); // push starting state to the stack

  // run until all values have been popped from the stack
  while (!myStack.empty()) {
    while (myStack.top() != input.front()) {

      // Set the row depending on which value is at the top of the stack
      if (myStack.top() == 'S') {
        current_row = 0;
      } else if (myStack.top() == 'E') {
        current_row = 1;
      } else if (myStack.top() == 'Q') {
        current_row = 2;
      } else if (myStack.top() == 'T') {
        current_row = 3;
      } else if (myStack.top() == 'R') {
        current_row = 4;
      } else if (myStack.top() == 'F') {
        current_row = 5;
      }

      // Set the column depending on which char is at the front of input
      if (input.front() == 'a') {
        myStack.pop();
        push(myStack, parse_table[current_row][0]);
      } else if (input.front() == 'b') {
        myStack.pop();
        push(myStack, parse_table[current_row][1]);
      } else if (input.front() == '=') {
        myStack.pop();
        push(myStack, parse_table[current_row][2]);
      } else if (input.front() == '+') {
        myStack.pop();
        push(myStack, parse_table[current_row][3]);
      } else if (input.front() == '-') {
        myStack.pop();
        push(myStack, parse_table[current_row][4]);
      } else if (input.front() == '*') {
        myStack.pop();
        push(myStack, parse_table[current_row][5]);
      } else if (input.front() == '/') {
        myStack.pop();
        push(myStack, parse_table[current_row][6]);
      } else if (input.front() == '(') {
        myStack.pop();
        push(myStack, parse_table[current_row][7]);
      } else if (input.front() == ')') {
        myStack.pop();
        push(myStack, parse_table[current_row][8]);
      } else if (input.front() == '$') {
        myStack.pop();
        push(myStack, parse_table[current_row][9]);
      }

      // in the case that a rule goes to epsilon, pop $ from the stack, then
      // check if the value before '$' is equal to the front char of input
      if (myStack.top() == '$' && myStack.size() > 1) {
        myStack.pop();
        // if, at any point, a rule has led to an empty string being added to
        // the stack, the string is not accepted.
      } else if (myStack.top() == ' ') {
        throw std::range_error("String not accpeted :(");
      }
    }

    // if a match is found between the top of the stack and the front of the
    // input string; print out the contents of the stack, pop from the stack,
    // and erase the first element of the input string.
    if (myStack.top() == input.front()) {
      print_stack(myStack);
      std::cout << "\tInput: " << input << std::endl;
      myStack.pop();
      input.erase(0, 1);
    }
  }

  // if we have gotten to this point without throwing an exception, the string
  // must be accepted. Nevertheless, check to make sure both the stack and the
  // input are empty.
  if (myStack.empty() && input == "") {
    std::cout << "Accepted!" << std::endl;
  }

  return 0;
}
