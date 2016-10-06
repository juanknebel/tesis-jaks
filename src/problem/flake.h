//
// Created by zero on 02/10/16.
//

#ifndef TESIS_JAKS_EXE_FLAKE_H
#define TESIS_JAKS_EXE_FLAKE_H

#include <string>
#include <set>
#include "problemInstance.h"

class Flake {
private:
    int id_;
    std::string nodeId_;
    double cost_;
    std::set<int> cover_;

public:
    Flake();
    Flake(int id, std::string nodeId, double cost, const std::set<int>& cover);
    int getId() const;
    std::string getNodeId() const;
    double getCost() const;
    const std::set<int>& getCover() const;
    ~Flake();
    friend std::ostream& operator<< (std::ostream& stream,const Flake& flake);
    bool operator==(const Flake& flake) const;
    bool operator!=(const Flake& flake) const;
    bool operator<(const Flake& flake) const;
    friend std::ostream& operator<< (std::ostream& stream,const Flake& flake);
    static double getCompat(const Flake& aFlake, const Flake& otherFlake, ProblemInstance& theProblem);
};


#endif //TESIS_JAKS_EXE_FLAKE_H
