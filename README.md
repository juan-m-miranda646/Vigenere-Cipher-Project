### PROJECT INFORMATION

Team: One

Member(s): Juan Miranda

Class: CIS 7

Case 3 - Vigenère cipher 

Date published: November 26, 2024

### PROGRAM DESCRIPTION

This program lets the user save and select keys from a file.
Then using that selected key, the user has the option to type plaintext
to encrypt it or type a ciphertext to decrypt it.

### PROGRAMMING APPROACHES

First, I decided to focus on the encryption and decryption functions since
those are the main functions of the project. I used the Unit 11 lab,
Exercise 1, as a reference to model the code for the vigenere cipher.
I also used the comments in the project criteria document for the vigenere
encryption and decryption equations. Once those functions were working, I
decided to implement a menu system that will allow the user to choose to 
either encrypt or decrypt a message. I used some references from CIS-5
and CIS-1A projects I did before. Once the cipher encryption and 
decryption menu was working, I decided to add a class to manage the cipher
keys. My inspiration for this was the Simple Key Loader (SKL) that the 
United States Army uses. I decided to use a file inside the class Key to
manage all the keys. It also makes the program more secure since the member
variable fstream is in the private section of the class, which means that only
the class can make changes to this member variable. In the public section of
the class, there is a single member variable for a vector string. This member
variable is used to get the keys from the files into the vector string. The
member functions in the class are used to get the keys in the file into the
vector string, add new keys to the file, close or open the file, and return
a specific key as a string.

### Basic Instructions

1. First, make sure that you have a .txt file that you can use for the program.
The program can add new keys to the .txt file but it cannot create a file.
Below is the .txt file that I used.

Link for .txt file ["Keys.txt"](https://github.com/juan-m-miranda646/Vigenere-Cipher-Project/blob/02f1ce0c889e138e86b23030dd09baf4ff66d9a2/src%20Folder/Keys.txt)

3. When the program asks you to input the file name, make sure that you type the
name as well as the format of the file.

EXAMPLE.

"Keys.txt", "Cipher.txt", etc.

3. Read carefully and follow the directions that the program displays.
Even if you make a mistake in your input, the program has input
validation to help you go through the menu's options. The only
inputs that do not have input vailidation are the ones for writing
down a new key, the plaintext, and the ciphertext.

4. To end the program, make sure you select the option for quitting
in the main menu.

### IMPORTANT

For saving a cipher key to work properly, make sure that the next
element in the file is already in place.

EXAMPLE. (This is how it should look in the file section)

1    EARN

2    SECRET

3    (this should be empty for the next key to be save and not be appended to the previous key)
