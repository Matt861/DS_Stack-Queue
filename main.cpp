// Authors: Matt Windham 51 & Kevin Kim 19
// Due date: 3/29/2017
// Programming Assignment Number 5
// Spring 2017 - CS 3358 - Section Number 2
//
// Instructor: Husain Gholoom
//
// This program will create a stack and a queue using inputs from the user.
// It will compare the stack and the queue and output whether the elements
// are the same in the same corresponding positions and if they have matching
// symbols.

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Stack
{
private:
    T *stackArray;
    int stackSize;
    int top;
    
public:
    Stack(int);
    Stack(const Stack&);
    ~Stack();
    void push(T);
    void pop(T &);
    bool isFull();
    bool isEmpty();
};

template <class T>
class Queue
{
private:
    T *queueArray;
    int queueSize;
    int front;
    int rear;
    int numItems;
public:
    Queue(int);
    Queue(const Queue &);
    ~Queue();
    void enqueue(T);
    void dequeue(T &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();
};

template <class T>
bool stackQueueCheck(Stack<T>, Queue<T>);

template <class T>
bool matchGroupSymbols(Stack<T>);

int main()
{
    int menuInput;          //integer value for menu input
    //1 = run program, 9 = terminate program
    bool menuSwitch = true; //boolean for menu switch
    //T = run again, F = terminate program
    
    cout << "*** Welcome to My stack / Queue Program ***"
    << endl << endl
    << "The function of this program is to :"
    << endl << endl
    << "\t1-\tValidate that a stack and a" << endl
    << "\t\tqueue is identical." << endl
    << "\t\tStacks / queues are same if" << endl
    << "\t\tthey have the same number of elements , symbols ," << endl
    << "\t\tand their elements and symbols at the" << endl
    << "\t\tcorresponding positions are the same."
    << endl << endl
    << "\t2-\tThe program also outputs whether the elements" << endl
    << "\t\tdo have the same matching group symbols."
    << endl << endl << endl;
    
    do
    {
        cout << "Select from the following menu" << endl
        << "1.\tEnter Stack / Queue Values." << endl
        << "9.\tTerminate the program.\t";
        
        cin >> menuInput;
        switch(menuInput)
        {
            case 1:
                if(cin.get() == '\n')
                {
                    string stackExp,            //string to hold expression for stack
                    queueExp;            //string to hold expression for queue
                    bool matchingSymbols,       //boolean for whether they have the same elements or symbols
                    //T = same symbols, F = differing symbols
                    matchingGroupSymbols;  //boolean for whether they have matching group symbols
                    //T = matching, F = not matching
                    
                    cout << endl << "Enter Stack Values terminated by ;\t";
                    
                    getline(cin, stackExp, ';');
                    
                    Stack<char> charStack(stackExp.size()); //stack holding characters from stackExp
                    
                    for(int count = 0; count < stackExp.size(); count++)
                    {
                        charStack.push(stackExp.at(count));
                    }
                    
                    cout << "Enter Queue Values terminated by ;\t";
                    
                    getline(cin, queueExp, ';');
                    
                    Queue<char> charQueue(queueExp.size()); //queue holding characters from queueExp
                    
                    for(int count = 0; count < queueExp.size(); count++)
                    {
                        charQueue.enqueue(queueExp.at(count));
                    }
                    
                    Stack<char> stackCopy(charStack);       //copy of charStack
                    Stack<char> flipStack(stackExp.size()); //stack to hold flipped charStack
                    char temp;
                    
                    while(stackCopy.isEmpty() != true)
                    {
                        stackCopy.pop(temp);
                        flipStack.push(temp);
                    }
                    
                    matchingSymbols = stackQueueCheck(flipStack, charQueue);
                    
                    if(matchingSymbols)
                    {
                        cout << endl
                        << "Stack and Queue are identical" << endl << endl;
                    }
                    else
                    {
                        cout << endl << "Stack and Queue are not identical"
                        << endl << endl;
                    }
                    
                    matchingGroupSymbols = matchGroupSymbols(flipStack);
                    
                    if(matchingGroupSymbols)
                    {
                        cout << "First Expression does have "
                        << "matching group symbols."
                        << endl << endl << endl;
                    }
                    else
                    {
                        cout << "First Expression does not have matching "
                        << "group symbols."
                        << endl << endl << endl;
                    }
                }
                else
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Invalid Option" << endl << endl;
                }
                
                break;
                
            case 9:
                menuSwitch = false;
                cout << endl << endl << "*** Program is terminated. Written by "
                "Kevin Kim and Matt Windham ***" << endl << endl;
                break;
                
            default:
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Option" << endl << endl;
        }
    }while(menuSwitch);
    return 0;
}

