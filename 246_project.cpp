#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits.h>
#include <algorithm>
#include <Windows.h>

using namespace std;

#define NO_PARENT -1

int d;
void setConsoleColors(WORD attributes) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, attributes);
}


struct User {
    string name;
    string password;
};

struct DeliveryPerson {
    string name;
    string password;
    int maxWeight;
    vector<string> schedule;
};

struct Order {
    string userName;
    vector<int> weight;
    vector<int> profit;
    vector<vector<int>> graph;
};

vector<User> userAccounts;
vector<DeliveryPerson> deliveryAccounts;
vector<Order> orders;

void saveUserAccounts(const string &filename, const vector<User> &accounts) {
    ofstream file(filename);
    for (const auto &user : accounts) {
        file << user.name << " " << user.password << endl;
    }
}

void loadUserAccounts(const string &filename, vector<User> &accounts) {
    ifstream file(filename);
    string name, password;
    while (file >> name >> password) {
        accounts.push_back({name, password});
    }
}

void saveDeliveryAccounts(const string &filename, const vector<DeliveryPerson> &accounts) {
    ofstream file(filename);
    for (const auto &dp : accounts) {
        file << dp.name << " " << dp.password << " " << dp.maxWeight << endl;
    }
}

void loadDeliveryAccounts(const string &filename, vector<DeliveryPerson> &accounts) {
    ifstream file(filename);
    string name, password;
    int maxWeight;
    while (file >> name >> password >> maxWeight) {
        accounts.push_back({name, password, maxWeight});
    }
}

bool rabinKarp(const string &text, const string &pattern) {
    int d = 256;
    int q = 101;
    int m = pattern.size();
    int n = text.size();
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                return true;
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return false;
}

void userDashboard(const string &username);
void deliveryDashboard(const string &username);
void dijkstra(int adj[9][9], int sv, int ev);
int knapSack(int W, const vector<int> &wt, const vector<int> &val, int n);

// sv = startV;
//ev = endV;

bool findUser(const string &name, User &user) {
    for (const auto &u : userAccounts) {
        if (u.name == name) {
            user = u;
            return true;
        }
    }
    return false;
}

vector<DeliveryPerson>::iterator findDeliveryPerson(const string &name) {
    return find_if(deliveryAccounts.begin(), deliveryAccounts.end(), [&](const DeliveryPerson &d) { return d.name == name; });
}

bool isPasswordUnique(const string &password) {
    return none_of(deliveryAccounts.begin(), deliveryAccounts.end(), [&](const DeliveryPerson &d) { return d.password == password; });
}

void userLogin() {
    string name, password;
    cout<<endl;
    cout << "Enter name: ";
    cin >> name;
    cout<<endl;
    cout << "Enter password: ";
    cin >> password;

    User user;
    bool user_it = findUser(name, user);
    auto dp_it = findDeliveryPerson(name);
    if ((user_it && rabinKarp(user.password, password)) || (dp_it != deliveryAccounts.end() && rabinKarp(dp_it->password, password))) {
        cout<<endl; cout << "User login successful!\n";
        userDashboard(name);
    } else { cout<<endl;
        cout << "Invalid username or password.\n";
    }
}

void deliveryLogin() {
    string name, password;
    cout<<endl;
    cout << "Enter name: ";
    cin >> name;
    cout<<endl;
    cout << "Enter password: ";
    cin >> password;

    auto dp_it = findDeliveryPerson(name);
    User user;
    bool user_it = findUser(name, user);
    if ((dp_it != deliveryAccounts.end() && rabinKarp(dp_it->password, password)) || (user_it && rabinKarp(user.password, password))) { cout<<endl;
        cout << "Delivery person login successful!\n";
        deliveryDashboard(name);
    } else {
        cout << "Invalid username or password.\n";
    }
}

void userSignup() {
    string name, password;
    cout<<endl;
    cout << "Enter name: ";
    cin >> name;

    //Check
    cout<<endl;
    cout << "Enter password: ";
    cin >> password;
    if (!isPasswordUnique(password) || any_of(userAccounts.begin(), userAccounts.end(), [&](const User &u) { return u.password == password; })) {
        cout << "Password already exists. Please choose a different password.\n";
        return;
    }

    userAccounts.push_back({name, password});
    saveUserAccounts("users.txt", userAccounts); cout<<endl;
    cout << "User account created successfully!\n";
}

