#ifndef APP_HPP
#define APP_HPP
#include <string>
using std::string;

class App
{
public:
    enum Mode : char {
        Edit, Play
    };


private:
    Mode            mMode               =   Edit;
    float           mClock              =   0.f;
    float           mRefreshRate        =   .75f;


public:
    explicit App() noexcept;              // Expects main::argv[0] as argument

    const Mode& mode() const;
    void toggleMode();

    const float& clock() const;
    void clockUpdate(float);
    void clockReset();

    const float& refreshRate() const;
    void setRefreshRate(float);
    void speedUp();
    void slowDown();

};

#endif // APP_HPP
