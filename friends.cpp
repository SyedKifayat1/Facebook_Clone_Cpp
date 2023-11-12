#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

class User;

class FriendshipGraph {
private:
    std::unordered_map<User*, std::unordered_set<User*>> adjacencyList;

public:
    // Function to add a user to the graph
    void addUser(User* user) {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            adjacencyList[user] = std::unordered_set<User*>();
        }
    }

    // Function to add a friendship (undirected edge)
    void addFriendship(User* user1, User* user2) {
        adjacencyList[user1].insert(user2);
        adjacencyList[user2].insert(user1);
    }

    // Function to display friends of a user
    void displayFriends(User* user) {
        std::cout << "Friends of " << user->getName() << ": ";
        for (const auto& friendNode : adjacencyList[user]) {
            std::cout << friendNode->getName() << " ";
        }
        std::cout << std::endl;
    }
};

class Friendship {
private:
    User* user1;
    User* user2;
    std::string status;  // "pending", "accepted", "rejected", "cancelled"

public:
    // Constructor
    Friendship(User* user1, User* user2) : user1(user1), user2(user2), status("pending") {}

    // Function to add a friend (send a friendship request)
    void addFriend(FriendshipGraph& graph) {
        if (status == "pending" || status == "rejected" || status == "cancelled") {
            status = "pending";
            std::cout << user1->getName() << " sent a friend request to " << user2->getName() << "." << std::endl;
            graph.addFriendship(user1, user2);
        }
    }

    // Function to accept a pending friendship request
    void acceptFriendship() {
        if (status == "pending") {
            status = "accepted";
            std::cout << user1->getName() << " and " << user2->getName() << " are now friends." << std::endl;
        }
    }

    // Function to reject a pending friendship request
    void rejectFriendship() {
        if (status == "pending") {
            status = "rejected";
            std::cout << user1->getName() << "'s friendship request to " << user2->getName() << " is rejected."
                      << std::endl;
        }
    }

    // Function to cancel an existing friendship
    void cancelFriendship() {
        if (status == "accepted") {
            status = "cancelled";
            std::cout << user1->getName() << " and " << user2->getName() << " are no longer friends." << std::endl;
        }
    }
};

class User {
private:
    std::string name;

public:
    User(const std::string& name) : name(name) {}

    // Getter for user name
    std::string getName() const {
        return name;
    }
};

int main() {
    // Create a FriendshipGraph
    FriendshipGraph friendshipGraph;

    // Create users
    User user1("John Doe");
    User user2("Alice Smith");

    // Add users to the graph
    friendshipGraph.addUser(&user1);
    friendshipGraph.addUser(&user2);

    // Create and perform friendship actions
    Friendship friendshipRequest(&user1, &user2);
    friendshipRequest.addFriend(friendshipGraph);      // Send a friend request
    friendshipRequest.acceptFriendship();  // Accept the friendship request

    // Display friends for each user
    friendshipGraph.displayFriends(&user1);
    friendshipGraph.displayFriends(&user2);

    return 0;
}
