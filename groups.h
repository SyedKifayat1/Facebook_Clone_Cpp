#include <iostream>
#include <string>
#include <vector>

class User;

class Group {
private:
    std::string name;
    std::string description;
    std::vector<User*> members;
    std::vector<std::string> posts;

public:
    // Constructor
    Group(const std::string& name, const std::string& description)
        : name(name), description(description) {}

    // Function to add a member to the group
    void addMember(User* user) {
        members.push_back(user);
        std::cout << user->getName() << " has joined the group: " << name << std::endl;
    }

    // Function to remove a member from the group
    void removeMember(User* user) {
        auto it = std::find(members.begin(), members.end(), user);
        if (it != members.end()) {
            members.erase(it);
            std::cout << user->getName() << " has left the group: " << name << std::endl;
        }
    }

    // Function to create a post within the group
    void createPost(const std::string& text) {
        posts.push_back(text);
        std::cout << "New post created in group " << name << ": " << text << std::endl;
    }

    // Function to read (display) posts in the group
    void readPosts() const {
        std::cout << "Posts in group " << name << ":" << std::endl;
        for (const auto& post : posts) {
            std::cout << "  - " << post << std::endl;
        }
    }
};

class User {
private:
    std::string name;

public:
    // Constructor
    User(const std::string& name) : name(name) {}

    // Getter for user name
    std::string getName() const {
        return name;
    }
};

int main() {
    // Create users
    User user1("John Doe");
    User user2("Alice Smith");

    // Create a group
    Group group("Tech Enthusiasts", "A group for technology enthusiasts");

    // Add members to the group
    group.addMember(&user1);
    group.addMember(&user2);

    // Create posts within the group
    group.createPost("Excited about the latest tech conference!");
    group.createPost("Any recommendations for coding resources?");

    // Read and display posts in the group
    group.readPosts();

    // Remove a member from the group
    group.removeMember(&user1);

    return 0;
}
