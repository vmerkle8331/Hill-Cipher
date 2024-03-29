#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

float encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];

// Function declarations
void encryption(); // Encrypts the message
void decryption(); // Decrypts the message
void getKeyMessage(const string& inputFilename); // Gets key and message from input file
void inverse(); // Finds the inverse of the key matrix
void writeToFile(const string& outputFilename, const string& content); // Writes output to a file

int main() {
    string inputFilename = "class_input_c.txt";
    getKeyMessage(inputFilename);
    encryption();
    decryption();
    return 0;
}

void encryption() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 3; k++)
                encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];

    string encryptedString = "";
    for (int i = 0; i < 3; i++)
        encryptedString += (char)(fmod(encrypt[i][0], 26) + 97);

    writeToFile("Doe_output_6c.txt", encryptedString);
    cout << "Encrypted string is: " << encryptedString << endl;
}

void decryption() {
    inverse();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 1; j++)
            for (int k = 0; k < 3; k++)
                decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];

    string decryptedString = "";
    for (int i = 0; i < 3; i++)
        decryptedString += (char)(fmod(decrypt[i][0], 26) + 97);

    cout << "Decrypted string is: " << decryptedString << endl;
}

void getKeyMessage(const string& inputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << inputFilename << endl;
        exit(EXIT_FAILURE);
    }

    // Get key matrix
    cout << "Enter 3x3 matrix for key (It should be inversible):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            inputFile >> a[i][j];
            c[i][j] = a[i][j];
        }

    // Get message
    cout << "\nEnter a 3-letter string (only lowercase letters): ";
    string msg;
    inputFile >> msg;

    // Validate message length
    if (msg.size() != 3) {
        cerr << "Error: Message length should be exactly 3 characters." << endl;
        exit(EXIT_FAILURE);
    }

    // Validate message content
    for (char c : msg) {
        if (c < 'a' || c > 'z') {
            cerr << "Error: Message should contain only lowercase letters." << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Assign message to mes array
    for (int i = 0; i < 3; i++)
        mes[i][0] = msg[i] - 'a'; // Convert character to index

    inputFile.close();
}

void inverse() {
    float p, q;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (i == j)
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }

    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 3; i++) {
            p = c[i][k];
            q = c[k][k];
            for (int j = 0; j < 3; j++) {
                if (i != k) {
                    c[i][j] = c[i][j] * q - p * c[k][j];
                    b[i][j] = b[i][j] * q - p * b[k][j];
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            b[i][j] = b[i][j] / c[i][i];

    cout << "\n\nInverse Matrix is:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
}

void writeToFile(const string& outputFilename, const string& content) {
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << outputFilename << endl;
        exit(EXIT_FAILURE);
    }
    outputFile << content;
    outputFile.close();
}