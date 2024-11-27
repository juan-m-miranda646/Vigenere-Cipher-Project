#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

// Team: One
// Member(s): Juan Miranda
// Class: CIS 7
// Case 3 - Vigenère cipher 
// *** PROGRAM COMMENTS ***
// This program lets the user save and select keys from a a file.
// Then using that selected key, the user has the option to type plaintext
// to encrypt it or type a ciphertext to decrpt it.
// *** IMPORTANT ***
// To make sure that the saving a cipher key works, make sure that the next
// element in the file is already in place.
// *** EXAMPLE *** This is how it should look in the file section
// 1    EARN
// 2    SECRET
// 3    (this should be empty for the next key to be save)

// class key to manage all the data in the cipher key file
class Key {
private:
    // fstream data type in private to make sure that nothing else other than
    // this class itself can access this data type
    fstream keyData;
public:
    // string vector to store the keys in the file into the vector string
    vector <string> keysArray;

    // Constructor
    Key() {}

    // Destructor --> destroys the object
    ~Key()
    {
        // If the file is open, close the file before destroying the object
        if (keyData.is_open())
        {
            keyData.close();
        }
    }

    // Function to open the file from outside the class
    // sets a boolean variable to true/false depending
    // of the state of the file
    void OpenFileOutside(const string& fileName, bool& isFileOpen)
    {
        keyData.open(fileName, ios::in); // open file for reading

        // Error message if the file is not opened
        if (!keyData.is_open())
        {
            isFileOpen = false;
        }
        else
        {
            isFileOpen = true;
        }
    }

    // Function to open the file from within the class
    // receives a boolean variable to detertmine how to open the file
    // open for reading only or open for writing and appending
    void OpenFile(const string& fileName, bool& isFileReading)
    {
        if (isFileReading == true)
        {
            keyData.open(fileName, ios::in); // open file for reading
        }
        else
        {
            keyData.open(fileName, ios::out | ios::app); // open file for and writing and appending
        }
    }

    // Function to close the file
    void CloseFile()
    {
        keyData.close();
    }

    // Function to read the data from the file and store its elements inside a vector string 
    void ReadKeys(const string& fileName, int& index)
    {
        // function variables
        string keyInLine;
        int countKeys = 0;
        bool isFileReading = true;

        // open file
        OpenFile(fileName, isFileReading);


        // Reset the file to the beginnig to use again
        keyData.clear(); // Clear error flag when reaching the end of a file
        keyData.seekg(0, ios::beg); // return file to its first element

        // Clear error flag when reaching the end of a file
        // this will be effective when the key menu runs again after adding a new key.
        // Makes it possible to display the new key list.
        if (!keysArray.empty())
        {
            keysArray.clear();
        }

        // Display for showing the keys in the file
        cout << endl << "This are the keys stored in the file:\n";

        // while loop to read the keys inside the file and display them
        // as well as to store the elements in the file and store them in a vector string.
        // The loop will start at the start of the file and will run until
        // it reaches the last element in the file
        while (getline(keyData, keyInLine)) // getline to get the string from the file and put it in a string
        {
            // using the string keyInLine, send that string to the vctor string KeysArray
            keysArray.push_back(keyInLine);
            // Display the key being read at the time of the iteration
            cout << (countKeys + 1) << " --> " << keysArray[countKeys] << endl;
            // Count for keys that is used for the index in the vector string
            countKeys++;
        }

        // Close file
        CloseFile();
        // Reset the count of keys to 0 for the next time this function runs
        countKeys = 0;
    }

    // Function to get a key
    string GetKey(int& keyNumber)
    {
        // Return the key the user selected
        // This will use the vector string and the index that the user has selected
        return keysArray[keyNumber];
    }

    // Function to save a new key
    void SaveKey(const string& fileName, string& newKey)
    {
        // variables
        bool isFileReading = false; // set the boolean to false

        // open file for writing and appending because the boolean is set to false
        OpenFile(fileName, isFileReading);

        // Clear error flag when reaching the end of a file
        keyData.clear();

        // Add the new key into the file
        keyData << newKey << endl;

        // close file
        CloseFile();
    }

};

// Function to check for correct numbers within a range
bool isValidNum(int num, int min, int max)
{
    // function variables
    int choiceValue = num;
    int minRange = min;
    int maxRange = max;
    bool inputIsValid;

    // if stament to evaluate for true or false
    if (choiceValue >= minRange && choiceValue <= maxRange)
    {
        inputIsValid = true;
    }
    else
    {
        inputIsValid = false;
    }

    return inputIsValid;
}


// Function to check for two correct characters
bool isValidChar(char playAgain)
{
    // function variables
    char againYes = 'Y';
    char againNo = 'N';
    bool inputIsValid;

    // if stament to evaluate for true or false
    if (playAgain == againYes || playAgain == againNo)
    {
        inputIsValid = true;
    }
    else
    {
        inputIsValid = false;
    }

    return inputIsValid;
}

