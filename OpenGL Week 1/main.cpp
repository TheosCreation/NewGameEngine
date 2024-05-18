#include "MyGame.h"

/**
 * @brief The entry point of the application.
 *
 * This function initializes and runs the game. It catches any exceptions
 * that occur during the execution and logs the error message.
 *
 * @return Returns 0 if the application runs successfully, otherwise returns -1.
 */
int main()
{
    try
    {
        MyGame game; // Create an instance of the game
        game.run();  // Run the game
    }
    catch (const std::exception& e)
    {
        std::wclog << e.what() << std::endl; // Log any exceptions that occur
        return -1; // Return -1 to indicate an error
    }

    return 0; // Return 0 to indicate successful execution
}