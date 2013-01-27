#include <iostream>
#include <iomanip>
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

TermElement* addPolynomials (TermElement* root1, TermElement* root2) {
    TermElement* sum = NULL; // create our new list
    while (root1 != NULL) { // add all terms from root1
        sum = addTerm(sum, root1->degree, root1->coefficient);
        root1 = root1->next;
    }
    while (root2 != NULL) {
        sum = addTerm(sum, root2->degree, root2->coefficient);
        root2 = root2->next;
    }
    return sum; // add all terms from root1
}

TermElement* multiplyPolynomials (TermElement* root1, TermElement* root2) {
    TermElement* product = NULL; // create our new list
    TermElement* itr1 = root1; // create iterator for root1
    while (root2 != NULL) { // for each term in root2
        while (itr1 != NULL) { // add each product node for root1
            product = addTerm(product, root2->degree * itr1->degree, root2->coefficient * itr1->coefficient);
            itr1 = itr1->next;
        }
        itr1 = root1; // reset root1 iterator
        root2 = root2->next;
    }
    return product;
}

TermElement* derivative (TermElement* root) {
    if (root == NULL)
        return NULL;
    TermElement* deriv = addTerm(NULL, root->degree-1, root->coefficient * root->degree); // start derivative list
    while (root->next != NULL) { // for each term in the original polynomial, takes it derivative
        root = root->next;
        if (root->coefficient * root->degree != 0) { // only create a non-trivial node (coefficient != 0)
            deriv = addTerm(deriv, root->degree-1, root->coefficient * root->degree);
        }
    }
    return deriv; //return our list
}

void printPolyNomial(TermElement* root) {
    cout << "Coefficient | Degree" << endl 
         << "--------------------" << endl; // print table header
    while (root != NULL) {
        cout << setw(12) << root->coefficient << '|' << root->degree << endl; // print value for each entry setw sets field size
        root = root->next;
    }
    cout << endl;
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
    TermElement* test = addTerm(NULL, 2, 1);
    test = addTerm(test, 3, 5);
    test = addTerm(test, 1, -5);
    TermElement* test2 = addTerm(NULL, 3, 2);
    test2 = addTerm(test2, 8, 5);
    TermElement* testdir = derivative(test);
    TermElement* testdirdir = derivative(testdir);
    printPolyNomial(test);
    printPolyNomial(testdir);
    printPolyNomial(testdirdir);
    printPolyNomial(test);
    printPolyNomial(test2);
    printPolyNomial(addPolynomials(test, test2));
    printPolyNomial(multiplyPolynomials(test, test2));
}
