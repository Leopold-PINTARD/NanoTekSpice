#include <memory>
#include <vector>
#include <cstdint>
#include <string>

enum Tristate {
    Undefined = (-true),
    True = true,
    False = false
};

class Pin {
    public:
        enum Type {
            Input = 0,
            Output = 1
        };
        Pin(Pin::Type type) : status(Undefined), pinType(type) {}
        Pin(const Pin &) = delete;
        ~Pin() {}
        enum Tristate getStatus() const {return status;}
        size_t getLinkedPin(size_t pin) const {return linkedPins[pin];}
        std::shared_ptr<IComponent> getLinkedComp(size_t comp) const {return linkedComps[comp];}
        void setStatus(enum Tristate val) {status = val;}
        void addLinkedComp(IComponent &comp, size_t pin) {
            linkedComps.push_back(std::shared_ptr<IComponent>(&comp));
            linkedPins.push_back(pin);
        }
        bool containsLinked(std::shared_ptr<IComponent> linkedComp, size_t linkedPin) {
            for (int i = 0; i != this->linkedPins.size(); i++) {
                if (this->linkedPins[i] == linkedPin && this->linkedComps[i] == linkedComp)
                    return true;
            }
            return false;
        }
        Type getType() const {return pinType;}
    private:
        std::vector<std::shared_ptr<IComponent>> linkedComps;
        std::vector<size_t> linkedPins;
        enum Tristate status;
        Type pinType;
};

class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual Tristate compute(size_t pin) = 0;
        virtual void simulate(size_t tick) = 0;
        virtual void setLink(size_t thisPin, IComponent &other,
            size_t otherPin) = 0;
        virtual enum Tristate getLink(std::size_t pin) const = 0;
        virtual const Pin &getPin(size_t pin) const = 0;

};

class AComponent : public IComponent {
    public:
        //Nothing happens by default, the simulation must be implemented on a case by case basis
        virtual void simulate(size_t tick) override {}
        //If a link is set on an output pin, the link is outgoing, if it's set on an input pin, the link is incoming
        virtual void setLink(size_t thisPin, IComponent &other,
            size_t otherPin) override {
            this->pins[thisPin].addLinkedComp(other, otherPin);
            if (this->pins[thisPin].containsLinked(std::shared_ptr<IComponent>(&other), otherPin))
                return;
            other.setLink(otherPin, *this, thisPin);
        };
        enum Tristate getLink(std::size_t pin) const override {
            if (pins[pin].getType() == Pin::Input)
                return pins[pin].getLinkedComp(0)->compute(pins[pin].getLinkedPin(0));
        };
        virtual const Pin &getPin(size_t pin) const override {return this->pins[pin];}
    protected:
        std::string compName;
        std::vector<Pin> pins;
};

class ADoor : public AComponent {
    public:
        ADoor() {
            Pin input(Pin::Input);
            Pin output(Pin::Output);

            for (int i = 0; i < 2; i++)
                pins.push_back(input);
            pins.push_back(output);
        }
};

class And : public ADoor {
    public:
        enum Tristate compute(size_t pin) {
        }
};
