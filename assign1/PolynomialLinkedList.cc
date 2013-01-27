#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

struct TermElement {
    int degree; // degree of this term
    double coefficient; // ceofficient of this term
    TermElement* next; // pointer to next node in this polynomial
};

double evaluate (TermElement* root, double x) {
    if (root == NULL) // return 0 for empty term
        return 0;
    return pow(x, root->degree) * root->coefficient; // return value of the term at that point
}

TermElement* addTerm (TermElement* root, int degree, double coefficient) {
    if (root == NULL) { // no polynomial
        root = (TermElement*) malloc(sizeof(TermElement)); // create node, to be return
        root->degree = degree; // populate new node
        root->coefficient = coefficient;
        root->next = NULL;
    }
    else if (root->degree == degree) { // shares degree with root, update coefficient
        root->coefficient += coefficient;
        if (root->coefficient == 0) { // element root node since coefficient is 0, return rest of list
            TermElement* toR = root->next;
            free(root);
            return toR;
        }
    }
    else { // modifying an existing polynomial
        TermElement* cur = root;
        if (cur->degree < degree) { // the new node should be root
            root = (TermElement*) malloc(sizeof(TermElement)); // create node, to be return as root
            root->degree = degree;
            root->coefficient = coefficient;
            root->next = cur;
        }
        else {
            while (cur->next != NULL && cur->next->degree > degree) { // traverse until we are before a node with a lower or equal coefficient to the one we are adding or we hit the end of the list
                cur = cur->next;
            }
            if (cur->next != NULL && cur->next->degree == degree) { // a node of the same degree exists, sum the coefficients
                cur->next->coefficient += coefficient;
                if (cur->next->coefficient == 0) { // if the new coefficient is zero, remove the term
                    TermElement* temp = cur->next; // save the term to free it
                    cur->next = cur->next->next; // change pointer to skip over it
                    free(temp); // free the term
                }
            }
            else { // creating a new term
                TermElement* newNode = (TermElement*) malloc(sizeof(TermElement)); // create node
                newNode->degree = degree; // populate
                newNode->coefficient = coefficient;
                newNode->next = cur->next; // point it to next
                cur->next = newNode; // point previous term to it
            }
        }
    }
    return root;
}

double evaluatePolynomial (TermElement* root, double x) {
    double total = 0;
    while (root != NULL) { // iterate over polynomial
        total += evaluate(root, x); // add each term to total
        root = root->next;
    }
    return total;
}

TermElement* derivative (TermElement* root) {
    TermElement* deriv = (TermElement*) malloc(sizeof(TermElement)); // start derivative list
    deriv->coefficient = root->coefficient * root->degree; // populate first derivative term
    deriv->degree = root->degree - 1;
    TermElement* cur = deriv; // set it to cur for the loop
    root = root->next;
    while (root != NULL) { // for each term in the original polynomial, takes it derivative
        TermElement* next = (TermElement*) malloc(sizeof(TermElement));
        next->coefficient = root->coefficient * root->degree; // populate derivative term
        if (next->coefficient == 0) { // do not add terms with coefficients of 0
            free(next);
            root = root->next;
            break;
        }
        next->degree = root->degree - 1;
        cur->next = next; // add it to our list
        cur = next; // get ready for next term
        root = root->next;
    }
    cur->next = NULL; // end our list
    return deriv; //return our list
}

void freeList (TermElement* root) {
    while (root != NULL) { // loop through list free storing next and freeing head until there is no head to free
        TermElement* temp = root;
        root = root->next;
        free(temp);
    }
}

int main (void) {
    // main is where i do testing, i imagine you will do it here as well
    TermElement* test = addTerm(NULL, 2, 2);
    test = addTerm(test, 3, 5);
    test = addTerm(test, 1, -5);
    cout << evaluatePolynomial(test, 3) << endl;
    TermElement* testdir = derivative(test);
    TermElement* testdirdir = derivative(testdir);
    while (test != NULL) {
        cout << test->degree << "\t" << test->coefficient << endl;
        test = test->next;
    }
    cout << evaluatePolynomial(testdir, 3) << endl;
    while (testdir != NULL) {
        cout << testdir->degree << "\t" << testdir->coefficient << endl;
        testdir = testdir->next;
    }
    cout << evaluatePolynomial(testdirdir, 3) << endl;
    while (testdirdir != NULL) {
        cout << testdirdir->degree << "\t" << testdirdir->coefficient << endl;
        testdirdir = testdirdir->next;
    }
}
