#pragma once

#include "Open.hpp"
#include "Service/AlgorithmState.hpp"

class PPFOpen : public Open<PPF> {
public:
    virtual void clear() = 0;
    virtual bool isDominated(const PPF &pair, int goalId) = 0;
    virtual std::vector<Node> getAllNodes() = 0;

    PPFOpen& withEpsDist(float epsDist) {
        epsDist_ = epsDist;
        return *this;
    }

    PPFOpen& withEpsTime(float epsTime) {
        epsTime_ = epsTime;
        return *this;
    }

protected:
    float epsDist_ = 0.f;
    float epsTime_ = 0.f;
};
