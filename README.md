# Table-Driven-Predictive-Parser

This program uses a stack based algorithm along with a table driven predictive LR Parser to identify string that are accepted by the Context Free Grammar below:

S--> F = E

E--> E + T

E--> E - T

E--> T

T--> T * F

T--> T / F

T--> F

F--> ( E )

F--> a

Left Recursion was removed to create the following grammar:
('$' represents the empty string aka epsilon)

S--> F = E

E--> TQ

Q--> +TQ | -TQ | $

T--> FR

R--> *FR | /FR | $

F--> ( E ) | a

From the grammar above the first and follow sets of the non terminals were found to be

First(S) = (, a

First(E) = (, a

First(Q) = +, -, $

First(T) = (, a

First(R) = *, /, $

First(F) = (, a, b


Follow(S) = $

Follow(E) = ), $

Follow(Q) = ), $

Follow(T) = +, -, ), $

Follow(R) = +, -, ), $

Follow(F) = *, /, +, -, ), =, $


These sets were used to create the following LR Table

State:  a    b     =    +    -    *    /    (    )    $

S      F=E  F=E   " "  " "  " "  " "  " "  F=E  " "  " "

E      TQ   TQ    " "  " "  " "  " "  " "  TQ   " "  " "

Q      " "  " "   " "  +TQ  -TQ  " "  " "  " "   $    $

T      FR   FR    " "  " "  " "  " "  " "  FR   " "  " "

R      " "  " "   " "   $    $   *F   /F   " "   $    $

F      a    b     " "  " "  " "  " "  " "  (E)  " "  " "


The Code works by parsing through the string and adding the cooresponding table value on to the stack in reverse order. If the topmost value of the stack matches the front char of the input string, the top of the stack is popped and the element is erased from the input string. Once the string and stack are empty the input is accepted. If at any point and empty " " is pushed onto the stack the string is rejected.
