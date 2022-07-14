#include<iostream>
using namespace std;

template <class T> class Node
{
public:
    int row;
    int col;
    T data;
    Node *next;
};


template <class T>
void insertNode(Node<T> **head, int row_index, int col_index, T x)
{
    Node<T> *temp = *head;
    Node<T> *newNode;
    Node<T> *prevNode;

    if (!temp)
    {
        temp = new Node<T>();
        temp->row = row_index;
        temp->col = col_index;
        temp->data = x;
        temp->next = NULL;
        *head = temp;
    }

    else
    {
        while (temp->next != NULL) {
            prevNode = temp;
            if (temp->row == row_index and temp->col == col_index) {
                temp->data = temp->data + x;
                if (!temp->data) {
                    prevNode->next = temp->next;
                    delete(temp);
                    return;
                }
                return;
            }
            temp = temp->next;
        }

        if (temp->row == row_index and temp->col == col_index)
        {
            temp->data = temp->data + x;
            return;
        }

        newNode = new Node<T>();
        newNode->row = row_index;
        newNode->col = col_index;
        newNode->data = x;
        newNode->next = NULL;
        temp->next = newNode;
    }
}

template <class T>
void showList(Node<T> *start)
{
    Node<T> *temp = start;

    cout << "Row\t" << "Col\t" << "Data" << endl;
    while (temp != NULL) {
        cout << temp->row << "\t" << temp ->col << "\t" << temp->data << endl;
        temp = temp->next;
    }
}

template <class T>
void add(Node<T>* start1, Node<T>* start2) {

    Node<T>* t1 = start1;
    Node<T>* t2 = start2;
    Node<T>* addList = NULL;

    while (t1 != NULL && t2 != NULL)
    {
        if (t1->row == t2->row)
        {
            if (t1->col == t2->col)
            {
                if (t1->data + t2->data) {
                    insertNode<T>(&addList, t1->row, t1->col, t1->data + t2->data);
                    t1 = t1->next;
                    t2 = t2->next;
                }
                else {
                    t1 = t1->next;
                    t2 = t2->next;
                }
            }
            else if (t1->col < t2->col)
            {
                insertNode<T>(&addList, t1->row, t1->col, t1->data);
                t1 = t1->next;
            }
            else
            {
                insertNode<T>(&addList, t2->row, t2->col, t2->data);
                t2 = t2->next;
            }
        }
        else
        {

            if (t1->row < t2->row)
            {
                insertNode<T>(&addList, t1->row, t1->col, t1->data);
                t1 = t1->next;
            }

            else
            {
                insertNode<T>(&addList, t2->row, t2->col, t2->data);
                t2 = t2->next;
            }

        }

    }

    while (t1 != NULL)
    {
        insertNode<T>(&addList, t1->row, t1->col, t1->data);
        t1 = t1->next;
    }
    while (t2 != NULL)
    {
        insertNode<T>(&addList, t2->row, t2->col, t2->data);
        t2 = t2->next;
    }

    showList<T>(addList);

}

// template <class T>
// void Multiply(Node<T>* start1, Node<T>* start2) {

//     Node<T>* t1 = start1;
//     Node<T>* t2 = start2;

//     while (t1 != NULL) {
//         while (t2 != NULL) {

//             if (t1->col == t2->row)
//             {
//                 insertNode(&mulList, t1->row, t2->col, t1->data * t2->data);
//             }
//             t2 = t2->next;
//         }

//         t2 = start2;
//         t1 = t1->next;
//     }

// }

template <class T>
void Multiply2(Node<T>* start1, Node<T>* start2) {

    Node<T>* t1 = start1;
    Node<T>* t2 = start2;
    Node<T>* mulList = NULL;

    while (t1 != NULL)
    {
        t2 = start2;
        while (t2->next != NULL)
        {
            if (t1->col == t2->row)
            {
                insertNode<T>(&mulList, t1->row, t2->col, t1->data * t2->data);
            }
            t2 = t2->next;
        }
        if (t2->next == NULL)
        {
            if (t1->col == t2->row)
            {
                insertNode<T>(&mulList, t1->row, t2->col, t1->data * t2->data);
            }
        }

        t1 = t1->next;
    }

    showList<T>(mulList);

}

template <class T>
void Transpose(Node<T> *start) {
    //cout << start->data << endl;
    // while (start != NULL) {
    //     insertNode(&transList, start->col, start->row, start->data);
    //     start = start->next;
    // }
    Node<T>* temp = start;
    int totalSize = 0;
    int rows = 0;
    while (temp != NULL) {
        totalSize = max(totalSize, temp->col);
        rows++;
        temp = temp->next;
    }

    int cols = totalSize;

    int totalArray[totalSize + 1];
    for (int i = 0; i < totalSize + 1; i++) {
        totalArray[i] = 0;
    }

    //cout << endl;

    temp = start;
    for (int i = 0; i < totalSize + 1; i++) {
        int count = 0;
        while (temp != NULL) {
            if (temp->col == i) {
                count++;
            }
            temp = temp->next;
        }
        temp = start;
        totalArray[i] = count;
        //cout << totalArray[i] << " ";
    }

    //cout << endl;
    int indexArray[totalSize + 2];
    indexArray[0] = 1;
    for (int i = 1; i < totalSize + 2; i++) {
        indexArray[i] = indexArray[i - 1] + totalArray[i - 1];
        //cout << indexArray[i] << " ";
    }

    //cout << endl;

    T transposedMatrix[rows + 1][3];
    for (int i = 0; i < rows + 1; i++) {
        for (int j = 0; j < 3; j++) {
            transposedMatrix[i][j] = 0;
        }
    }



    temp = start;
    while (temp != NULL) {
        int tempVar = temp->row;
        temp->row = temp->col;
        temp->col = tempVar;

        int finalIndex = indexArray[temp->row];
        indexArray[temp->row]++;
        transposedMatrix[finalIndex][0] = temp->row;
        transposedMatrix[finalIndex][1] = temp->col;
        transposedMatrix[finalIndex][2] = temp->data;

        temp = temp->next;

    }
    cout << endl;
    cout << "Transposed Matrix" << endl;
    cout << "Row\t" << "Col\t" << "Data" << endl;
    for (int i = 1; i < rows + 1; i++) {
        for (int j = 0; j < 3; j++) {
            cout << transposedMatrix[i][j] << "\t";
        }
        cout << endl;
    }

}

