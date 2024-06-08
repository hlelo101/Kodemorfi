#include <iostream>
#include <vector>
#include <fstream>

// Variables
std::string version = "vP-8.06.24";
std::vector<std::string> lines;
std::string parsedCode = "<!-- Generated by Kodemorfi " + version + " -->";
bool executed = false;

void computeLines() {
    for(int i = 0; i!=lines.size(); i++) {
        if(!lines[i].empty()) {
            if(lines[i].at(0) == '#') { // Big text
                std::cout << "Line " << (i + 1) << ": " << "Big text. Computing... ";
                parsedCode = parsedCode + "<h1>" + lines[i].substr(1) + "</h1>";
                std::cout << "Done" << std::endl;
            } else if(lines[i].at(0) == '\\') { // Escape
                std::cout << "Line " << (i + 1) << ": " << "Escape character. Computing... ";
                parsedCode = parsedCode + "<p>" + lines[i].substr(1) + "</p>";
                std::cout << "Done" << std::endl;
            } else if(lines[i].at(0) == '[' && lines[i].at(2) == ']' || lines[i].at(0) == '[' && lines[i].at(4) == ']') { // Custom font size
                std::cout << "Line " << (i + 1) << ": " << "Custom size text. Computing... ";
                if(lines[i].at(4) == ']') {
                    parsedCode = parsedCode + "<p style=\"font-size: " + lines[i].substr(1, 3) + "em\">" + lines[i].substr(5) + "</p>";
                } else { // Default
                    parsedCode = parsedCode + "<p style=\"font-size: " + lines[i].substr(1, 1) + "em\">" + lines[i].substr(3) + "</p>";
                }
                std::cout << "Done" << std::endl;
            } else {
                parsedCode = parsedCode + "<p>" + lines[i] + "</p>";
            }
        } else {
            break;
        }
    }
    std::cout << "HTML:\n" << parsedCode << std::endl;
}
int main() {
    bool error = false;
    std::cout << "Kodemorfi " << version << std::endl;
    std::cout << "Reading file... ";
    std::ifstream readFile;
    readFile.open("main.km");
    if (readFile.is_open()) {
        std::cout << "Done" << std::endl;
        std::string line;
        while (std::getline(readFile, line)) {
            lines.push_back(line);
        }
        readFile.close();
        computeLines();
    } else {
        std::cout << "Error\nAn error occured during file opening. Ensure that \"main.km\" is present." << std::endl;
        error = true;
        readFile.close();
    }
    if(!error) {
        std::cout << "Writing file... ";
        std::ofstream writeFile;
        writeFile.open("kodemorfi_output.html");
        writeFile << parsedCode;
        writeFile.close();
        std::cout << "Done" << std::endl;
    }
    return 0;
}
