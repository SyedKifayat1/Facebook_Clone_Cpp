// Data stuctures mini package to simulate the organization of users in facebook network
// Includes the implementation of various data stuctures including Graph, Trie, Queue and Stack

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "trie.h"
#include <fstream>
#include <Windows.h>
#include <algorithm>
using namespace std;

class TrieNode *rootOfTrie = getNode();

// doubly linked list of posts - specific to a user
class Post
{
public:
    string author;
    string content;
    int likes;
    Post *previousPost;
    Post *nextPost;
};

// every newsfeed is user-specific
// it is a stack of posts LIFO
// every time a user posts something, the newsfeeds of all his/her friends get the particular post added to their stack

class Feed
{
public:
    Post *post;
    Feed *next;
};

// queue of friend requests
class FriendRequest
{
public:
    string nameOfUser;
    int idOfUser;
    string username;
    FriendRequest *next;
};

// Graph
// every user is a node in the adjacency list
class User
{
public:
    User(string name, int userName, string email, string password, string dateOfBirth, User *next, Post *posts, FriendRequest *friendRequestsFront, FriendRequest *friendRequestsRear, Feed *feed, bool active)
    {
        this->name = name;
        this->user_id = userName;
        this->friendRequestsFront = friendRequestsFront;
        this->active = active;
        this->next = next;
        this->feed = feed;
        this->posts = posts;
    }

    User() {}
    string email, password, dateOfBirth;
    int user_id;
    string user_name;
    string name;
    User *next;                         // refer graph1
    Post *posts;                        // denotes the head of posts - points to the first post
    FriendRequest *friendRequestsFront; // points to the first friend request
    FriendRequest *friendRequestsRear;  // points to the last friend request
    Feed *feed;                         // stack of posts: newsfeed
    bool active;
};

class Graph
{
public:
    int V;
    User *users; // must be an array of adjacency lists, as the graph can be disconnected
};

typedef class Graph *GRAPHPTR;

//   - Pointer to the newly initialized User object representing the friend
class User *initializeFriend(int id, string name, string email, string password, string dateOfBirth)
{
    // Create a new User object representing the friend with provided details
    // Initialize other fields to NULL or default values as needed
    User *temp = new User(name, id, email, password, dateOfBirth, NULL, NULL, NULL, NULL, NULL, true);

    // Return the pointer to the newly initialized User object
    return temp;
}

//   - The index of the user in the graph if found, otherwise -1
int findIndex(GRAPHPTR graph, string userName)
{
    // Loop through the vertices in the graph
    for (int i = 0; i < graph->V; i++)
    {
        // Check if the username of the current user in the graph matches the provided username
        if (graph->users[i].name == userName)
        {
            // Return the index of the user if found
            return i;
        }
    }
    // Return -1 if the user is not found in the graph
    return -1;
}

// Function to add an edge between two users in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - user: The username of the first user
//   - destination_user: The username of the second user to form the edge with the first user
void addEdge(GRAPHPTR graph, string user, string destination_user)
{
    // Find the indices of the source and destination users in the graph
    int src = findIndex(graph, user);
    int destination = findIndex(graph, destination_user);

    // Append destination to the adjacency list of the source user
    User *destinationUser = initializeFriend(graph->users[destination].user_id, graph->users[destination].name, graph->users[destination].email, graph->users[destination].password, graph->users[destination].dateOfBirth);
    User *curUser = &graph->users[src];
    while (curUser->next != NULL)
    {
        curUser = curUser->next;
    }
    curUser->next = destinationUser;

    // Append the source to the adjacency list of the destination user
    destinationUser = initializeFriend(graph->users[src].user_id, graph->users[src].name, graph->users[destination].email, graph->users[destination].password, graph->users[destination].dateOfBirth);
    curUser = &graph->users[destination];
    while (curUser->next != NULL)
    {
        curUser = curUser->next;
    }
    curUser->next = destinationUser;
}

// Function to initialize a User object with default values
// Arguments:
//   - user: Pointer to the User object to be initialized
void initializeUser(class User *user)
{
    // Set default values for the User object attributes
    user->name = "";                  // Initialize name as an empty string
    user->next = NULL;                // Initialize the next pointer as NULL
    user->posts = NULL;               // Initialize posts as NULL
    user->friendRequestsFront = NULL; // Initialize friendRequestsFront as NULL
    user->friendRequestsRear = NULL;  // Initialize friendRequestsRear as NULL
    user->feed = NULL;                // Initialize feed as NULL
    user->active = false;             // Set active status to false
}

