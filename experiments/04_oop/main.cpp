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


class Gpio {
public:
	Gpio(GPIO& port, uint32_t pin, Type function, ActiveLevel active)
    : m_port{port}
    , m_pin{pin}
    , m_function{function}
    , m_active{active}
    {
        m_port.mode |= (1 << m_pin);
    }

	ActiveLevel state() {
        const auto set = m_port.input & (1 << m_pin);
        return set ? ActiveLevel::High : ActiveLevel::Low;
    }

	void set_pin() {
        m_port.output |= (1 << m_pin);
    }

	void clear_pin() {
        m_port.output &= ~(1 << m_pin);
    }

private:
    GPIO& m_port;
    uint32_t m_pin;
    Type m_function;
    ActiveLevel m_active;
};



int main() {

    {
        GPIO portA = {};
        auto port = Gpio {portA, 2, Type::Output, ActiveLevel::High};
        port.set_pin();
    }

}
