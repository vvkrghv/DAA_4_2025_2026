#include<bits/stdc++.h>
using namespace std;

class SocialNetwork {
    map<string, vector<string>> friendsList;  // user -> list of friends

public:
    // Add new user
    void addUser(string name) {
        if (friendsList.find(name) == friendsList.end()) {
            friendsList[name] = {};
            cout << "User '" << name << "' added.\n";
        } else {
            cout << "User already exists!\n";
        }
    }

    // Add friendship (undirected)
    void addFriendship(string u1, string u2) {
        if (friendsList.find(u1) == friendsList.end() || friendsList.find(u2) == friendsList.end()) {
            cout << "Both users must exist!\n";
            return;
        }

        if (u1 == u2) {
            cout << "A user cannot be friend with themselves!\n";
            return;
        }

        // Prevent duplicates
        if (find(friendsList[u1].begin(), friendsList[u1].end(), u2) == friendsList[u1].end()) {
            friendsList[u1].push_back(u2);
            friendsList[u2].push_back(u1);
            cout << "Friendship added between " << u1 << " and " << u2 << ".\n";
        } else {
            cout << "They are already friends!\n";
        }
    }

    // Show friends
    void showFriends(string name) {
        if (friendsList.find(name) == friendsList.end()) {
            cout << "User not found.\n";
            return;
        }

        cout << name << "'s friends: ";
        if (friendsList[name].empty()) {
            cout << "No friends yet.\n";
            return;
        }

        for (string f : friendsList[name])
            cout << f << " ";
        cout << "\n";
    }

    // Recommend friends (friends of friends)
    void recommendFriends(string name) {
        if (friendsList.find(name) == friendsList.end()) {
            cout << "User not found.\n";
            return;
        }

        set<string> visited;
        queue<pair<string, int>> q;
        q.push({name, 0});
        visited.insert(name);
        set<string> recommended;

        while (!q.empty()) {
            string current = q.front().first;
            int level = q.front().second;
            q.pop();

            if (level >= 2) continue;

            for (string neighbor : friendsList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    if (level == 1 && neighbor != name)
                        recommended.insert(neighbor);
                    q.push({neighbor, level + 1});
                }
            }
        }

        cout << "Friend recommendations for " << name << ": ";
        if (recommended.empty())
            cout << "No recommendations found.";
        else
            for (string r : recommended) cout << r << " ";
        cout << "\n";
    }

    // Shortest connection (BFS)
    void shortestPath(string start, string target) {
        if (friendsList.find(start) == friendsList.end() || friendsList.find(target) == friendsList.end()) {
            cout << "Both users must exist!\n";
            return;
        }

        queue<pair<string, int>> q;
        set<string> visited;

        q.push({start, 0});
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front().first;
            int dist = q.front().second;
            q.pop();

            if (current == target) {
                cout << "Shortest connection between " << start << " and " << target
                     << " is " << dist << " degree(s).\n";
                return;
            }

            for (string neighbor : friendsList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push({neighbor, dist + 1});
                }
            }
        }

        cout << "No connection found between " << start << " and " << target << ".\n";
    }

    // Save to file
    void saveToFile(string filename) {
        ofstream out(filename);
        for (auto &p : friendsList) {
            out << p.first << ":";
            for (string f : p.second)
                out << f << ",";
            out << "\n";
        }
        out.close();
    }

    // Load from file
    void loadFromFile(string filename) {
        ifstream in(filename);
        if (!in) {
            cout << "No existing network found. Creating new one.\n";
            return;
        }

        friendsList.clear();
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            string user = line.substr(0, line.find(':'));
            string friendsStr = line.substr(line.find(':') + 1);
            addUser(user);

            stringstream ss(friendsStr);
            string friendName;
            while (getline(ss, friendName, ',')) {
                if (!friendName.empty()) {
                    addUser(friendName);
                    friendsList[user].push_back(friendName);
                }
            }
        }
        in.close();
    }
};

int main() {
    SocialNetwork sn;
    int choice;
    string u1, u2;

    // Load data from file (network.txt)
    sn.loadFromFile("network.txt");

    cout << "\n=== Social Network Menu ===\n";
    cout << "(Sample data loaded from 'network.txt' if available)\n";

    while (true) {
        cout << "\n=== Social Network Menu ===\n";
        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Show Friends\n";
        cout << "4. Recommend Friends\n";
        cout << "5. Shortest Path Between Users\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter user name: ";
                cin >> u1;
                sn.addUser(u1);
                break;
            case 2:
                cout << "Enter two user names: ";
                cin >> u1 >> u2;
                sn.addFriendship(u1, u2);
                break;
            case 3:
                cout << "Enter user name: ";
                cin >> u1;
                sn.showFriends(u1);
                break;
            case 4:
                cout << "Enter user name: ";
                cin >> u1;
                sn.recommendFriends(u1);
                break;
            case 5:
                cout << "Enter two user names: ";
                cin >> u1 >> u2;
                sn.shortestPath(u1, u2);
                break;
            case 6:
                cout << "Saving network and exiting...\n";
                sn.saveToFile("network.txt");
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
