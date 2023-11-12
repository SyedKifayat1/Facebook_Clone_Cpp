#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

// Forward declaration of User and Content classes
class User;
class Content;

// Define a simple timestamp structure
struct Timestamp {
    int year, month, day, hour, minute, second;
};

// User class
class User {
private:
    static int nextUserID;
    int userID;

public:
    // Constructor
    User() : userID(nextUserID++) {}

    // Getter for User ID
    int getUserID() const {
        return userID;
    }
};

// Content class
class Content {
private:
    static int nextContentID;
    int contentID;

public:
    // Constructor
    Content() : contentID(nextContentID++) {}

    // Getter for Content ID
    int getContentID() const {
        return contentID;
    }
};

// Share class
class Share {
private:
    static int nextShareID;
    int shareID;
    const User* userID;
    const Content* sharedContentID;
    Timestamp timestamp;

public:
    // Constructor
    Share(const User* user, const Content* content)
        : shareID(nextShareID++), userID(user), sharedContentID(content) {
        // Get the current timestamp
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        struct tm* parts = std::localtime(&now_c);

        // Populate timestamp structure
        timestamp.year = 1900 + parts->tm_year;
        timestamp.month = 1 + parts->tm_mon;
        timestamp.day = parts->tm_mday;
        timestamp.hour = parts->tm_hour;
        timestamp.minute = parts->tm_min;
        timestamp.second = parts->tm_sec;
    }

    // Function to display share details
    void displayShare() const {
        std::cout << "Share ID: " << shareID << std::endl;
        std::cout << "User ID: " << userID->getUserID() << std::endl;
        std::cout << "Shared Content ID: " << sharedContentID->getContentID() << std::endl;
        std::cout << "Timestamp: " << timestamp.year << "-"
                  << timestamp.month << "-"
                  << timestamp.day << " "
                  << timestamp.hour << ":"
                  << timestamp.minute << ":"
                  << timestamp.second << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
};

// Initialize static variables
int Share::nextShareID = 1;
int User::nextUserID = 1;
int Content::nextContentID = 1;

int main() {
    // Create instances of User and Content
    User userA, userB;
    Content postContent;

    // User A shares the post content
    Share share(userA, &postContent);

    // Display share details
    share.displayShare();

    return 0;
}
