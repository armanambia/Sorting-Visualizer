//#include <SFML\Audio.hpp>
//#include <SFML\Graphics.hpp>
//#include <iostream>
//int main()
//{
//    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
//    // Load a sprite to display
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
//    player.setFillColor(sf::Color::Red);
//    //player.setOrigin(50.0f, 50.0f);
//    player.setPosition(206.0f, 206.0f);
//    // Texture
//    sf::Texture playerTexture;
//    playerTexture.loadFromFile("tux_from_linux.png");
//    // apply to player
//    player.setTexture(&playerTexture);
//    // texture attributes
//    sf::Vector2u textureSize = playerTexture.getSize();
//    textureSize.x /= 3;
//    textureSize.y /= 9;
//    player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 8, textureSize.x, textureSize.y));
//    // Start the game loop
//    while (window.isOpen())
//    {
//        // Process events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            switch (event.type) {
//            case sf::Event::Closed:
//                window.close();
//                break;
//            case sf::Event::Resized:
//                std::cout << "width: " << event.size.width << ", height: " << event.size.height << std::endl;
//                break;
//            case sf::Event::TextEntered:
//                if (event.text.unicode < 128) {
//                    printf("%c\n", event.text.unicode);
//                }
//                break;
//            }
//            
//            
//        }
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
//        //    player.move(-0.1f, 0.0f);
//        //}
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
//        //    player.move(0.1f, 0.0f);
//        //}
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
//        //    player.move(0.0f, -0.1f);
//        //}
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
//        //    player.move(0.0f, 0.1f);
//        //}
//        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//        //    // pass in window to get position relative to window
//        //    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//        //    player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
//        //    
//        //}
//        // Clear screen
//        window.clear();
//        // Draw the shape
//        // window.draw(shape);
//        window.draw(player);
//        window.display();
//    }
//    return EXIT_SUCCESS;
//}