// Function to initialize a graph structure with a given number of vertices (users)
// Arguments:
//   - v: The number of vertices (users) in the graph
// Returns:
//   - Pointer to the initialized graph structure
GRAPHPTR initializeGraph(int v)
{
    // Create a new graph structure
    GRAPHPTR graph = new Graph;

    // Set the number of vertices (users) in the graph
    graph->V = v;

    // Allocate memory for 'v' User objects (vertices) in the graph
    graph->users = new User[v];

    // Initialize each User object in the graph
    for (int i = 0; i < v; i++)
    {
        // Set the user_id for each User object
        graph->users[i].user_id = i;

        // Initialize the User object using the initializeUser function
        initializeUser(&graph->users[i]);
    }

    // Return the pointer to the initialized graph structure
    return graph;
}

// Function to add a new user to the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - name: The name of the new user
//   - password: The password associated with the new user's account
void addUser(GRAPHPTR graph, string name, string password)
{
    // Convert the name to lowercase for uniformity
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    int i;
    // Iterate through the vertices (users) in the graph
    for (i = 0; i < graph->V; i++)
    {
        // Check for an inactive (non-active) user
        if (graph->users[i].active == false)
        {
            // Assign the name, password, and set the user as active
            graph->users[i].name = name;
            graph->users[i].password = password;
            graph->users[i].active = true;
            break; // Exit the loop after adding the user
        }
    }

    // Call the 'insert' function to insert the user's name into a Trie data structure
    insert(rootOfTrie, name);
}

// Function to display all active users in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
void displayAllUsersInTheSystem(GRAPHPTR graph)
{
    // Display a header indicating that the following list contains all users in the system
    cout << "All the users in the system: \n";

    // Iterate through the vertices (users) in the graph
    for (int i = 0; i < graph->V; i++)
    {
        // Check if the user is active
        if (graph->users[i].active)
        {
            // Display the user's ID and name if they are active
            cout << graph->users[i].user_id << " : " << graph->users[i].name << endl;
        }
    }
}

// Function to display a particular user's information and prompt for user ID selection
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - name: The name of the user to be displayed
// Returns:
//   - The user ID selected by the user
int displayParticularUser(GRAPHPTR graph, string name)
{
    // Display users with the provided name in the system
    for (int i = 0; i < graph->V; i++)
    {
        if (graph->users[i].name == name)
        {
            cout << graph->users[i].user_id << " : " << name << endl;
        }
    }

    int id;
    // Prompt the user to enter the ID of the required person
    cout << "Enter the ID of the required person: \n";
    cin >> id;

    return id; // Return the selected user ID
}

// Function to get a FriendRequest object
// Returns:
//   - Pointer to a newly created FriendRequest object
class FriendRequest *getFriendRequest()
{
    // Create a new FriendRequest object
    FriendRequest *fr = new FriendRequest;

    // Set the 'next' pointer to NULL for initialization
    fr->next = NULL;

    // Return the pointer to the newly created FriendRequest object
    return fr;
}

// Function to enqueue a friend request for a user in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - sourceUserID: The user ID of the sender of the friend request
//   - destinationUserID: The user ID of the recipient of the friend request
void enqueueFriendRequest(GRAPHPTR graph, int sourceUserID, int destinationUserID)
{
    // Create a new FriendRequest object and initialize its attributes
    FriendRequest *temp = getFriendRequest();
    temp->idOfUser = sourceUserID;
    temp->nameOfUser = graph->users[sourceUserID].name;

    // Enqueue the friend request for the destination user
    if (graph->users[destinationUserID].friendRequestsRear == NULL)
    {
        // If the destination user's friendRequestsRear is NULL, indicating an empty queue
        // Set both front and rear to the new FriendRequest object
        graph->users[destinationUserID].friendRequestsRear = graph->users[destinationUserID].friendRequestsFront = temp;
    }
    else
    {
        // If the destination user's friendRequestsRear is not NULL
        // Append the new FriendRequest object to the rear of the queue
        graph->users[destinationUserID].friendRequestsRear->next = temp;
        graph->users[destinationUserID].friendRequestsRear = temp;
    }
}

