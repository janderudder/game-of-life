/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "helpers/keyb.hpp"
#include "helpers/ProjectPath.hpp"
#include "helpers/Resource.hpp"
#include "helpers/sf_Vector_traits.hpp"
#include "app/App.hpp"
#include "app/Cursor.hpp"
#include "data/World.hpp"
#include "forms/QuitConfirm.hpp"
#include "graphics/WorldRenderer.hpp"
#include "Camera.hpp"
using std::cout;
using std::endl;


int main(int argc, char** argv)
{
    //////////////////////////////////////////////////////////
    //  Initialisation
    //////////////////////////////////////////////////////////
	using namespace std::literals;


    // Project absolute path
    ProjectPath::Init(argv[0]);


    // Font
    auto mainFont = makeResource<sf::Font>(ProjectPath::Get("resources/fonts/sansation.ttf"));


    // Cells data
    World world(128);


    // Graphics
    WorldRenderer worldRenderer(world, 12);


    // App : handling some application apects
    App app;


    // Window creation, size changes according to screen resolution
    sf::RenderWindow window;
    if ( sf::VideoMode::getDesktopMode().width >= 1024 )
        window.create(sf::VideoMode(800, 600), "Automaton", sf::Style::Default);
    else
        window.create(sf::VideoMode::getDesktopMode(), "Automaton", sf::Style::Default);

    window.setFramerateLimit(50);


    // Mouse & cursor
    Cursor cursor(window);

    sf::Vector2i mousePos;
    bool drawAuthorized = false;


    // Clicked cell
    size_t clickedCellNumber = 0;
    char   clickedCellState = 2;    // 2 = not dead nor alive (0 nor 1)


    // Select cells rectangle
    sf::RectangleShape selectRect;
    selectRect.setOutlineThickness(4.f);
    selectRect.setOutlineColor(sf::Color::Red);
    selectRect.setFillColor(sf::Color::Transparent);
    selectRect.setSize({0, 0});
    selectRect.setOrigin(makeVector(-selectRect.getOutlineThickness()));
    sf::Vector2f selectRectStartPos;
    bool selectionStarted = false;
    bool selectionPossible = true;


    // Forms
    QuitConfirm quitForm(*mainFont);
    quitForm.setOrigin(quitForm.getLocalBounds().width / 2.f, quitForm.getLocalBounds().height / 2.f);
    quitForm.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);


    // Generations : previous and future stacks
    bool movedInTime = false;


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

                // Forms
                quitForm.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

                // Cursor
                cursor.onWindowResize(window.getSize());
            }


            // Keyboard keys
            else if ( event.type == sf::Event::KeyPressed )
            {
                switch ( event.key.code ) {
                    case kEscape:
                        if ( selectionStarted ) {   // If we were drawing the seletion rectangle, stop and reset it
                            selectionStarted = false;
                            selectRect.setSize({0, 0});
                            selectionPossible = false;
                        }
                        else
                            quitForm.toggleDisplay();
                    break;

                    case kReturn:
                        if ( quitForm.isDisplayed() )
                            window.close();
                        else
                            app.toggleMode();
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
                        if (app.refreshRate() > .125f)
                            // refresh -= .125f;
                            app.speedUp();

                        else if (app.refreshRate() > .025f)
                            // refresh -= .025f;
                            app.speedUp();

                        else
                            // refresh -= .005f;
                            app.speedUp();

                        if (app.refreshRate() < .005f)
                            app.setRefreshRate(.005f);
                    break;

                    case kSubtract:
                        if (app.refreshRate() < .025f)
                            // refresh += .005f;
                            app.slowDown();

                        else if (app.refreshRate() < .125)
                            // refresh += .25f;
                            app.slowDown();

                        else
                            // refresh += .125f;
                            app.slowDown();

                        if ( app.refreshRate() > 2.f )
                            app.setRefreshRate(2.f);
                    break;

                    case kR:
                        app.setRefreshRate(.75f);
                    break;

                    case kC:
                        camera.centerOn(
                            sf::Vector2f(worldRenderer.getBounds().width, worldRenderer.getBounds().height)
                            / 2.f
                        );
                    break;

                    case kB:
                        if ( app.mode() == App::Edit ) {
                            world.goBackward();
                            movedInTime = true;
                        }
                    break;

                    case kF:
                        if ( app.mode() == App::Edit ) {
                            world.computeNextState();
                            movedInTime = true;
                        }
                    break;
                }
            }


            else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( event.mouseButton.button == sf::Mouse::Middle ) {
                    cursor.setMode(Cursor::Crosshair);
                    mousePos = sf::Mouse::getPosition(window);
                }

                else if ( event.mouseButton.button == sf::Mouse::Left ) {
                    // Prevent drawing cells while we move or resize the window, because when we click
                    // on window's sides or title bar, this event will not be fired.
                    drawAuthorized = true;
                }
            }


            else if ( event.type == sf::Event::MouseButtonReleased )
            {
                if ( event.mouseButton.button == sf::Mouse::Middle ) {
                    cursor.setMode(Cursor::Normal);
                }

                else if ( event.mouseButton.button == sf::Mouse::Left ) {
                    // Resetting cursor states
                    clickedCellNumber = 0;
                    clickedCellState = 2;
                    drawAuthorized = false;
                }

                else if ( event.mouseButton.button == sf::Mouse::Right ) {
                    if ( !selectionPossible )
                        selectionPossible = true;   // Reset the possibility to select, after cancelling selection

                    else if ( selectionStarted )    // We selected some cells
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
                                sf::Vector2f upLeftPoint = worldRenderer.getCellPoint(cellN)->position;
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
            if ( cursor.getMode() == Cursor::Crosshair )  {
                auto newMousePos = sf::Mouse::getPosition(window);
                camera.move(static_cast<sf::Vector2f>(newMousePos - mousePos));
                sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
                mousePos = sf::Mouse::getPosition(window);
            }

            else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) && app.mode() == App::Edit )
            {
                auto mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);

                if ( !selectionStarted && selectionPossible ) {
                    selectRectStartPos = mouseWorldPos;
                    selectRect.setPosition(mouseWorldPos);
                    selectionStarted = true;
                }

                else if ( selectionPossible ) {
                    auto offset = selectRect.getOutlineThickness() * 2.f;
                    selectRect.setSize({
                        mouseWorldPos.x - selectRectStartPos.x - offset,
                        mouseWorldPos.y - selectRectStartPos.y - offset
                    });
                }
            }

            else if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if ( drawAuthorized && app.mode() == App::Edit )
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
            if ( cursor.getMode() == Cursor::Normal )
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
            cursor.setMode(Cursor::Normal);
            drawAuthorized = false;
        }

        // Correct "mysterious" mouse grab bug
        if ( cursor.getMode() != Cursor::Crosshair )
            window.setMouseCursorGrabbed(false);


        // --- Data update
        if ( movedInTime ) {
            app.clockReset();
            movedInTime = false;
        }

        else if ( app.mode() == App::Play ) {
            if ( app.clock() == 0.f )
                world.computeNextState();

            app.clockUpdate(frameSeconds);

            if ( app.clock() > app.refreshRate() )
                app.clockReset();
        }


        // --- Graphic update
        worldRenderer.update();


        //////////////////////////////////////////////////////////
        //  Display
        //////////////////////////////////////////////////////////
        window.clear(sf::Color(227, 223, 223));

        window.setView(camera);
            window.draw(worldRenderer);
            window.draw(selectRect);

        window.setView(defaultView);
            window.draw(cursor);
            window.draw(quitForm);

        window.display();


    }   // End of main loop


	return 0;
}

