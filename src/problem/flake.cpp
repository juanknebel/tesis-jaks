//
// Created by zero on 02/10/16.
//

#include "flake.h"

Flake::Flake() {
    this->id_ = -1;
    this->cost_ = -1.0;
    this->nodeId_ = "ERROR";
    this->cover_ = std::set<int> ();
}

Flake::Flake(int id, std::string nodeId, double cost, const std::set<int> &cover) {
    this->id_ = id;
    this->nodeId_ = nodeId;
    this->cost_ = cost;
    this->cover_ = std::set<int> (cover);
}

int Flake::getId() const{
    return this->id_;
}

std::string Flake::getNodeId() const {
    return this->nodeId_;
}

double Flake::getCost() const {
    return this->cost_;
}

const std::set<int> &Flake::getCover() const {
    return this->cover_;
}

Flake::~Flake() {

}

std::ostream &operator<<(std::ostream &stream, const Flake &flake) {
    stream << flake.getNodeId();
    return stream;
}

bool Flake::operator!=(const Flake &flake) const {
    return this->id_ != flake.id_;
}

bool Flake::operator==(const Flake &flake) const {
    return this->id_ == flake.id_;
}

bool Flake::operator<(const Flake& flake) const {
    return this->id_ < flake.id_;
}

double Flake::getCompat(const Flake& aFlake, const Flake& otherFlake, ProblemInstance& theProblem) {
    return theProblem.getCompat(aFlake.getId(), otherFlake.getId());
}