// Function to dequeue a friend request for a user in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - ID: The user ID for whom the friend request needs to be dequeued
void dequeueFriendRequest(GRAPHPTR graph, int ID)
{
    FriendRequest *front1 = graph->users[ID].friendRequestsFront;

    // If the queue has only one element
    if (front1->next == NULL)
    {
        free(graph->users[ID].friendRequestsFront);                                        // Free the memory of the front node
        graph->users[ID].friendRequestsFront = graph->users[ID].friendRequestsRear = NULL; // Reset front and rear to NULL
    }
    else
    {
        front1 = front1->next;                         // Move front1 to the next node
        free(graph->users[ID].friendRequestsFront);    // Free the memory of the original front node
        graph->users[ID].friendRequestsFront = front1; // Update the front pointer to the next node
    }
}

// Function to delete a friend request entry from a file
// Arguments:
//   - user: The user associated with the friend request
//   - requester: The user who sent the friend request
void deleteFriendRequestFromFile(string user, string requester)
{
    // Open the input and temporary files for reading and writing, respectively
    ifstream inputFile("FriendRequests.txt");
    ofstream tempFile("temp.txt");

    // Check if files were opened successfully
    if (!inputFile.is_open() || !tempFile.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    string user_f, requester_f;
    bool contentDeleted = false;

    // Read and process the content from the input file
    while (getline(inputFile, user_f, ':'))
    {
        getline(inputFile, requester_f, '\n');

        // Check if the content matches the request to delete
        if (user_f != user && requester_f != requester)
        {
            tempFile << user_f << ":" << requester_f << endl; // Write non-matching content to the temporary file
        }
        else
        {
            contentDeleted = true; // Mark content deletion
        }
    }

    inputFile.close(); // Close input file
    tempFile.close();  // Close temporary file

    // If content was deleted, update the original file
    if (contentDeleted)
    {
        // Remove the original file and rename the temporary file
        if (remove("FriendRequests.txt") != 0)
        {
            cout << "Error deleting original file." << endl;
            return;
        }
        if (rename("temp.txt", "FriendRequests.txt") != 0)
        {
            cout << "Error renaming temporary file." << endl;
            return;
        }
    }
    else
    {
        cout << "Content to delete not found in the file." << endl;
        remove("temp.txt"); // Remove the temporary file if no deletion occurred
    }
}

// Function to display and process pending friend requests for a user in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - ID: The user ID for whom pending friend requests need to be displayed
void displayFriendRequests(GRAPHPTR graph, int ID)
{
    FriendRequest *front1 = graph->users[ID].friendRequestsFront;
    FriendRequest *rear1 = graph->users[ID].friendRequestsRear;

    // Check if there are no pending friend requests for the user
    if (!front1 && !rear1)
    {
        cout << "No pending friend requests!" << endl;
        return;
    }

    // Process each pending friend request
    while (true)
    {
        cout << "Friend request received from:\n";
        cout << "User Name: " << front1->nameOfUser << endl;

        char choice;
        cout << "To accept friend request, enter 'y'; to reject it, enter 'n':\n\n";
        cin >> choice;

        if (choice == 'y')
        {
            // Accept the friend request and add an edge between the users in the graph
            addEdge(graph, graph->users[ID].name, front1->nameOfUser);

            // Add friends to the file
            ofstream file("friends.txt", ios::app);
            if (!file.is_open())
            {
                cout << "\nError: Failed to open file for writing!\n";
            }
            else
            {
                file << graph->users[ID].name << ":" << front1->nameOfUser << endl;
            }
            file.close();
        }

        // Delete the friend request entry from the file
        deleteFriendRequestFromFile(front1->nameOfUser, graph->users[ID].name);

        // Remove the processed friend request from the queue
        if (front1 == rear1)
        {
            dequeueFriendRequest(graph, ID);
            break;
        }

        front1 = front1->next;
        dequeueFriendRequest(graph, ID);

        if (front1 == NULL)
        {
            break;
        }
    }
}

// Function to send a friend request from a user to another user in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - senderName: The name of the user sending the friend request
//   - reciverName: The name of the user who will receive the friend request
void sendFriendRequest(GRAPHPTR graph, string senderName, string reciverName)
{
    string be_a_friend;
    int ID = findIndex(graph, senderName); // Get the ID of the sender in the graph
    cout << "\nId :" << ID << endl;
    User *user = &graph->users[ID];
    be_a_friend = reciverName;

    // If receiver name is not provided, prompt user to input the receiver's name
    if (reciverName == "")
    {
        cin.ignore();
        cout << "\nUser Name of the person whom you want to befriend: ";
        getline(cin, be_a_friend);
    }
    // cout<<"\nReciver :"<<be_a_friend<<endl;
    // Get the ID of the destination user (receiver) in the graph
    int destinationUserID = findIndex(graph, be_a_friend);

    // Check if the destination user exists in the graph
    if (destinationUserID > graph->V || destinationUserID < 0)
    {
        cout << "\nYour friend is not found!\n";
        return;
    }

    // If receiver name is not provided, store the friend request in a file
    if (reciverName == "")
    {
        ofstream file("FriendRequests.txt", ios::app);
        if (!file.is_open())
        {
            cout << "\nError: Failed To Open File For Writing!\n";
        }
        else
        {
            file << user->name << ":" << be_a_friend << endl; // Store the friend request in the file
        }
        file.close();
    }

    // Enqueue the friend request in the receiver's queue
    enqueueFriendRequest(graph, ID, destinationUserID);

    // If receiver name is not provided, display a confirmation message
    if (reciverName == "")
    {
        cout << "Friend request sent to " << be_a_friend << endl;
    }
}

// Function to push a post into a user's feed stack
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - ID: The user ID where the post will be added to the feed
//   - srcPost: Pointer to the post to be added
void pushIntoFeedStack(GRAPHPTR graph, int ID, Post *srcPost)
{
    // If the user's feed is empty
    if (graph->users[ID].feed == NULL)
    {
        // Create a new feed node and add the post
        graph->users[ID].feed = new Feed;
        graph->users[ID].feed->post = srcPost;
        graph->users[ID].feed->next = NULL;
    }
    else
    {
        // Create a new feed node, assign the post, and link it to the existing feed
        Feed *tempFeed = new Feed;
        tempFeed->post = srcPost;
        tempFeed->next = graph->users[ID].feed; // Point the new node to the current feed
        graph->users[ID].feed = tempFeed;       // Update the feed pointer to the new node
    }
}

// Function to remove the top post from a user's feed stack
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - ID: The user ID from whose feed the post will be removed
void popFromFeedStack(GRAPHPTR graph, int ID)
{
    // Store the reference to the top of the feed to be deleted
    Feed *feedToBeDeleted = graph->users[ID].feed;

    // Move the feed pointer to the next node (removing the top post)
    graph->users[ID].feed = graph->users[ID].feed->next;

    // Delete the feed node that was at the top of the feed
    delete feedToBeDeleted;
}

// Function to add a post to a user's profile and update feeds of their friends
// Arguments:
//   - graph: Pointer to the graph structure containing user information
//   - user: Pointer to the user who is adding the post
//   - content: The content of the post
//   - likes: The number of likes for the post
void addPost(GRAPHPTR graph, User *user, string content, int likes)
{
    // Create a new post
    Post *post = new Post;
    post->previousPost = post->nextPost = NULL;
    post->author = user->name;

    // If content is not provided, prompt the user to enter the content
    if (content == "")
    {
        cout << "Enter the content: ";
        cin.ignore();
        getline(cin, post->content);
    }
    else
    {
        post->content = content;
    }
    post->likes = likes;

    // Add the post to the user's posts

    // If the user has no posts yet
    if (user->posts == NULL)
    {
        user->posts = post;
    }
    else
    {
        // Traverse the user's posts to find the last post
        Post *temp = user->posts;
        while (temp->nextPost != NULL)
        {
            temp = temp->nextPost;
        }

        // Add the new post to the end of the user's posts
        temp->nextPost = post;
        post->previousPost = temp;

        // If content is not provided, store the post in a file
        if (content == "")
        {
            ofstream file("addPost.txt", ios::app);
            if (!file.is_open())
            {
                cout << "\nError: Failed To Open File For Writing!\n";
            }
            else
            {
                file << post->author << ":" << post->content << "," << post->likes << endl;
            }
            file.close();
        }

        // Update feeds of friends in the graph
        User *friendOfUser = user->next;
        while (friendOfUser != NULL)
        {
            // Push the post into the feed of each friend
            pushIntoFeedStack(graph, friendOfUser->user_id, post);
            friendOfUser = friendOfUser->next;
        }
    }
}

// Function to view and navigate through a user's posts
// Allows deletion of posts if the user chooses
// Arguments:
//   - user: Pointer to the user whose posts are being viewed
void viewPosts(User *user)
{
    Post *curPost = user->posts;

    // Loop to navigate through the posts
    while (true)
    {
        // If no posts or end of posts, return
        if (curPost == NULL)
        {
            return;
        }

        // Display post content and likes
        cout << "\t" << curPost->content << "\n\tLikes : " << curPost->likes << endl;
        cout << "Enter 'd' to delete this post, 'n' to move to the next post, 'p' for the previous post, or 'x' to exit\n";

        string temp;
        cin >> temp;

        // Delete the current post if chosen
        if (temp == "d")
        {
            if (curPost->previousPost != NULL)
            {
                Post *temp = curPost;
                curPost->previousPost->nextPost = curPost->nextPost;
                curPost = curPost->nextPost;
                delete temp;
            }
            else
            {
                // If the current post is the first post
                user->posts = curPost->nextPost;
                delete curPost;
                curPost = user->posts;
            }
        }

        // Move to the previous post if chosen
        if (temp == "p" && curPost->previousPost)
        {
            curPost = curPost->previousPost;
        }

        // Move to the next post if chosen
        if (temp == "n" && curPost->nextPost)
        {
            curPost = curPost->nextPost;
        }

        // Exit if chosen
        if (temp == "x")
        {
            return;
        }
    }
}

// Function to view and interact with the user's feed
// Arguments:
//   - graph: Pointer to the graph structure containing user feeds
//   - ID: ID of the user whose feed is being viewed
void viewFeed(GRAPHPTR graph, int ID)
{
    Feed *currentFeed = graph->users[ID].feed; // Top of the feed stack for the user

    // If no posts in the feed
    if (currentFeed == NULL)
    {
        cout << "There are no posts in your feed now!\nPlease come back later!\n";
        return;
    }

    // Loop to display and interact with posts in the feed
    while (currentFeed != NULL)
    {
        cout << "\tPost Author :" << currentFeed->post->author << " : \n";
        cout << "\t\tPosted Content :" << currentFeed->post->content << endl;
        cout << "\t\tLikes : " << currentFeed->post->likes << endl
             << endl;

        // Prompt user for actions: Like, Move to the next post, or Stop viewing the feed
        cout << "Enter 'l' to like the post, 'n' to move to the next post, or 'x' to stop viewing the feed\n";
        string c;
        cin >> c;

        // Perform actions based on user input
        if (c == "l")
        {
            currentFeed->post->likes++;      // Increment likes for the post
            currentFeed = currentFeed->next; // Move to the next post
        }
        else if (c == "x")
        {
            popFromFeedStack(graph, ID); // Remove the viewed feed from the stack
            return;
        }
        else if (c == "n")
        {
            currentFeed = currentFeed->next; // Move to the next post
        }

        // If the end of feed is reached
        if (currentFeed == NULL)
        {
            return;
        }
    }

    // If all posts have been shown
    cout << "All the posts have been shown!\n";
}

// Function to display a user's friends
// Argument:
//   - user: Pointer to the user whose friends are to be displayed
void viewFriends(User *user)
{
    User *curFriend = user->next;

    // Loop through the user's friends and display their names
    while (curFriend)
    {
        cout << curFriend->name << "\n";
        curFriend = curFriend->next;
    }
}

// Function to suggest friends based on mutual connections
// Arguments:
//   - graph: Pointer to the graph structure containing user connections
//   - ID: ID of the user for whom friend suggestions are made
void friendSuggestions(GRAPHPTR graph, int ID)
{
    unordered_map<int, int> umap;
    User *user = &graph->users[ID];

    // Storing the immediate friends of the user in a map
    User *friendOfUser = user->next;
    while (friendOfUser)
    {
        umap.insert(make_pair(friendOfUser->user_id, 0));
        friendOfUser = friendOfUser->next;
    }

    // Calculating mutual friends
    friendOfUser = user->next;
    while (friendOfUser)
    {
        User *searchUser = &graph->users[friendOfUser->user_id];
        User *friendOfSearchUser = searchUser->next;

        while (friendOfSearchUser)
        {
            if (umap.find(friendOfSearchUser->user_id) != umap.end())
            {
                umap[friendOfSearchUser->user_id]++;
            }
            friendOfSearchUser = friendOfSearchUser->next;
        }
        friendOfUser = friendOfUser->next;
    }

    // Display friend suggestions with mutual friends >= 2
    cout << "Friend suggestions, filtered with no. of mutual friends greater than or equal to 2:\n";
    for (auto i = umap.begin(); i != umap.end(); i++)
    {
        if (i->second >= 2)
        {
            cout << i->first << " : " << graph->users[i->first].name << endl;
        }
    }
}

// Function to check if a user exists in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user data
//   - userName: Name of the user to be checked for existence
// Returns:
//   - true if the user exists, false otherwise
bool isUserExists(GRAPHPTR graph, string userName)
{
    // Loop through all users in the graph
    for (int i = 0; i < graph->V; i++)
    {
        // Check if the current user's name matches the specified userName
        if (graph->users[i].name == userName)
        {
            // User found, return true
            return true;
        }
    }
    // User not found, return false
    return false;
}

// createAccount(GRAPHPTR graph, string Name, string email, string password, string dateOfBirth, string userName)

// Function to create a new user account in the graph
// Arguments:
//   - graph: Pointer to the graph structure containing user data
//   - Name: Username for the new account
//   - password: Password for the new account
void createAccount(GRAPHPTR graph, string Name, string password)
{
    // Check if the user already exists in the graph
    if (isUserExists(graph, Name))
    {
        cout << "User already exists with username: " << Name << endl;
    }
    else
    {
        // Open file for writing user information
        ofstream file("names.txt", ios::app);
        if (!file.is_open())
        {
            cout << "\nError :Failed To Open File For Writing!\n";
        }
        else
        {
            // Write user information (username:password) to the file
            file << Name << ":" << password << endl;
        }
        file.close();

        // Add the user to the graph
        addUser(graph, Name, password);
        cout << "User added successfully!" << endl;
    }
}

// Function to authenticate user login
// Arguments:
//   - graph: Pointer to the graph structure containing user data
//   - userName: Username entered during login
//   - pass: Password entered during login
// Returns:
//   - true if login credentials are valid, false otherwise
bool loginAccount(GRAPHPTR graph, string userName, string pass)
{
    // Iterate through all users in the graph
    for (int i = 0; i < graph->V; i++)
    {
        // Check if the username matches
        if (graph->users[i].name == userName)
        {
            // If the username matches, check if the password matches
            if (graph->users[i].password == pass)
            {
                // Return true if both username and password match
                return true;
            }
        }
    }

    // Return false if the username or password doesn't match
    return false;
}

// Function to manage user actions after successful login
// Arguments:
//   - graph: Pointer to the graph structure containing user data
//   - userName: Username of the logged-in user
void afterLogin(GRAPHPTR graph, string userName)
{
    // Find the ID/index of the logged-in user
    int id = findIndex(graph, userName);
    int flag = 0;
    User *currentUser = &graph->users[id];
    int choice;

    // Loop for user interaction options
    while (flag == 0)
    {
        system("clear");
        // Display menu options
        cout << "\n\t\t\t----------- Welcome to Facebook " << currentUser->name << " ----------- \n1).View your feed\n2).Post\n3).View your posts\n4).View all your friend requests\n5).View all your friends\n6).Send friend requests\n7).View suggested friends\n0).Exit\nEnter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("clear");
            viewFeed(graph, id); // Display user's feed
            break;
        }
        case 2:
        {
            system("clear");
            addPost(graph, currentUser, "", 0); // Add a post
            break;
        }
        case 3:
        {
            system("clear");
            viewPosts(currentUser); // View user's posts
            break;
        }
        case 4:
        {
            system("clear");
            displayFriendRequests(graph, id); // View friend requests
            break;
        }
        case 5:
        {
            system("clear");
            viewFriends(currentUser); // View user's friends
            break;
        }
        case 6:
        {
            system("clear");
            sendFriendRequest(graph, currentUser->name, ""); // Send friend requests
            break;
        }
        case 7:
        {
            system("clear");
            friendSuggestions(graph, id); // View friend suggestions
            break;
        }
        case 0:
        {
            cout << "Thank you !\n";
            flag = 1; // Exit the loop and function
            break;
        }
        default:
        {
            cout << "Invalid choice\n"; // Handle invalid inputs
        }
        }
        cout << "\nPress Enter to continue....\n";
        getchar();
        getchar();
    }
}

