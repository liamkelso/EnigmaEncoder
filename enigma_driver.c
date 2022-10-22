#include "enigma.h"

int main() {
    char message[80];
    char encrypted_message[80];
    char decrypted_message[80];
    char which_rotors[5];
    char encryption_rotors[4][27];
    int rotations;
    int num_active_rotors;

    printf("Enter the message to be encrypted or decrypted: ");
    Get_Message(message);

    printf("\nWhich rotors will be used to encrypt the message: ");
    num_active_rotors = Get_Which_Rotors(which_rotors); 

    printf("\nEnter the number of rotations to apply to the encryption rotors: ");
    rotations = Get_Rotations();

    Set_Up_Rotors(encryption_rotors, which_rotors);
    Apply_Rotation(rotations, encryption_rotors);
    Encrypt(encryption_rotors, num_active_rotors, message, encrypted_message);
    Decrypt(encryption_rotors, num_active_rotors, encrypted_message, decrypted_message);

    printf("The encrypted message is: %s", encrypted_message);
    printf("The decrypted message is: %s", decrypted_message);

    return 0;
}
