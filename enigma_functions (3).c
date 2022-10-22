/* Liam Kelso
 * 
*/
#include "enigma.h"

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
     scanf("%[^\n]", msg);
     int i=0,j=0;
     while(msg[i]!='\0'){
         if(msg[i]!= '\n'){
             msg[j++]=msg[i];
         }
     i++;
     }
     msg[j]='\0';
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
    int rotor_Count = 0;
    scanf("%4s", which_rotors);
    int i = 0;
    while(which_rotors[i]!='\0'){
        rotor_Count++;
        i++;
    }
    return rotor_Count;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
	 int numRotations;   
    scanf("%d", &numRotations);
    return numRotations;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
    int whatRotor;
    int which_rotorCount = 0;
    int i = 0;
    while(which_rotors[which_rotorCount] != '\0'){
        i = 0;
        whatRotor = which_rotors[which_rotorCount] - '0';
        while(ROTOR_CONSTANTS[whatRotor][i] != '\0'){
            encryption_rotors[which_rotorCount][i] = ROTOR_CONSTANTS[whatRotor][i];
            i++;
        }
        which_rotorCount++;
    }
	return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
    int rotorRow = 0;
    int i = 0;
    int last_element;
    for(int j = 0; j < rotations; j++)
    {
        i = 0;
        rotorRow = 0;
        last_element = 0;
        while(encryption_rotors[rotorRow][i] != '\0'){
        last_element = encryption_rotors[rotorRow][25];
            for(int i = 26; i > 0; i--){
            encryption_rotors[rotorRow][i] = encryption_rotors[rotorRow][i-1];
            }
        encryption_rotors[rotorRow][0] = last_element;
        rotorRow++;
        i = 0;
        last_element = 0;
        }
    }
    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
   int i = 0;
    char placeholder;
    int indexChar;
    int d=0;
    //Loop through the message
    while(msg[i] != '\0'){
        //break if space maybe
        //sets placeholder to the current char in i
        while(msg[i] == ' ' && msg[i+1] != '\0'){
            encrypted_msg[i] = ' ';
            i++;
        }
        placeholder = msg[i];
        //loop through rotor 0 alphabet to find first index
        //loop through the entire encryption rotor until null terminal to find matching char, for loop with num_ac_rotors.
        for(int columnCount = 0; columnCount < num_active_rotors; columnCount++){
            d = 0;
            for(int d = 0; d < 26; d++){
                if(ROTOR_CONSTANTS[0][d] == placeholder){
                    indexChar = d;
                }
            }
	    if(placeholder != ' '){
                placeholder = encryption_rotors[columnCount][indexChar];
            }
        }
        //Set placeholder to equal that char. at the end of the loop, add placeholder to encrypted_msg and then set everything equal to 0. Should work! :)
        encrypted_msg[i] = placeholder;
        i++;
    }
    encrypted_msg[i] = '\0';
       	return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
   int i = 0;
    char placeholder;
    int indexChar;
    int d=0;
    //Loop through the message
    while(encrypted_msg[i] != '\0'){
        //break if space maybe
        //sets placeholder to the current char in i
	while(encrypted_msg[i] == ' '){
            decrypted_msg[i] = ' ';
            if(encrypted_msg[i+1] != '\0'){
             i++;
            }
            else{
                break;
            }
        }
        placeholder = encrypted_msg[i];
        for(int columnCount = num_active_rotors - 1; columnCount > -1; columnCount--){
            d = 0;
            for(int d = 0; d < 26; d++){
                if(encryption_rotors[columnCount][d] == placeholder){
                    indexChar = d;
                }
            }
	    if(placeholder != ' '){
                placeholder = ROTOR_CONSTANTS[0][indexChar];
            }
        }
        //Set placeholder to equal that char. at the end of the loop, add placeholder to encrypted_msg and then set everything equal to 0. Should work! :)
        decrypted_msg[i] = placeholder;
        i++;
    }
   decrypted_msg[i] = '\0';
       	return;
}


