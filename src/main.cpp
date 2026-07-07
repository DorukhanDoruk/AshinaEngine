// Pull in the Application class. See HANDBOOK.md#includes-and-pragma-once
#include "app/application.hpp"

// Program entry point. Returns an exit code to the OS. See HANDBOOK.md#the-main-function
int main() {
    // Build the top-level engine object on the stack. `ashina::` names the namespace.
    // See HANDBOOK.md#namespaces-and-the-scope-resolution-operator
    ashina::Application app;
    // Run the main loop until the window is closed.
    app.run();
    return 0; // 0 means success
}
