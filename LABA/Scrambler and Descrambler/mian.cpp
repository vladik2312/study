#include <iostream>
#include <bitset>
#include <random>

using namespace std;

// Scrambler function
string scrambler(string input, int K, string shiftRegister)
{
    int registerLen = shiftRegister.size();
    string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        int feedbackBit = (shiftRegister[0] - '0') ^ (shiftRegister[1] - '0') ^ (shiftRegister[4] - '0');
        int inputBit = input[i] - '0';
        output += to_string(feedbackBit ^ inputBit);
        shiftRegister = shiftRegister.substr(1) + to_string(feedbackBit);
    }
    return output;
}

// Descrambler function
string descrambler(string input, int K, string shiftRegister)
{
    int registerLen = shiftRegister.size();
    string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        int feedbackBit = (shiftRegister[0] - '0') ^ (shiftRegister[1] - '0') ^ (shiftRegister[4] - '0');
        int inputBit = input[i] - '0';
        output += to_string(feedbackBit ^ inputBit);
        shiftRegister = shiftRegister.substr(1) + input[i];
    }
    return output;
}

// Random sequence generator function
string randomSequenceGenerator(int K)
{
    string output = "";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);
    for (int i = 0; i < K; i++)
    {
        output += to_string(distrib(gen));
    }
    return output;
}

int main()
{
    // Variant 16 parameters
    int K = 12;
    string shiftRegister = "1001000100001";
    int outputRegister = 11;

    // Generate random sequence
    string inputSequence = randomSequenceGenerator(K);
    cout << "Input sequence: " << inputSequence << endl;

    // Scramble the sequence
    string scrambledSequence = scrambler(inputSequence, K, shiftRegister);
    cout << "Scrambled sequence: " << scrambledSequence << endl;

    // Descramble the sequence
    string descrambledSequence = descrambler(scrambledSequence, K, shiftRegister);
    cout << "Descrambled sequence: " << descrambledSequence << endl;

    // Compare input and descrambled sequences
    if (inputSequence == descrambledSequence)
    {
        cout << "Input and descrambled sequences are the same" << endl;
    }
    else
    {
        cout << "Input and descrambled sequences are different" << endl;
    }

    return 0;
}