// Function to manage the main login/signup page for Facebook
// Arguments:
//   - graph: Pointer to the graph structure containing user data
void main_facebook_login_page(GRAPHPTR graph)
{
    int Check = 0;
    while (Check == 0)
    {
        system("clear");

        // Display the Facebook logo and login/signup options
        cout << "\n\t\t\t\t\tFacebook\n";
        cout << "\n\t\t----------Welcome to SignUp/SignIn Page----------\n\n1).SignUp\n2).SignIn\n0).Exit  \nYour Choice:";
        int Choice;
        cin >> Choice;
        switch (Choice)
        {
        case 1:
        {
            system("clear");
            cout << "\n\t\t----------Welcome to SignUp Page----------\n\n";
            string name, pass;
            cout << "Enter Name:";
            cin >> name;
            cout << "\nEnter Password:";
            cin >> pass;
            createAccount(graph, name, pass); // Create a new account
            break;
        }
        case 2:
        {
            system("clear");
            cout << "\n\t\t----------Welcome to SignIn Page----------\n";
            string userName, pass;
            cin.ignore();
            cout << "\nEnter Your User Name: ";
            getline(cin, userName);
            transform(userName.begin(), userName.end(), userName.begin(), ::tolower); // Convert username to lowercase

            cout << "\nEnter Your Password: ";
            getline(cin, pass);
            transform(pass.begin(), pass.end(), pass.begin(), ::tolower); // Convert password to lowercase

            bool check = loginAccount(graph, userName, pass); // Check login credentials
            if (check == true)
            {
                afterLogin(graph, userName); // Perform actions after successful login
            }
            else
            {
                cout << "\nInvalid login!\n"; // Handle invalid login
            }
            break;
        }
        case 0:
        {
            Check = 1;
            cout << "\n--------------Good Bye---------------\n\n";
            break;
        }
        default:
        {
            cout << "\nInvalid Choice!\n"; // Handle invalid inputs
        }
        }
        cout << "\nPress Enter to continue....\n";
        getchar();
        getchar();
    }
}

