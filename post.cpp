#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>

// Forward declaration of User class (assuming it is defined elsewhere in the code)
class User;

// Comment class representing a comment on a post
class Comment {
private:
    User* author;
    std::string text;
    std::time_t timestamp;

public:
    Comment(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

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
};

// Post class representing a post on the platform
class Post {
private:
    User* author;
    std::string text;
    std::unordered_set<User*> likes;
    std::vector<Comment> comments;
    std::time_t timestamp;

public:
    // Constructor
    Post(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Function to add a like to the post by a specific user
    void addLike(User* user) {
        likes.insert(user);
        std::cout << user->getName() << " liked the post." << std::endl;
    }

    // Function to add a comment to the post
    void addComment(const Comment& comment) {
        comments.push_back(comment);
        std::cout << comment.getAuthor()->getName() << " commented: " << comment.getText() << std::endl;
    }

    // Function to edit the post content (only allowed for the author)
    void editPost(const std::string& newText) {
        if (author != nullptr) {
            text = newText;
            std::cout << "Post edited successfully by " << author->getName() << "." << std::endl;
        } else {
            std::cerr << "Error: Post author not specified." << std::endl;
        }
    }

    // Function to delete the post from the platform (only allowed for the author)
    void deletePost() {
        if (author != nullptr) {
            std::cout << "Post deleted successfully by " << author->getName() << "." << std::endl;
            // Additional logic for deleting the post from the platform
        } else {
            std::cerr << "Error: Post author not specified." << std::endl;
        }
    }

    // Getter for post text
    std::string getText() const {
        return text;
    }

    // Getter for post author
    User* getAuthor() const {
        return author;
    }

    // Getter for post timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort comments by timestamp (using insertion sort for simplicity)
    void sortCommentsByTimestamp() {
        std::sort(comments.begin(), comments.end(), [](const Comment& a, const Comment& b) {
            return a.getTimestamp() < b.getTimestamp();
        });
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
    // Create a user and a post
    User user1("John Doe");
    Post post1(&user1, "This is a sample post.");

    // Add a like to the post
    User user2("Alice Smith");
    post1.addLike(&user2);

    // Add a comment to the post
    Comment comment1(&user1, "Great post!");
    post1.addComment(comment1);

    // Edit the post (only allowed for the author)
    post1.editPost("Updated post content.");

    // Delete the post (only allowed for the author)
    post1.deletePost();

    // Sort comments by timestamp
    post1.sortCommentsByTimestamp();

    return 0;
}
