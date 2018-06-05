#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
#include "helpers/sf_Vector_traits.hpp"
#include "Resource.hpp"
#include "data/World.hpp"
#include "graphics/WorldRenderer.hpp"
#include "Camera.hpp"
#include "helpers/keyb.hpp"
#include "forms/QuitConfirm.hpp"
using std::cout;
using std::endl;


int main(int argc, char** argv)
{
	using namespace std::literals;

    // Font
    auto mainFont = make_resource<sf::Font>("./resources/fonts/sansation.ttf");
	    
    // Cells data
    World world(128);

    // Graphics
    WorldRenderer worldRenderer(world, 28);

    // App mode
    enum AppMode : std::uint8_t {
        Edit, Play
    };

    auto appMode = AppMode::Edit;
    float appClock = 0.f;
    float refresh = .75f;
    

    // Mouse & cursor
    sf::Vector2i mousePos;
    bool mouseViewMode = false;
    bool cursorsAvailable = false;
    bool drawAuthorized = false;
    sf::Cursor defaultCursor, crossCursor;
    if ( crossCursor.loadFromSystem(sf::Cursor::Cross) )
        cursorsAvailable = true;
    
    // Clicked cell
    size_t clickedCellNumber = 0;
    char   clickedCellState = 2;


    // Select cells rectangle
    sf::RectangleShape selectRect;
    selectRect.setOutlineThickness(4.f);
    selectRect.setOutlineColor(sf::Color::Red);
    selectRect.setFillColor(sf::Color::Transparent);
    selectRect.setSize({0, 0});
    selectRect.setOrigin(makeVector(-selectRect.getOutlineThickness()));    
    sf::Vector2f selectRectStartPos;
    bool selectionStarted = false;
    

	//////////////////////////////////////////////////////////
    //  Window creation
    //////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(640, 480), "Automaton", sf::Style::Default);
    window.setFramerateLimit(50);
    

    // Forms
    QuitConfirm quitForm(mainFont);
    quitForm.setOrigin(quitForm.getLocalBounds().width / 2.f, quitForm.getLocalBounds().height / 2.f);
    quitForm.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);


    //////////////////////////////////////////////////////////
    //  Camera (view)
    //////////////////////////////////////////////////////////
    sf::View defaultView = window.getDefaultView();
    Camera camera(window);
    float cameraRunSpeed = 3.5f;
    camera.centerOn(worldRenderer.getBounds().width / 2.f, worldRenderer.getBounds().height / 2.f);

    
    //////////////////////////////////////////////////////////
    //  Frame clock
    //////////////////////////////////////////////////////////
    sf::Clock clock;
    sf::Time frameTime;
    float frameSeconds = frameTime.asSeconds();
    bool showFrameTime = false;



    //////////////////////////////////////////////////////////
    //  Main app loop
    //////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        //////////////////////////////////////////////////////////
        //  Frame time
        //////////////////////////////////////////////////////////
        frameTime = clock.restart();
        frameSeconds = frameTime.asSeconds();
        showFrameTime && std::cout << 1.f / frameSeconds << std::endl;


        //////////////////////////////////////////////////////////
        //  Events handling loop
        //////////////////////////////////////////////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ( event.type == sf::Event::Closed )
                window.close();


            else if ( event.type == sf::Event::Resized )
            {
                // Views proportions
                camera.onWindowResize();
                defaultView.setSize(static_cast<sf::Vector2f>(window.getSize()));
                defaultView.setCenter(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
                quitForm.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
                window.setMouseCursorGrabbed(false);
            }


            // Keyboard keys
            else if ( event.type == sf::Event::KeyPressed )
            {
                switch ( event.key.code ) {
                    case kEscape:
                        quitForm.toggleDisplay();
                    break;

                    case kReturn:
                        if ( quitForm.isDisplayed() )
                            window.close();
                        else if ( appMode == AppMode::Edit )
                            appMode = AppMode::Play;
                        else appMode = AppMode::Edit;
                    break;

                    case kPageUp:
                        camera.zoomIn();
                    break;
                    case kPageDown:
                        camera.zoomOut();
                    break;
                    case kZ:
                        camera.resetZoom();
                    break;

                    case kAdd:
                        if (refresh > .125f)
                            refresh -= .125f;
                        
                        else if (refresh > .025f)
                            refresh -= .025f;

                        else refresh -= .005f;

                        if (refresh < .005f)
                            refresh = .005f;
                    break;
                    case kSubtract:
                        if (refresh < .025f)
                            refresh += .005f;
                        
                        else if (refresh < .125)
                            refresh += .25f;

                        else refresh += .125f;

                        if ( refresh > 2.f )
                            refresh = 2.f;
                    break;
                    case kR:
                        refresh = .75f;
                    break;
                }
            }


            else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( event.mouseButton.button == sf::Mouse::Middle ) {
                    if ( cursorsAvailable )
                        window.setMouseCursor(crossCursor);
                    else
                        window.setMouseCursorVisible(false);
                    
                    window.setMouseCursorGrabbed(true);
                    mouseViewMode = true;
                    mousePos = sf::Mouse::getPosition(window);
                }

                else if ( event.mouseButton.button == sf::Mouse::Left ) {
                    // Prevent drawing cells while we move or resize the window
                    drawAuthorized = true;
                    window.setMouseCursorGrabbed(false);
                }
            }


            else if ( event.type == sf::Event::MouseButtonReleased )
            {
                if ( event.mouseButton.button == sf::Mouse::Middle )
                {
                    mouseViewMode = false;

                    if ( cursorsAvailable )
                        window.setMouseCursor(defaultCursor);
                    else
                        window.setMouseCursorVisible(true);

                    window.setMouseCursorGrabbed(false);
                }
                
                else if ( event.mouseButton.button == sf::Mouse::Left ) {
                    // Resetting cursor states
                    clickedCellNumber = 0;
                    clickedCellState = 2;
                    drawAuthorized = false;
                }

                else if ( event.mouseButton.button == sf::Mouse::Right ) {
                    if ( selectionStarted )   // We selected some cells
                    {
                        auto cellSize = worldRenderer.getCellSize();
                        auto worldBounds = worldRenderer.getBounds();
                        auto rectBounds = selectRect.getGlobalBounds();

                        sf::Vector2f rectBeg = { rectBounds.left, rectBounds.top };
                        sf::Vector2f rectEnd = { rectBounds.left + rectBounds.width, rectBounds.top + rectBounds.height };

                        for ( float y = rectBeg.y;  y < rectEnd.y;  y += cellSize )
                        for ( float x = rectBeg.x;  x < rectEnd.x;  x += cellSize )
                        {
                            if ( worldBounds.contains({x, y}) ) {
                                auto cellN = worldRenderer.graphicsCoordsToCellNumber({x, y});
                                sf::Vector2f upLeftPoint = (worldRenderer.getCellPoint(cellN))->position;
                                sf::Vector2f downRightPoint = { upLeftPoint.x + cellSize, upLeftPoint.y + cellSize };
                                if ( world[cellN].isAlive() )
                                    world[cellN].toggleEdit();
                            }
                        }

                        selectionStarted = false;
                        selectRect.setSize({0, 0});
                    }
                }
            }


            else if ( event.type == sf::Event::MouseWheelMoved )
            {
                if ( event.mouseWheelScroll.wheel < 0 )
                    camera.zoomOut();
                else
                    camera.zoomIn();
            }
        } // -- events handling loop end

        
        //////////////////////////////////////////////////////////
        //  Live events
        //////////////////////////////////////////////////////////
        if ( window.hasFocus() )
        {
            //////////////////////////////////////////////////////////
            //  Mouse
            //////////////////////////////////////////////////////////
            if ( mouseViewMode ) {
                auto mnpos = sf::Mouse::getPosition(window);
                camera.move(static_cast<sf::Vector2f>(mousePos - mnpos));
                // camera.move(static_cast<sf::Vector2f>(mnpos - mousePos));
                sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
                mousePos = sf::Mouse::getPosition(window);
            }
            
            else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) && appMode == AppMode::Edit )
            {
                auto mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);

                if ( !selectionStarted ) {
                    selectRectStartPos = mouseWorldPos;
                    selectRect.setPosition(mouseWorldPos);
                    selectionStarted = true;
                }

                else {
                    auto offset = selectRect.getOutlineThickness() * 2.f;
                    selectRect.setSize({
                        mouseWorldPos.x - selectRectStartPos.x - offset,
                        mouseWorldPos.y - selectRectStartPos.y - offset
                    });
                }
            }

            else if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if ( drawAuthorized && appMode == AppMode::Edit )
                {
                    // Check that mouse pointer is on the grid
                    auto mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);

                    if ( worldRenderer.getBounds().contains(mouseWorldPos) ) {
                        auto c = worldRenderer.graphicsCoordsToCellNumber(mouseWorldPos) + 1;
                        if ( clickedCellNumber != c ) {
                            clickedCellNumber = c;
                            if ( clickedCellState == 2 || clickedCellState != (char)world[c - 1].isAlive() ) {
                                world[c - 1].toggleEdit();
                                clickedCellState = (char)world[c - 1].isAlive();
                            }
                        }
                    }
                }
            }


            //////////////////////////////////////////////////////////
            //  Keyboard
            //////////////////////////////////////////////////////////
            if ( !mouseViewMode )
            {
                if ( keyb(kLShift) || keyb(kRShift) ) {
                    if ( keyb(kUp) )
                        camera.move( 0, -camera.getSpeed().y * cameraRunSpeed * frameSeconds );

                    if ( keyb(kDown) )
                        camera.move( 0, camera.getSpeed().y * cameraRunSpeed * frameSeconds );

                    if ( keyb(kLeft) )
                        camera.move( -camera.getSpeed().x * cameraRunSpeed * frameSeconds, 0 );

                    if ( keyb(kRight) )
                        camera.move( camera.getSpeed().x * cameraRunSpeed * frameSeconds, 0 );
                }
                else {
                    if ( keyb(kUp) )
                        camera.move( 0, -camera.getSpeed().y * frameSeconds );

                    if ( keyb(kDown) )
                        camera.move( 0, camera.getSpeed().y * frameSeconds );

                    if ( keyb(kLeft) )
                        camera.move( -camera.getSpeed().x * frameSeconds, 0 );

                    if ( keyb(kRight) )
                        camera.move( camera.getSpeed().x * frameSeconds, 0 );
                }
            }

        } // -- live events end (window.hasFocus())

        else  {     // If window has lost focus, reset some stuff
            if ( cursorsAvailable )
                window.setMouseCursor(defaultCursor);
            else
                window.setMouseCursorVisible(true);
            
            window.setMouseCursorGrabbed(false);
            mouseViewMode = false;
            drawAuthorized = false;
        }
        

        // --- Data update
        if ( appMode == AppMode::Play )
        {
            if ( appClock == 0.f )
                world.computeNextState();
            
            appClock += frameSeconds;

            if ( appClock > refresh )
                appClock = 0.f;
        }


        // --- Graphic update
        worldRenderer.update();


        //////////////////////////////////////////////////////////
        //  Display
        //////////////////////////////////////////////////////////
        window.clear(sf::Color(46, 90, 254));
        
        window.setView(camera);
          window.draw(worldRenderer);
          window.draw(selectRect);
        
        window.setView(defaultView);
          window.draw(quitForm);

        window.display();


    }   // End of main loop


	return 0;
}

