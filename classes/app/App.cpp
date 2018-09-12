#include "app/App.hpp"
#include <filesystem>



App::App() noexcept
{

}



const App::Mode&
App::mode() const {
    return mMode;
}



void
App::toggleMode() {
    mMode = (mMode == Edit) ? Play : Edit;
}


const float&
App::clock() const {
    return mClock;
}


void
App::clockUpdate(float elapsed) {
    mClock += elapsed;
}


void
App::clockReset() {
    mClock = 0.f;
}


const float&
App::refreshRate() const {
    return mRefreshRate;
}


void
App::setRefreshRate(float rate) {
    mRefreshRate = rate;
}


void
App::speedUp() {
    mRefreshRate -= .05f;
}


void
App::slowDown() {
    mRefreshRate += .05f;
}
