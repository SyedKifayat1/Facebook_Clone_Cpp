#include <iostream>
#include <vector>
#include <ctime>

// Forward declaration of User class (assuming it is defined elsewhere in the code)
class User;

class Like {
private:
    User* user;
    std::string targetType;  // "post" or "comment"
    unsigned int targetID;   // ID of the liked post or comment
    std::time_t timestamp;

public:
    // Constructor
    Like(User* user, const std::string& targetType, unsigned int targetID)
        : user(user), targetType(targetType), targetID(targetID), timestamp(std::time(nullptr)) {}

    // Getter for the user who liked
    User* getUser() const {
        return user;
    }

    // Getter for the type of target ("post" or "comment")
    std::string getTargetType() const {
        return targetType;
    }

    // Getter for the ID of the liked post or comment
    unsigned int getTargetID() const {
        return targetID;
    }

    // Getter for the timestamp of the like
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to display information about the like
    void displayLikeInfo() const {
        std::cout << user->getName() << " liked a " << targetType << " with ID " << targetID
                  << " at " << std::asctime(std::localtime(&timestamp));
    }
};

// Function to display all likes in a vector
void displayAllLikes(const std::vector<Like>& likes) {
    for (const Like& like : likes) {
        like.displayLikeInfo();
        std::cout << std::endl;
    }
}

// Example User class (assuming it is defined elsewhere in the code)
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

// Example usage:
int main() {
    // Create users and likes
    User user1("John Doe");
    User user2("Alice Smith");

    std::vector<Like> likes;
    likes.emplace_back(&user1, "post", 123);
    likes.emplace_back(&user2, "comment", 456);

    // Display all likes
    displayAllLikes(likes);

    return 0;
}