void deliverySignup() {
    string name, password;
    int maxWeight;
    cout << "Enter name: ";
    cin >> name;

    // Check (2)
    cout<<endl;
    cout << "Enter password: ";
    cin >> password;
    if (!isPasswordUnique(password) || any_of(deliveryAccounts.begin(), deliveryAccounts.end(), [&](const DeliveryPerson &dp) { return dp.password == password; })) {
        cout << "Password already exists. Please choose a different password.\n";
        return;
    }
    cout<<endl;

    cout << "Enter maximum weight your vehicle can carry: ";
    cout<<endl;
    cin >> maxWeight;

    deliveryAccounts.push_back({name, password, maxWeight});
    saveDeliveryAccounts("delivery.txt", deliveryAccounts);
    cout<<endl;
    cout << "Delivery person account created successfully!\n";
    cout<<endl;

}

void userDashboard(const string &username) {
    cout<<endl;
    cout << "Hello " << username << ", welcome to the user dashboard!" << endl;
    int choice;
    while (true) {
        cout<<endl;
        cout << "1. Place an order\n2. Logout\n\n\n\nEnter your choice: ";
        cout<<endl;
        cin >> choice;
        if (choice == 1) {



          cout<<endl;
             cout<<"Enter the Number of locations you want to deliver: "<<endl;
             cin>>d;

            int numItems;cout<<endl;
            cout << "Enter the number of items in the order: ";
            cin >> numItems;

            vector<int> weight(numItems);
            vector<int> profit(numItems);
            for (int i = 0; i < numItems; ++i) {
                cout << "Enter weight of item " << i + 1 << ": ";
                cin >> weight[i];
                cout << "Enter the cost of the items  " << i + 1 << ": ";
                cin >> profit[i];
            }

            orders.push_back({username, weight, profit, {}});  cout<<endl;
            cout<<endl;
            cout << "Order placed successfully!\n";
        } else if (choice == 2) {
            break;
        }
    }
}

void deliveryDashboard(const string &username) {cout<<endl;
    cout << "Hello " << username << ", welcome to the delivery person dashboard!" << endl;
    int choice;
    while (true) {cout<<endl;
        cout << "1. View and accept orders\n2. View schedule\n3. Logout\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            if (orders.empty()) {cout<<endl;
                cout << "No orders available.\n";
                continue;
            }
            for (int i = 0; i < orders.size(); ++i) {
                const auto &order = orders[i];
                cout << "Order " << i + 1 << ": " << order.userName << "\n";

                auto dp_it = findDeliveryPerson(username);
                if (dp_it != deliveryAccounts.end()) {
                    int maxProfit = knapSack(dp_it->maxWeight, order.weight, order.profit, order.weight.size());
                    cout << "Max Profit: " << maxProfit << "\n";

                    for (int j = 0; j < order.weight.size(); ++j) {
                        cout << "  Item " << j + 1 << ": Weight=" << order.weight[j] << ", Profit=" << order.profit[j] << "\n";
                    }

                    int adj[9][9] = {
                        {0, 4, 0, 0, 0, 0, 0, 8, 0},
                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
                        {0, 0, 4, 0, 10, 0, 2, 0, 0},
                        {0, 0, 0, 14, 0, 2, 0, 1, 6},
                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
                        {0, 0, 2, 0, 0, 0, 6, 7, 0}
                    };
                    dijkstra(adj, 0, d);

                }
            }cout<<endl;
            cout << "Enter the order number to accept: ";
            int orderNumber;
            cin >> orderNumber;
            if (orderNumber < 1 || orderNumber > orders.size()) {cout<<endl;
                cout << "Invalid order number.\n";
                continue;
            }
            auto &order = orders[orderNumber - 1];

            auto dp_it = findDeliveryPerson(username);
            if (dp_it != deliveryAccounts.end()) {
                int maxProfit = knapSack(dp_it->maxWeight, order.weight, order.profit, order.weight.size());
                if (maxProfit > 0) {
                    dp_it->schedule.push_back(order.userName);
                    orders.erase(orders.begin() + (orderNumber - 1));cout<<endl;
                    cout << "Order accepted successfully!\n";




                } else {cout<<endl;
                    cout << "Order cannot be accepted due to weight constraints.\n";
                }
            }
        } else if (choice == 2) {
            auto dp_it = findDeliveryPerson(username);
            if (dp_it != deliveryAccounts.end()) {
                if (dp_it->schedule.empty()) {cout<<endl;
                    cout << "No orders in the schedule.\n";
                } else {
                    cout << "Schedule:\n";cout<<endl;
                    for (const auto &user : dp_it->schedule) {
                        cout << user << "\n";
                    }
                }
            } else {cout<<endl;
                cout << "Delivery person not found.\n";
            }
        } else if (choice == 3) {
            break;
        }
    }
}

