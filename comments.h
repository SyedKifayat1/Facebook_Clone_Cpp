#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>

// Forward declaration of User class (assuming it is defined elsewhere in the code)
class User;

// Reply class representing a reply to a comment
class Reply {
private:
    User* author;
    std::string text;
    std::time_t timestamp;

public:
    Reply(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Getter for reply text
    std::string getText() const {
        return text;
    }

    // Getter for reply author
    User* getAuthor() const {
        return author;
    }

    // Getter for reply timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }
};

// Comment class representing a comment on a post
class Comment {
private:
    User* author;
    std::string text;
    std::unordered_set<Reply*> replies; // Efficient storage for unique replies
    std::time_t timestamp;

public:
    // Constructor
    Comment(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Destructor to free memory occupied by replies
    ~Comment() {
        for (auto reply : replies) {
            delete reply;
        }
    }

    // Function to add a reply to the comment
    void addReply(Reply* reply) {
        replies.insert(reply);
        std::cout << reply->getAuthor()->getName() << " replied: " << reply->getText() << std::endl;
    }

    // Function to edit the comment text (only allowed for the author)
    void editComment(const std::string& newText) {
        if (author != nullptr) {
            text = newText;
            std::cout << "Comment edited successfully by " << author->getName() << "." << std::endl;
        } else {
            std::cerr << "Error: Comment author not specified." << std::endl;
        }
    }

    // Function to delete the comment from the post (only allowed for the author)
    void deleteComment() {
        if (author != nullptr) {
            std::cout << "Comment deleted successfully by " << author->getName() << "." << std::endl;
            // Additional logic for deleting the comment from the post
        } else {
            std::cerr << "Error: Comment author not specified." << std::endl;
        }
    }

    // Getter for comment text
    std::string getText() const {
        return text;
    }

    // Getter for comment author
    User* getAuthor() const {
        return author;
    }

    // Getter for comment timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort replies by timestamp (using insertion sort for simplicity)
    void sortRepliesByTimestamp() {
        std::vector<Reply*> sortedReplies(replies.begin(), replies.end());
        std::sort(sortedReplies.begin(), sortedReplies.end(), [](const Reply* a, const Reply* b) {
            return a->getTimestamp() < b->getTimestamp();
        });

        // Output sorted replies
        for (auto sortedReply : sortedReplies) {
            std::cout << "Sorted Reply: " << sortedReply->getAuthor()->getName() << " - " << sortedReply->getText() << std::endl;
        }
    }
};

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
    // Create a user, a comment, and some replies
    User user1("John Doe");
    Comment comment1(&user1, "This is a sample comment.");

    User user2("Alice Smith");
    Reply reply1(&user2, "Thank you!");
    comment1.addReply(&reply1);

    User user3("Bob Johnson");
    Reply reply2(&user3, "Great discussion!");
    comment1.addReply(&reply2);

    // Edit the comment (only allowed for the author)
    comment1.editComment("Updated comment content.");

    // Delete the comment (only allowed for the author)
    comment1.deleteComment();

    // Sort replies by timestamp
    comment1.sortRepliesByTimestamp();

    return 0;
}
