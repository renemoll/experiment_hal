#include <cinttypes>

struct GPIO {
	volatile uint32_t mode;
	volatile uint32_t input;
	volatile uint32_t output;
};

enum class ActiveLevel {
	High,
	Low
};

enum class Type {
	Input,
	Output,
	Alternative
};


void gpio_configure(GPIO& port, uint32_t pin, Type function, ActiveLevel active) {
    port.mode |= (1 << pin);
    // where to set the level?
}

ActiveLevel gpio_state(GPIO& port, uint32_t pin) {
    const auto set = port.input & (1 << pin);
    return set ? ActiveLevel::High : ActiveLevel::Low;
}

void gpio_set_pin(GPIO& port, uint32_t pin) {
    port.output |= (1 << pin);
}

void gpio_clear_pin(GPIO& port, uint32_t pin) {
    port.output &= ~(1 << pin);
}



int main() {
    {
        GPIO portA = {};
        gpio_configure(portA, 2, Type::Output, ActiveLevel::High);
        gpio_set_pin(portA, 2);
    }
}
