/**
   @author Olli-Pekka
   @version 2.0 25.1.2020
*/
class Led
{
  private:
    int _pin;
    int _times[4];
    unsigned long timeIndex = 0;
    unsigned long latestTime = 0;
    int ledState = LOW;
    int _wait;
    bool ifwait = true;

  public:
    Led(int pin, const int times[4], int wait);
    int Stop();
    int Start();
    int Check();
    int WaitBeforeStart();
};

Led::Led(int pin, const int times[4], int wait)
{
  for (int i = 0; i < 4; i++)
  {
    _times[i] = times[i];
  }
  _pin = pin;
  pinMode(pin, OUTPUT);
  _wait = wait;
}

int Led::Stop()
{
  digitalWrite(_pin, LOW);
}

int Led::Start ()
{
  digitalWrite(_pin, HIGH);
}

int Led::WaitBeforeStart()
{
  if (_wait - millis() <= 0) ifwait = false;
}

int Led::Check()
{
  if (ifwait)
  {
    WaitBeforeStart();
  }
  else
  {
    if (millis() - latestTime >= _times[timeIndex])
    {
      if ( timeIndex == 3)  timeIndex = 0; else  timeIndex += 1;
      if (ledState == HIGH ) ledState = LOW; else ledState = HIGH;
      latestTime = millis();
      digitalWrite(_pin, ledState);
    }
  }
}

const int doubleBlink[4] = {2000, 75 , 75, 75};
const int singleBlink[4] = {2125, 100, 0, 0};
Led strobe = Led(13, doubleBlink, 3000);
Led backlight = Led(12, singleBlink, 0);
Led leftNav = Led(11, singleBlink, 0);
Led leftStrobe = Led(10, singleBlink, 0);
Led rightNav = Led(9, singleBlink, 0);
Led rightStrobe = Led(8, singleBlink, 0);

void setup()
{
  leftNav.Start();
  rightNav.Start();
  backlight.Start();
}

/**
   Kutsutaan ledejä ohjaavia ohjelmia
*/
void loop()
{
  strobe.Check();
  leftStrobe.Check();
  rightStrobe.Check();
}
