#include "app/App.hpp"
#include <filesystem>



App::App() noexcept
{
    
}



const App::Mode& 
App::mode() const {
    return this->mMode;
}



void
App::toggleMode() {
    this->mMode = (mMode == Edit) ? Play : Edit;
}


const float&
App::clock() const {
    return this->mClock;
}


void
App::clockUpdate(float elapsed) {
    this->mClock += elapsed;
}


void
App::clockReset() {
    this->mClock = 0.f;
}


const float&
App::refreshRate() const {
    return this->mRefreshRate;
}


void
App::setRefreshRate(float rate) {
    this->mRefreshRate = rate;
}


void
App::speedUp() {
    this->mRefreshRate -= .05f;
}


void
App::slowDown() {
    this->mRefreshRate += .05f;
}
