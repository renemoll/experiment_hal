# Interfaces


Aspects of interest:
* Simple interface
* Avoid mis-use
* Ability to pass a pin around (dependency injection)
* Low overhead (code size / instructions)

Implementation options:
* plain functions
* OOP
* Template
  * Template + interface
* STM32 LL + STM32 HAL
* Facade pattern

Todo:
https://www.beningo.com/how-to-write-epic-hardware-abstraction-layers-hal-in-c/#

## Plain function


```c++
struct GPIO {
	volatile uint32_t mode;
	volatile uint32_t input;
	volatile uint32_t output;
};

enum class ActiveLevel {
	High,
	Low
};

enum class Function {
	Input,
	Output,
	Alternative
}

void gpio_configure(GPIO* port, uint32_t pin, Function function, ActiveLevel active);
ActiveLevel gpio_state(GPIO* port, uint32_t pin);
void gpio_set_pin(GPIO* port, uint32_t pin);
void gpio_clear_pin(GPIO* port, uint32_t pin);
```

+ simple
+ easy to pass around
- easy to make mistake
- easy to misuse 

## OOP

```c++
class Gpio {
public:
	Gpio(port, pin, direction, active_level);

	active_level state();
	void set_pin();
	void clear_pin();
};
```

OOP in C: [Creating a GPIO HAL and Driver in C](https://www.embeddedrelated.com/showarticle/1638.php)

## OOP + interface

Seperate interface

## Template

```c++
class<Port, Pin> Gpio {
public:
	Gpio(direction, active_level);

	active_level state();
	void set_pin();
	void clear_pin();
};
```


## Template + static

```c++
class<Port, Pin> Gpio {
public:
	static active_level state();
	static void set_pin();
	static void clear_pin();
};
```

* https://modm.io/reference/module/modm-architecture-gpio/ ?

## Template + interface

```c++

class GpioInterface {
public:
	virtual active_level state();
	virtual void set_pin();
	virtual void clear_pin();
};

class<Port, Pin> Gpio : public GpioInterface {
public:
	active_level state() override;
	void set_pin() override;
	void clear_pin() override;
};

```

# static polymorphism

CRTP
