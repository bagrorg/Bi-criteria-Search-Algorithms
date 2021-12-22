#pragma once

class PPFClosed : public Closed<PPF> {
public:
    virtual void clear() = 0;
};

class DummyPPFClosed : public PPFClosed {
public:
    size_t size() const override {
        return 0;
    }

    void add(PPF n) override {

    }

    bool wasExpanded(const PPF &n) const override {
        return false;
    }

    void clear() override {

    }
};