// Function to display menu options
int mainMenuDisplay(Key& keysData, const string& fileName, int& index)
{
    // function variables
    int choice;
    int minChoice = 1;
    int maxChoice = 4;
    bool isInputValid;

    // Menu Display
    keysData.ReadKeys(fileName, index); // Display the keys that are in the file
    cout << endl << "Pick an option for the Key file.\n";
    cout << "1. Select a key.\n";
    cout << "2. Save a new key.\n";
    cout << "3. Go to Vigenere Cipher menu.\n";
    cout << "4: Quit the program\n";

    // Ask the user to input the selection for the option in the menu
    cout << "Select the number for the option that you want: ";
    cin >> choice;

    // while loop to ask again if the user selects something else outside the available options (1 through 4)
    while (!isValidNum(choice, minChoice, maxChoice))
    {
        // Menu Display
        cout << endl << "Sorry, Invalid Input. Please try again.\n";
        keysData.ReadKeys(fileName, index); // Display the keys that are in the file
        cout << endl << "Pick an option for the Key file.\n";
        cout << "1. Select a key.\n";
        cout << "2. Save a new key.\n";
        cout << "3. Go to Vigenere Cipher menu.\n";
        cout << "4: Quit the program\n";

        // Aks the user to input the selection for the option in the menu
        cout << "Select the number for the option that you want: ";
        cin >> choice;
    }

    return choice;
}

// Function to encrypt the plaintext
string vigenereEncrypt(string plaintext, string& key)
{
    // function variables
    string encryptedText = "";
    int keyIndex = 0;
    int keyLength = key.length();

    // Set the plaintext and key to uppercase
    // Makes it easier to encrypt text
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), toupper);
    transform(key.begin(), key.end(), key.begin(), toupper);

    // For loop to read each individual character in the plaintext
    for (int i = 0; i < plaintext.length(); i++)
    {
        // check if the character is a letter
        // if so, encrypt the character using the vigenere equation for encryption
        // Ei = ((Pi MOD 26) + (Ki MOD 26)) MOD 26
        if (isalpha(plaintext[i]))
        {
            encryptedText += char(((plaintext[i] % 26) + (key[keyIndex % keyLength] % 26)) % 26 + 65);
        }
        // Avoid encrypting non-letters
        else
        {
            encryptedText += plaintext[i];
        }

        // Index increases to read the following character in the key for the next loop
        keyIndex++;
    }

    return encryptedText;
}

// Function to decrypt the ciphertext
string vigenereDecrypt(string ciphertext, string& key)
{
    // function variables
    string decryptedText = "";
    int keyIndex = 0;
    int keyLength = key.length();

    // Set the ciphertext and key to uppercase
    // Makes it easier to decrypt text
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), toupper);
    transform(key.begin(), key.end(), key.begin(), toupper);

    // For loop to read each individual character in the ciphertext
    for (int i = 0; i < ciphertext.length(); i++)
    {
        // check if the character is a letter
        // if so, decrypt the character using the vigenere equation for decryption
        // Di = ((Ei MOD 26) - (Ki MOD 26) + (26)) MOD 26
        if (isalpha(ciphertext[i]))
        {
            decryptedText += char(((ciphertext[i] - 'A') - (key[keyIndex % keyLength] - 'A') + 26) % 26 + 'A');
        }
        // Avoid decrypting non-letters
        else
        {
            decryptedText += ciphertext[i];
        }

        // Index increases to read the following character in the key for the next loop
        keyIndex++;
    }

    return decryptedText;
}


// Function to display menu options
int VigenereCipherMenu()
{
    // function variables
    int choice;
    int minChoice = 1;
    int maxChoice = 2;
    bool isInputValid;

    // Menu display
    cout << endl << "Pick an option for the cipher option.\n";
    cout << "1. Encrypt plaintext.\n";
    cout << "2. Decrypt ciphertext.\n";

    // Ask the user to input the selection for the option in the menu
    cout << "Select the number for the option that you want: ";
    cin >> choice;

    // while loop to ask again if the user selects something else outside the available options (1 and 2)
    while (!isValidNum(choice, minChoice, maxChoice))
    {
        // Menu display
        cout << endl << "Sorry, Invalid Input. Please try again.\n";
        cout << endl << "Pick an option for the cipher option.\n";
        cout << "1. Encrypt plaintext.\n";
        cout << "2. Decrypt ciphertext.\n";

        // Ask the user to input the selection for the option in the menu
        cout << "Select the number for the option that you want: ";
        cin >> choice;
    }

    return choice;
}

