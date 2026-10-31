#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // Not run by the quick start's command: its coverage report shows these lines as uncovered.
        std::cout << "Hello, " << argv[1] << "!" << std::endl;
        return 0;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
