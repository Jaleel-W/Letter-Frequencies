#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

// Function to calculate letter frequencies
std::map<char, double> calculateFrequencies(const std::string& text) {
    std::map<char, int> letterCounts;
    int totalLetters = 0;

    // Count occurrences of each letter
    for (char ch : text) {
        if (std::isalpha(ch)) {
            char upperCh = std::toupper(ch);
            letterCounts[upperCh]++;
            totalLetters++;
        }
    }

    // Calculate relative frequencies
    std::map<char, double> relativeFrequencies;
    for (const auto& pair : letterCounts) {
        relativeFrequencies[pair.first] = static_cast<double>(pair.second) / totalLetters;
    }

    return relativeFrequencies;
}

// Function to print frequencies
void printFrequencies(const std::map<char, double>& frequencies) {
    std::cout << "Letter Frequencies in Ciphertext:\n";
    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

// Function to decrypt ciphertext using a substitution map
std::string decrypt(const std::string& ciphertext, const std::map<char, char>& substitutionMap) {
    std::string plaintext;
    for (char ch : ciphertext) {
        if (std::isalpha(ch)) {
            char upperCh = std::toupper(ch);
            if (substitutionMap.find(upperCh) != substitutionMap.end()) {
                plaintext += substitutionMap.at(upperCh);
            } else {
                plaintext += ch; // Keep the character as is if not in the map
            }
        } else {
            plaintext += ch; // Keep non-alphabetic characters
        }
    }
    return plaintext;
}

int main() {
    // Ciphertext
    std::string ciphertext = "GWC uiw afsrx qcfh fhq rfc Nmjsgq Rmpcb! Xc pcqamg acvsr rfc uiw rm rfc qcfh. Rfc uiw rm rfc qcfh, rfc qcfh rm rfc uiw, rfc uiw rm rfc qcfh, rfc qcfh rm rfc uiw.";

    // Calculate letter frequencies
    std::map<char, double> frequencies = calculateFrequencies(ciphertext);

    // Print frequencies
    printFrequencies(frequencies);

    // Provided English letter frequencies
    std::map<char, double> englishFrequencies = {
        {'A', 0.0817}, {'B', 0.0150}, {'C', 0.0278}, {'D', 0.0425}, {'E', 0.1270},
        {'F', 0.0223}, {'G', 0.0202}, {'H', 0.0609}, {'I', 0.0697}, {'J', 0.0015},
        {'K', 0.0077}, {'L', 0.0403}, {'M', 0.0241}, {'N', 0.0675}, {'O', 0.0751},
        {'P', 0.0193}, {'Q', 0.0010}, {'R', 0.0599}, {'S', 0.0633}, {'T', 0.0906},
        {'U', 0.0276}, {'V', 0.0098}, {'W', 0.0236}, {'X', 0.0015}, {'Y', 0.0197},
        {'Z', 0.0007}
    };

    // Sort ciphertext frequencies for comparison
    std::vector<std::pair<char, double>> sortedCipherFrequencies(frequencies.begin(), frequencies.end());
    std::sort(sortedCipherFrequencies.begin(), sortedCipherFrequencies.end(),
              [](const std::pair<char, double>& a, const std::pair<char, double>& b) {
                  return a.second > b.second;
              });

    // Sort English frequencies for comparison
    std::vector<std::pair<char, double>> sortedEnglishFrequencies(englishFrequencies.begin(), englishFrequencies.end());
    std::sort(sortedEnglishFrequencies.begin(), sortedEnglishFrequencies.end(),
              [](const std::pair<char, double>& a, const std::pair<char, double>& b) {
                  return a.second > b.second;
              });

    // Create a substitution map based on frequency matching
    std::map<char, char> substitutionMap;
    for (size_t i = 0; i < sortedCipherFrequencies.size(); i++) {
        substitutionMap[sortedCipherFrequencies[i].first] = sortedEnglishFrequencies[i].first;
    }

    // Print substitution map
    std::cout << "\nSubstitution Map:\n";
    for (const auto& pair : substitutionMap) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }

    // Decrypt the ciphertext using the substitution map
    std::string plaintext = decrypt(ciphertext, substitutionMap);

    // Print decrypted plaintext
    std::cout << "\nDecrypted Plaintext:\n" << plaintext << "\n";

    return 0;
}