template <class T>
bool stackQueueCheck(Stack<T> stack, Queue<T> queue)
{
    bool check = true;
    Stack<T> tempStack(stack);
    Queue<T> tempQueue(queue);
    T tempStackChar,
    tempQueueChar;
    
    queue.dequeue(tempQueueChar);
    
    while(tempStack.isEmpty() == false && tempQueue.isEmpty() == false)
    {
        tempStack.pop(tempStackChar);
        queue.dequeue(tempQueueChar);
        
        if(tempStackChar != tempQueueChar)
            check = false;
    }
    
    return check;
}

template <class T>
bool matchGroupSymbols(Stack<T> stack)
{
    bool groupCheck = true,
    numberCheck = false,
    totalCheck = false;
    T tempChar;
    int openType1 = 0,
    openType2 = 0,
    openType3 = 0,
    openType4 = 0,
    closeType1 = 0,
    closeType2 = 0,
    closeType3 = 0,
    closeType4 = 0;
    
    while(stack.isEmpty() == false)
    {
        stack.pop(tempChar);
        
        switch(tempChar)
        {
            case '(':
                openType1++;
                break;
            case '{':
                openType2++;
                break;
            case '[':
                openType3++;
                break;
            case '<':
                openType4++;
                break;
            case ')':
                closeType1++;
                break;
            case '}':
                closeType2++;
                break;
            case ']':
                closeType3++;
                break;
            case '>':
                closeType4++;
                break;
            default:
                break;
        }
        
        if(openType1 < closeType1 || openType2 < closeType2 ||
           openType3 < closeType3 || openType4 < closeType4)
            groupCheck = false;
    }
    if(openType1 == closeType1 && openType2 == closeType2 &&
       openType3 == closeType3 && openType4 == closeType4)
        numberCheck = true;
    
    if(groupCheck == true && numberCheck == true)
        totalCheck = true;
    
    return totalCheck;
}

//Constructor
template <class T>
Stack<T>::Stack(int size)
{
    stackArray = new T[size];
    stackSize = size;
    top = -1;
}

//Copy constructor
template <class T>
Stack<T>::Stack(const Stack &obj)
{
    //Create stack array
    if(obj.stackSize > 0)
        stackArray = new T[obj.stackSize];
    else
        stackArray = NULL;
    
    //Copy the stackSize attribute
    stackSize = obj.stackSize;
    
    //Copy the stack contents
    for(int count = 0; count < stackSize; count++)
        stackArray[count] = obj.stackArray[count];
    
    //Set the top of the stack
    top = obj.top;
}

//Destructor
template <class T>
Stack<T>::~Stack()
{
    if(stackSize > 0)
        delete [] stackArray;
}

template <class T>
void Stack<T>::push(T item)
{
    if(isFull())
    {
        cout << "The stack is full.\n";
    }
    else
    {
        if(item != ' ')
        {
            top++;
            stackArray[top] = item;
        }
    }
}

template <class T>
void Stack<T>::pop(T &item)
{
    if(isEmpty())
    {
        cout << "the stack is empty.\n";
    }
    else
    {
        item = stackArray[top];
        top--;
    }
}

template <class T>
bool Stack<T>::isFull()
{
    bool status;
    
    if(top == stackSize - 1)
        status = true;
    else
        status = false;
    
    return status;
}

template <class T>
bool Stack<T>::isEmpty()
{
    bool status;
    
    if(top == -1)
        status = true;
    else
        status = false;
    
    return status;
}

//Constructor
template <class T>
Queue<T>::Queue(int s)
{
    queueArray = new T[s];
    queueSize = s;
    front = -1;
    rear = -1;
    numItems = 0;
}

//Copy Constructor
template <class T>
Queue<T>::Queue(const Queue &obj)
{
    queueArray = new T[obj.queueSize];
    
    queueSize = obj.queueSize;
    front = obj.front;
    rear = obj.rear;
    numItems = obj.numItems;
    
    for(int count = 0; count < obj.queueSize; count++)
    {
        queueArray[count] = obj.queueArray[count];
    }
}

//Destructor
template <class T>
Queue<T>::~Queue()
{
    delete [] queueArray;
}

template <class T>
void Queue<T>::enqueue(T item)
{
    if(isFull())
    {
        cout << "The queue is full.\n";
    }
    else
    {
        if(item != ' ')
        {
            rear = (rear + 1) % queueSize;
            queueArray[rear] = item;
            numItems++;
        }
    }
}

template <class T>
void Queue<T>::dequeue(T &item)
{
    if(isEmpty())
    {
        cout << "The queue is empty.\n";
    }
    else
    {
        front = (front + 1) % queueSize;
        item = queueArray[front];
        numItems--;
    }
}

template <class T>
bool Queue<T>::isEmpty() const
{
    bool status;
    
    if(numItems > 0)
        status = false;
    else
        status = true;
    
    return status;
}

template <class T>
bool Queue<T>::isFull() const
{
    bool status;
    
    if(numItems < queueSize)
        status = false;
    else
        status = true;
    
    return status;
}

template <class T>
void Queue<T>::clear()
{
    front = queueSize - 1;
    rear = queueSize - 1;
    numItems = 0;
}