void printPath(int currentVertex, int parents[]) {
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents);
    printf("%d->", currentVertex);
}

void printSolution(int sv, int distances[], int parents[], int ev) {
    printf("Vertex\t      Distance\t         Path\n");
    for (int vertexIndex = 0; vertexIndex < ev; vertexIndex++) {
        if (vertexIndex != sv) {
            printf("%d -> %d \t\t %d \t\t", sv, vertexIndex, distances[vertexIndex]);
            printPath(vertexIndex, parents);
            printf("\n");
        }
    }
}

void dijkstra(int adj[9][9], int sv, int ev) {
    int shortestDistances[ev];
    bool added[ev];
    int parents[ev];

    for (int vertexIndex = 0; vertexIndex < ev; vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }

    shortestDistances[sv] = 0;
    parents[sv] = NO_PARENT;

    for (int i = 1; i < ev; i++) {
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;

        for (int vertexIndex = 0; vertexIndex < ev; vertexIndex++) {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }

        added[nearestVertex] = true;

        for (int vertexIndex = 0; vertexIndex < ev; vertexIndex++) {
            int edgeDistance = adj[nearestVertex][vertexIndex];

            if (edgeDistance > 0 && (shortestDistance + edgeDistance) < shortestDistances[vertexIndex]) {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

    printSolution(sv, shortestDistances, parents, ev);
}

int knapSack(int W, const vector<int> &wt, const vector<int> &val, int n) {
    vector<vector<int>> K(n + 1, vector<int>(W + 1));
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[n][W];
}

int main() {


    loadUserAccounts("users.txt", userAccounts);
    loadDeliveryAccounts("delivery.txt", deliveryAccounts);
    setConsoleColors(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
    system("cls");

    while (true) {
        cout<<endl;

        cout << "                                        "<< "Welcome to the Courier Service Management System\n";
        cout << "                                        "<<"--------------------------------------------------\n";

        cout << "Do you want to:\n";cout<<endl;
        cout << "1. Create an Account\n";cout<<endl;
        cout << "2. Login\n";cout<<endl;
        cout << "3. Quit\n";cout<<endl;
        cout << "Enter your choice: ";cout<<endl;
        string choice;
        cin >> choice;
        if (choice == "1") {cout<<endl;
            cout << "Create account as:\n";cout<<endl;
            cout << "1. User\n";cout<<endl;
            cout << "2. Delivery Person\n";cout<<endl;
            cout << "Enter your choice: ";cout<<endl;
            int type;
            cin >> type;
            if (type == 1) {
                userSignup();
            } else if (type == 2) {
                deliverySignup();
            } else {cout<<endl;
                cout << "Invalid choice!\n";cout<<endl;
            }
        } else if (choice == "2") {
            cout << "Login as:\n";cout<<endl;
            cout << "1. User\n";cout<<endl;
            cout << "2. Delivery Person\n";cout<<endl;
            cout << "Enter your choice: ";cout<<endl;
            int type;
            cin >> type;
            if (type == 1) {
                userLogin();
            } else if (type == 2) {
                deliveryLogin();
            } else {cout<<endl;
                cout << "Invalid choice!\n";cout<<endl;
            }
        } else if (choice == "3") {
            break;
        } else {cout<<endl;
            cout << "Invalid choice!\n";cout<<endl;
        }
    }
    return 0;
}



