#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// Function to parse the configuration file
std::unordered_map<std::string, std::string> parseConfigFile(const std::string& configFile) {
    std::unordered_map<std::string, std::string> configSettings;

    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open configuration file " << configFile << std::endl;
        return configSettings; // Return empty map if file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        // Split line into key-value pair
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            // Trim leading and trailing whitespaces
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            // Store key-value pair in map
            configSettings[key] = value;
        }
    }

    return configSettings;
}

int main(int argc, char *argv[]) {
    std::string configFile = "default_config.conf"; // Default configuration file path
    if (argc > 1) {
        configFile = argv[1]; // Use configuration file provided as command-line argument
    }

    // Parse the configuration file
    std::unordered_map<std::string, std::string> configSettings = parseConfigFile(configFile);

    // Display parsed configuration settings
    for (const auto& pair : configSettings) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    return 0;
}
