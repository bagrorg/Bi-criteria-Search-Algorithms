#pragma once

class PPFOpen : public Open<PPF> {
public:
    virtual void clear() = 0;
    virtual bool isDominated(const PPF &pair) = 0;
};

class DummyPPFOpen : public PPFOpen {
public:
    size_t size() const override {
        return 0;
    }

    void add(PPF n) override {

    }

    bool isEmpty() const override {
        return false;
    }

    PPF getBest() override {
        return PPF(0, Node(), Node());
    }

    void clear() override {

    }

    bool isDominated(const PPF &pair) override {
        return false;
    }
};
