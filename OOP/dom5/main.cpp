
#include <iostream>
#include "Text.h"

int main() {
    const char* fileName = "test.txt";

    Text text(fileName);

    std::cout << "-- Hashtags is: " << std::endl;
    text.findHashtags();

    char* searchedWord = const_cast<char*>("#fmiLife");

    std::cout << "\n\n-- The message closest to \"#fmiLife\" is:" << std::endl;
    text.findMessage(searchedWord);

    std::cout << "\n\n-- Messages arranged by proximity to \"#fmiLife\":" << std::endl;
    text.sortMessages(searchedWord);

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Enter new message to add in text: " << std::endl;
    const char* message = "Male male napravih tez operatori #BOGSUM";
    std::cout << "Lets enter message for you :) Message is: " << message << std::endl;
    //std::cin >> message;

    Text text1 = text + message;
    std::cout << "First text don't have the message :/" << std::endl;
    text.listMessages();

    std::cout << "\n \nBut second text have it ;)" << std::endl;
    text1.listMessages();

    std::cout << "---------------------------------------------------" << std::endl;
    text += message;
    std::cout << "After operator+= already first text have message :)" << std::endl;
    text.listMessages();

    std::cout << "---------------------------------------------------" << std::endl;
    const char* searchedMessage = "male tez #BOGSUM";
    Message messageObj = text1[searchedMessage];
    std::cout << "Message content closed to our message is: " << messageObj.getContent() << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    return 0;
}