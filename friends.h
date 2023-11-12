#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Node structure for a linked list of friends
struct Node {
    User* friendUser;
    Node* next;

    Node(User* friendUser) : friendUser(friendUser), next(nullptr) {}
};

// LinkedList class to manage friends
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a new friend to the linked list
    void addFriend(User* friendUser) {
        Node* newNode = new Node(friendUser);
        newNode->next = head;
        head = newNode;
    }
};

// User class representing a user with a list of friends
class User {
private:
    std::string name;
    std::string email;
    std::string password;
    LinkedList friendsList;

public:
    User(std::string name, std::string email, std::string password)
        : name(name), email(email), password(password) {}

    std::string getEmail() const {
        return email;
    }

    // Authenticate the user based on the hashed password
    bool authenticate(std::string enteredPassword) const {
        // Replace with actual secure password authentication logic
        return enteredPassword == password;
    }

    // Add a friend to the user's friends list
    void addFriend(User* friendUser) {
        friendsList.addFriend(friendUser);
    }
};

// Graph class representing relationships between users
class Graph {
private:
    std::unordered_map<std::string, User*> users;

public:
    // Add a new user to the graph
    void addUser(User* user) {
        users[user->getEmail()] = user;
    }

    // Add a friendship between two users
    void addFriendship(User* user1, User* user2) {
        user1->addFriend(user2);
        user2->addFriend(user1);
    }

    // Authenticate a user based on email and password
    User* authenticateUser(std::string email, std::string password) const {
        auto it = users.find(email);
        if (it != users.end() && it->second->authenticate(password)) {
            return it->second;
        }
        return nullptr; // User not found or authentication failed
    }
};

int main() {
    // Create a graph representing relationships between users
    Graph userGraph;

    // Adding users to the graph
    User user1("John Doe", "john@example.com", "password123");
    User user2("Alice Smith", "alice@example.com", "securepassword");
    User user3("Bob Johnson", "bob@example.com", "pass123");

    userGraph.addUser(&user1);
    userGraph.addUser(&user2);
    userGraph.addUser(&user3);

    // Establishing friendships
    userGraph.addFriendship(&user1, &user2);
    userGraph.addFriendship(&user1, &user3);

    // Example usage: Authenticating a user
    std::string userEmail, userPassword;
    std::cout << "Enter your email: ";
    std::cin >> userEmail;
    std::cout << "Enter your password: ";
    std::cin >> userPassword;

    User* authenticatedUser = userGraph.authenticateUser(userEmail, userPassword);

    if (authenticatedUser != nullptr) {
        std::cout << "Authentication successful. Welcome back, " << authenticatedUser->getEmail() << "!" << std::endl;
    } else {
        std::cout << "Authentication failed. Please check your email and password." << std::endl;
    }

    return 0;
}
