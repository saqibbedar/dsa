#include <iostream>
#include <string>
#include <forward_list>

struct UserSchema{
    std::string _id;
    std::string username;
    std::string email;
    std::string password;

    void display() const {
        std::cout << "_id: " << _id << std::endl
                  << "username: " << username << std::endl
                  << "email: " << email << std::endl
                  << "password: " << password;
    }
};

int main(){
    std::forward_list<UserSchema> users;
    
    UserSchema user;

    user._id = "id_is_unique";
    user.username = "saqibbedar";
    user.email = "hello@example.email";
    user.password = "password";

    users.push_front(user);

    std::forward_list<UserSchema>::iterator it;
    for (it = users.begin(); it != users.end(); ++it){
        it->display();
    }

    return 0;
}