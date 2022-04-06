#pragma once

#include <arduino.h>

//������ 1 �� �������

class myButton {
public:
	myButton(uint8_t pin) {
		pinMode(pin, INPUT_PULLUP);			
		_pin = pin;
	}

	void setDebounce(uint16_t value);
	boolean isPressed();
private:
	uint32_t _debounceValue;
	uint8_t _pin;

	boolean button_flag;
	boolean button_pressed;
	boolean one_return;
	uint32_t last_press;
};

boolean myButton::isPressed() {							//������� ���������� ������� �� ������	

	boolean button = !digitalRead(_pin);				//��-��, ��� ��� � ��� � �������?

	if (button && !button_flag							//�������, �� ������
		&& millis() - last_press > _debounceValue) {	//� �� �� ����� �������?
		button_flag = 1;								//�� ��� ��� �� ��������:
		one_return = 1;									//��������� ����, �������� ����...
	}
	if (!button && button_flag) {						//�, ��� ��� � ���, �������, ������ ���� ������, �� ��� ���
		button_flag = 0;								//������ �������� ����, �����
		last_press = millis();							//� ���������� ����� �������� millis()
		one_return = 0;									//�� ����� ������������
	}

	if (one_return) {									//� ����� ���������, ���� �� �������, ������� ���� �������
		one_return = 0;									//���� ����, �� �� ����. ���������� ���� ��� - � �����
		return 1;										//�� ���������� �������
	}
	else return 0;										//������ � ��� ����� � ����� �� ����.
}

void myButton::setDebounce(uint16_t value) {			//������� �������� ������������
	_debounceValue = value;								//��� ���� �������� ������� � ������� ����������
}														//����, ��� �� ������
