#pragma once

class PPFOpen : public Open<PPF> {
public:
    virtual void clear() = 0;
    virtual bool isDominated(const PPF &pair) = 0;
};
