#include <iostream>
#include <limits.h>
#include <stdlib.h>
using namespace std;

#define max 100
#define infinity INT_MAX
#define nil -1

int n;
int adj[max][max];
int predecessor[max];
int pathlength[max];
int ispresent_in_queue[max];
int front, rear;
int queue[max];

void initialize_queue();
void insert_queue(int u);
int delete_queue();
int isempty_queue();
void create_graph();
void findpath(int s, int v);
int bellmanford(int s);

int main() {
    int flag, s, v;
    create_graph();
    cout << "Enter source vertex: ";
    cin >> s;
    flag = bellmanford(s);
    if (flag == -1) {
        cout << "Error: Negative cycle in graph" << endl;
        exit(1);
    }
    while (1) {
        cout << "Enter destination vertex (-1 to quit): ";
        cin >> v;
        if (v == -1)
            break;
        if (v < 0 || v >= n)
            cout << "This vertex does not exist";
        else if (v == s)
            cout << "Source and destination vertices are same" << endl;
        else if (pathlength[v] == infinity)
            cout << "There is no path from source to destination vertex" << endl;
        else
            findpath(s, v);
    }
    return 0;
}

void findpath(int s, int v) {
    int i, u;
    int path[max];
    int shortdist = 0;
    int count = 0;
    while (v != s) {
        count++;
        path[count] = v;
        u = predecessor[v];
        shortdist += adj[u][v];
        v = u;
    }
    count++;
    path[count] = s;
    cout << "Shortest path is: ";
    for (i = count; i >= 1; i--)
        cout << path[i];
    cout<<endl;
    cout << "Shortest distance is: " << shortdist << endl;
}

int bellmanford(int s) {
    int i, current;
    for (i = 0; i < n; i++) {
        predecessor[i] = nil;
        pathlength[i] = infinity;
        ispresent_in_queue[i] = false;
    }
    initialize_queue();
    pathlength[s] = 0;
    insert_queue(s);
    ispresent_in_queue[s] = true;
    while (!isempty_queue()) {
        current = delete_queue();
        ispresent_in_queue[current] = false;
        for (i = 0; i < n; i++) {
            if (adj[current][i] != 0 && pathlength[i] > pathlength[current] + adj[current][i]) {
                pathlength[i] = pathlength[current] + adj[current][i];
                predecessor[i] = current;
                if (!ispresent_in_queue[i]) {
                    insert_queue(i);
                    ispresent_in_queue[i] = true;
                }
            }
        }
    }
    // Check for negative cycles
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != 0 && pathlength[j] > pathlength[i] + adj[i][j]) {
                return -1; // Negative cycle detected
            }
        }
    }
    return 1;
}

void initialize_queue() {
    for (int i = 0; i < max; i++)
        queue[i] = 0;
    rear = -1;
    front = -1;
}

int isempty_queue() {
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

void insert_queue(int added_item) {
    if (rear == max - 1) {
        cout << "Queue is full" << endl;
        exit(1);
    } else {
        if (front == -1)
            front = 0;
        rear = rear + 1;
        queue[rear] = added_item;
    }
}

int delete_queue() {
    int d;
    if (front == -1 || front > rear) {
        cout << "Queue is empty" << endl;
        exit(1);
    } else {
        d = queue[front];
        front = front + 1;
    }
    return d;
}

void create_graph() {
    int m_e, origin, destin, wt;
    cout << "Enter the number of vertices: ";
    cin >> n;
    m_e = n * (n - 1);
    for (int i = 1; i <= m_e; i++) {
        cout << "Enter edges (-1 -1 to quit) " << i << ":";
        cin >> origin >> destin;
        if ((origin == -1) && (destin == -1))
            break;
        cout << "Enter weight for this edge: ";
        cin >> wt;
        if (origin >= n || destin >= n || origin < 0 || destin < 0) {
            cout << "Invalid edge!" << endl;
        } else
            adj[origin][destin] = wt;
    }
}


//output:
/*
Enter the number of vertices: 5
Enter edges (-1 -1 to quit) 1:1 0
Enter weight for this edge: 6
Enter edges (-1 -1 to quit) 2:1 2
Enter weight for this edge: 5
Enter edges (-1 -1 to quit) 3:2 3
Enter weight for this edge: -4
Enter edges (-1 -1 to quit) 4:0 4
Enter weight for this edge: 7
Enter edges (-1 -1 to quit) 5:2 4
Enter weight for this edge: -3
Enter edges (-1 -1 to quit) 6:-1 -1
Enter source vertex: 1
Enter destination vertex (-1 to quit): 4
Shortest path is: 124
Shortest distance is: 2
Enter destination vertex (-1 to quit): 3
Shortest path is: 123
Shortest distance is: 1
Enter destination vertex (-1 to quit):
*/


//differnce between this and previous code: 
/* previous code used--->
          int k=0; 
          if(s == current)
            k++;
          if(k>n)
            return -1; //negative cycle reachable from source vertex

This code used ---> 
        for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != 0 && pathlength[j] > pathlength[i] + adj[i][j]) {
                return -1; // Negative cycle detected
            }
        }
    }
*/
