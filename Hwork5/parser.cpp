#include <iostream>
using namespace std;

/*
I := iESI' -
I' := eS | epsilon -
E := GE' -
E' := oGE' | epsilon -
G := x | y | z | w -
S := s | dLb
L := sL'
L' := L | epsilon
*/

bool terminal(char symbol, string& s);
bool I(string& s);
bool I_prime(string& s);
bool E(string& s);
bool E_prime(string& s);
bool G(string& s);
bool S(string& s);
bool L(string& s);
bool L_prime(string& s);
bool parse(string s);

int main() {
    string s = "ixdssbe";
    if (parse(s)) {
        cout << "Parsing successful" << endl;
    }
    else {
        cout << "Parsing failed" << endl;
    }
}

bool terminal(char symbol, string& s) {
    if (!(s.empty()) && s[0] == symbol) {
        s = s.substr(1);
        return true;
    }
    
    return false;
}

bool I(string& s) {
    if (terminal('i', s)) {
        if (E(s)) {
            if (S(s)) {
                return I_prime(s);
            }
        }
    }

    return false;
}

bool I_prime(string& s) {
    string state = s;
    if (terminal('e', s)) {
        if (S(s)) {
            return true;
        }
    }

    s = state;
    return true;
}

bool E(string& s) {
    if (G(s)) {
        return E_prime(s);
    }

    return false;
}

bool E_prime(string& s) {
    string state = s;

    if (terminal('o', s)) {
        if (G(s)) {
            if (E_prime(s)) {
                return true;
            }
        }
    }

    s = state;
    return true;
}

bool G(string& s) {
    if (terminal('x', s)) {
        return true;
    } 
    else if (terminal('y', s)) {
        return true;
    }
    else if (terminal('z', s)) {
        return true;
    }
    else if (terminal('w', s)) {
        return true;
    }
    
    return false;
}

bool S(string& s) {
    string state = s;

    if (terminal('s', s)) {
        return true;
    }
    
    s = state;

    if (terminal('d', s)) {
        if (L(s)) {
            if (terminal('b', s)) {
                return true;
            }
        }
    }

    return false;
}

bool L(string& s) {
    if (terminal('s', s)) {
        return L_prime(s);
    }
    return false;
}

bool L_prime(string& s) {
    string state = s;

    if (L(s)) {
        return true;
    }

    s = state;
    return true;
}

bool parse(string s) {
    I(s);
    return s.empty();
}