// The main function serves as the entry point to the program
int main()
{
    // Initialize console attributes
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Get current console attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Change the background color of the console
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_BLUE);

    // Open files to read user data and relationships
    fstream file("names.txt", ios::in);
    fstream file_p("addPost.txt", ios::in);
    fstream file_R("FriendRequests.txt", ios::in);
    fstream file_F("friends.txt", ios::in);

    // Initialize the user graph
    GRAPHPTR graph = initializeGraph(50);

    // Read user data and populate the user graph
    string tempName, password;
    while (getline(file, tempName, ':'))
    {
        getline(file, password, '\n');
        addUser(graph, tempName, password);
    }
    file.close();

    // Read post data and add posts to respective users
    string userName, content;
    string likes;
    while (getline(file_p, userName, ':'))
    {
        getline(file_p, content, ',');
        getline(file_p, likes, '\n');
        int num = stoi(likes);
        int index = findIndex(graph, userName);
        addPost(graph, &graph->users[index], content, num);
    }
    file_p.close();

    string user_name, requesterName;

    // Establish friendships between users
    while (getline(file_F, user_name, ':'))
    {
        getline(file_F, requesterName, '\n');
        addEdge(graph, user_name, requesterName);
    }

    file_F.close();

    // Handle friend requests
    while (getline(file_R, requesterName, ':'))
    {
        requesterName.erase(std::remove_if(requesterName.begin(), requesterName.end(), ::isspace), requesterName.end());
        getline(file_R, user_name, '\n');
        user_name.erase(std::remove_if(user_name.begin(), user_name.end(), ::isspace), user_name.end());

        sendFriendRequest(graph, requesterName, user_name);
    }
    file_R.close();

    // Start the main Facebook login page
    main_facebook_login_page(graph);

    // Restore original console attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Return 0 to indicate successful completion of the program
    return 0;
}