// Driver Code
int main()
{

    int n;
    cout << "Choose an operation: " << endl;
    cout << "1) Add 2 Matrices " << endl;
    cout << "2) Multiply 2 Matrices " << endl;
    //cout << "3) Show Matrices " << endl;
    cout << "3) Transpose" << endl;
    cin >> n;


    if (n == 1) {

        int rows1, columns1;
        cout << "\nEnter dimensions of matrix 1 " << endl;
        cin >> rows1 >> columns1;
        long double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }

        int rows2, columns2;
        cout << "\nEnter dimensions of matrix 2 " << endl;
        cin >> rows2 >> columns2;
        long double y[rows2][columns2];
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                cin >> y[i][j];
            }
        }

        if (rows1 != rows2 or columns1 != columns2) {
            cout << "INVALID INPUTS" << endl;
            return 0;
        }

        Node<double> *first1 = NULL;
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < columns1; j++)
            {
                if (x[i][j] != 0)
                    insertNode<double>(&first1, i, j, x[i][j]);
            }
        }

        Node<double> *first2 = NULL;
        for (int i = 0; i < rows2; i++)
        {
            for (int j = 0; j < columns2; j++)
            {
                if (y[i][j] != 0)
                    insertNode<double>(&first2, i, j, y[i][j]);
            }
        }

        cout << endl;
        cout << "Addition" << endl;
        add(first1, first2);
        //showList(addList);

    }

    else if (n == 2) {

        int rows1, columns1;
        cout << "\nEnter dimensions of matrix 1 " << endl;
        cin >> rows1 >> columns1;
        long double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }

        int rows2, columns2;
        cout << "\nEnter dimensions of matrix 2 " << endl;
        cin >> rows2 >> columns2;
        long double y[rows2][columns2];
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                cin >> y[i][j];
            }
        }

        Node<float> *first1 = NULL;
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < columns1; j++)
            {
                if (x[i][j] != 0)
                    insertNode<float>(&first1, i, j, x[i][j]);
            }
        }

        Node<float> *first2 = NULL;
        for (int i = 0; i < rows2; i++)
        {
            for (int j = 0; j < columns2; j++)
            {
                if (y[i][j] != 0)
                    insertNode<float>(&first2, i, j, y[i][j]);
            }
        }

        if (columns1 != rows2) {
            cout << "INVALID INPUTS" << endl;
            return 0;
        }

        cout << endl;
        cout << "Multiplication" << endl;
        Multiply2(first1, first2);
        //showList(mulList);

    }

    else if (n == 3) {
        int rows1, columns1;
        cout << "\nEnter dimensions of matrix 1 " << endl;
        cin >> rows1 >> columns1;
        long double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }

        Node<double> *first1 = NULL;
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < columns1; j++)
            {
                if (x[i][j] != 0)
                    insertNode<double>(&first1, i, j, x[i][j]);
            }
        }

        Transpose(first1);
    }

    else {
        cout << "Invalid Input" << endl;
    }


    // int sparseMatrix1[4][3] = {
    //     { 2, 0, 3},
    //     { 1, 2, 5},
    //     { 9, 8, 0},
    //     { 0, 0, 4}
    // };

    // int sparseMatrix2[3][4] = {
    //     { 0, 5, 0, 6},
    //     { 2, 0, 4, 0},
    //     { 0, 0, 7, 0}
    // };

    // int sparseMatrix2[2][2] = {
    //     { 1, 2},
    //     {3, 4}
    // };


    // Node *first1 = NULL;
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         if (sparseMatrix2[i][j] != 0)
    //             insertNode(&first1, i, j,
    //                             sparseMatrix2[i][j]);
    //     }
    // }

    // showList(first1);

    // Transpose(first1);
    // cout << endl;
    // cout << endl;
    // showList(transList);
    // cout << endl;

    // Node *first2 = NULL;
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         if (sparseMatrix2[i][j] != 0)
    //             insertNode(&first2, i, j,
    //                             sparseMatrix2[i][j]);
    //     }
    // }

    // showList(first1);
    // cout << endl;
    // cout << endl;
    // showList(first2);
    // cout << endl;
    // cout << endl;
    // add(first1, first2);
    // showList(addList);
    // cout << endl;
    // cout << endl;
    // Multiply2(first1, first2);
    // //cout << mulList->data << "-------" << endl;
    // showList(mulList);


    return 0;
}