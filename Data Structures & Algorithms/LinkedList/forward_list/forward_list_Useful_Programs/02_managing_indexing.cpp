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
    for (int i = 0; i < 3; ++i){
        user._id = "id_is_unique" + std::to_string(i+1);
        user.username = "johndoe" + std::to_string(i+1);
        user.email = "johndoe@example.email";
        user.password = "password" + std::to_string(i+1);
        users.push_front(user);
    }

    std::forward_list<UserSchema>::iterator it;
    for (it = users.begin(); it != users.end(); ++it){
        it->display();
        std::cout << std::endl <<std::endl;
    }

    // update record add index 2
    int index = 1;
    int currentIndex = 0;

    for (it = users.begin(); it != users.end(); ++it, ++currentIndex){
        if(currentIndex == index){
            it->_id = "id_is_unique";
            it->username = "saqibbedar";
            it->email = "saqibbedar@example.email";
            it->password = "password";
            break;
        }
    }

    std::cout << "\nUpdated Records: " << std::endl <<std::endl;

    for (it = users.begin(); it != users.end(); ++it){
        it->display();
        std::cout << std::endl <<std::endl;
    }

    return 0;
}