void VigenereCipherSection(string& key)
{
    // Cipher menu constants
    int const OPTION_ENCRYPT = 1;
    int const OPTION_DECRYPT = 2;

    // function variables
    int cipherChoice;
    char runAgain;
    string ciphertext = "";
    string plaintext = "";
    string encryptedText;
    string decryptedText;

    // do while loop to always ask the user about the menu options until quitting
    do
    {
        // call the menu display and ask for the user's choice
        cipherChoice = VigenereCipherMenu();

        // Switch statement to select between different options in the menu
        switch (cipherChoice)
        {
            // Encrypt plaintext
        case 1:
            // ask user for the plaintext
            cin.ignore();
            cout << endl << "Enter the plaintext that you want to Encrypt:\n";
            getline(cin, plaintext);

            // convert plaintext to encrypted text
            encryptedText = vigenereEncrypt(plaintext, key);

            // Input the results of the encryption
            cout << endl << "Using the key: " << key << "; the plaintext: " << plaintext << endl;
            cout << "Encrypts to: " << encryptedText << endl;
            break;

            // Decrypt ciphertext
        case 2:
            // ask user for the ciphertext
            cin.ignore();
            cout << endl << "Enter the ciphertext that you want to Decrypt:\n";
            getline(cin, ciphertext);

            // convert ciphertext to decrypted text
            decryptedText = vigenereDecrypt(ciphertext, key);

            // Input the results of the decryption
            cout << endl << "Using the key: " << key << "; the ciphertext: " << ciphertext << endl;
            cout << "Decrypts to: " << decryptedText << endl;
            break;

            // Invalid choice (to catch errors)
        default:
            cout << "Error - Invalid choice!" << endl;
            break;
        }

        // ask user to run the menu again
        cout << endl << "Do you want to run the cipher menu again? (Y/N)" << endl;
        cin >> runAgain;

        // set runAgain to uppercase
        runAgain = toupper(runAgain);

        // look for proper input for the characters Y and N
        while (isValidChar(runAgain) == false)
        {
            // ask user to run the menu again
            cout << endl << "Sorry, Invalid Input. Please try again.\n";
            cout << endl << "Do you want to run the cipher menu again? (Y/N)" << endl;
            cin >> runAgain;

            // set runAgain to uppercase
            runAgain = toupper(runAgain);
        }

    } while (toupper(runAgain) != 'N'); // statement to keep asking the user until the user decides to stop running the cipher menu
}

int main()
{
    // Main Menu constants
    int const OPTION_SELECT_KEY = 1;
    int const OPTION_ADD_KEY = 2;
    int const OPTION_CIPHER_MENU = 3;
    int const OPTION_QUIT = 4;
    int const OPTION_EMPTY_KEY = 5;

    // variables
    int mainMenuChoice;
    int index = 0;
    int keyNumber = 0;
    string fileName;
    string key = "";
    string newKey;
    Key keysData;
    bool isFileOpen = false;

    // Ask the user to type the file name
    cout << "what is the name of the file that you would like to use?\n";
    getline(cin, fileName);

    // Open the file inside the Key class
    // For this project the name of the file is "Keys.txt"
    keysData.OpenFileOutside(fileName, isFileOpen);

    // if statement to continue running the program when the key file is open
    if (isFileOpen == true)
    {
        // close the file
        // the program closes the file here since it will get open again
        // when other functions in the key class get call
        keysData.CloseFile();

        // do while loop to continue giving the user opportunities to run the program
        // until the user decides to stop using it
        do
        {
            // display the main menu for the keys options
            mainMenuChoice = mainMenuDisplay(keysData, fileName, index);

            // Change option value if the user wants to go to the cipher menu
            // and there is no key selected
            if (key == "" && mainMenuChoice == 3)
            {
                // change mainMenuChoice
                mainMenuChoice = 5;
            }

            // Switch statement to select between different options in the menu
            switch (mainMenuChoice)
            {
                // Select Key from file
            case OPTION_SELECT_KEY:
                // Ask user for the input option of the key the user wants to select
                cout << endl << "Please select the number of the key you want to pick: ";
                cin >> keyNumber;
                // subtract 1 to the number of the key the user wants to act as an index for the GetKey function
                keyNumber -= 1;
                // set the string key equal to the selected key in the file
                key = keysData.GetKey(keyNumber);
                // Display the results of the selection
                cout << endl << "This is your current key: " << key << endl;
                break;

                // Add new key to file
            case OPTION_ADD_KEY:
                // Ask user for the input of the new key to be added in the file
                cin.ignore(); // removes the error between cin and getline
                cout << endl << "Please write down the new key you want to add in the list:\n";
                getline(cin, newKey);
                // send the newKey string into the file to get save
                keysData.SaveKey(fileName, newKey);
                // reset index for the next loop
                index = 0;
                break;

                // Open the menu for the vigenere cipher menu
            case OPTION_CIPHER_MENU:
                // Display the Vigenere cipher menu and run its code
                VigenereCipherSection(key);
                break;

                // stop the program
            case OPTION_QUIT:
                // display for choosing to quit the program
                cout << endl << "You chose to quit the program.\n";
                break;

                // Run this option when the user tries to go to the cipher menu
                // and no key was selected
            case OPTION_EMPTY_KEY:
                // Display to prevent the user going to the cipher menu when there is no key selected
                cout << endl << "You have not selected a key to use in the Cipher Menu.\n";
                cout << "Try again and select a key before going to the Cipher Menu.\n";
                break;

                // Invalid choice (to catch errors)
            default:
                cout << endl << "Error - Invalid choice!\n";
                break;
            }
        } while (mainMenuChoice != OPTION_QUIT);
    }
    // stop running the program if the key file is not open
    else
    {
        // Display for file not opening
        cout << "Error opening file!\n";
    }

    // Destroy the keys object
    keysData.~Key();

    return 0;
}