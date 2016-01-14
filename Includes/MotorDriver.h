class CMotor
{
  private:
  char m_cFEnable, m_cREnable;
  char m_cFPWM, m_cRPWM;
  public:
  CMotor(char cForwardEnablePin, char cReverseEnablePin, char cForwardPWM, char cReversePWM)
  {
    m_cFEnable = cReverseEnablePin;
    m_cREnable = cReverseEnablePin;
    m_cFPWM = cForwardPWM;
    m_cRPWM = cReversePWM;

    pinMode(m_cFEnable, OUTPUT);
    pinMode(m_cREnable, OUTPUT);
    pinMode(m_cFPWM, OUTPUT);
    pinMode(m_cRPWM, OUTPUT);
    analogWrite(m_cFPWM, 0);
    analogWrite(m_cRPWM, 0);
  }
  void SetMotorSpeed(char cNewSpeed)
  {
    //Disable all drive
    digitalWrite(m_cFEnable, LOW);
    digitalWrite(m_cREnable, LOW);
    analogWrite(m_cFPWM, 0);
    analogWrite(m_cRPWM, 0);
    if(cNewSpeed & 0b10000000)
    {
      digitalWrite(m_cFEnable, LOW);
      digitalWrite(m_cREnable, HIGH);
      analogWrite(m_cFPWM, 0);
      analogWrite(m_cRPWM, cNewSpeed << 1);
    }
    else
    {
      digitalWrite(m_cFEnable, HIGH);
      digitalWrite(m_cREnable, LOW);
      analogWrite(m_cFPWM, cNewSpeed << 1);
      analogWrite(m_cRPWM, 0);
    }
  }
};

