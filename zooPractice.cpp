#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;
class Animal {
protected:
    string name;
    int age;
    string species;
public:
    Animal(string n, int a, string s) : name(n), age(a), species(s) {}
    virtual ~Animal() {}
    string getName() { return name; }
    void setName(string n) { name = n; }
    int getAge() { return age; }
    void setAge(int a) { age = a; }
    string getSpecies() { return species; }
    virtual string makeInfoString() {
        return name + ", " + to_string(age) + " years old";
    }
};
class Hyena : public Animal {
    string noiseType;
public:
    Hyena(string n, int a) : Animal(n, a, "Hyena"), noiseType("laugh") {}
    string getNoise() { return noiseType; }
};
class Lion : public Animal {
    string habitat;
public:
    Lion(string n, int a) : Animal(n, a, "Lion"), habitat("Savanna") {}
    string getHabitat() { return habitat; }
};
class Tiger : public Animal {
    string stripePattern;
public:
    Tiger(string n, int a) : Animal(n, a, "Tiger"), stripePattern("Bold") {}
    string getPattern() { return stripePattern; }
};
class Bear : public Animal {
    bool isGrizzly;
public:
    Bear(string n, int a) : Animal(n, a, "Bear"), isGrizzly(true) {}
    bool checkGrizzly() { return isGrizzly; }
};
int main() {
    vector<Animal*> zooAnimals;
    map<string, int> speciesCount;
    ifstream inFile("arrivingAnimals.txt");
    if (!inFile) {
        cout << "Error opening input file." << endl;
        return 1;
    }
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, species, ageStr;
        getline(ss, ageStr, ',');
        getline(ss, name, ',');
        getline(ss, species);
        if (!species.empty() && species[0] == ' ') species.erase(0, 1);
        if (!name.empty() && name[0] == ' ') name.erase(0, 1);
        int age = stoi(ageStr);
        if (species == "Hyena") zooAnimals.push_back(new Hyena(name, age));
        else if (species == "Lion") zooAnimals.push_back(new Lion(name, age));
        else if (species == "Tiger") zooAnimals.push_back(new Tiger(name, age));
        else if (species == "Bear") zooAnimals.push_back(new Bear(name, age));
        speciesCount[species]++;
    }
    inFile.close();
    ofstream outFile("newAnimals.txt");
    outFile << "Zoo Arrival Report" << endl;
    outFile << "==================" << endl;
    for (auto const& [type, count] : speciesCount) {
        outFile << "\nSpecies: " << type << " (Total: " << count << ")" << endl;
        for (Animal* a : zooAnimals) {
            if (a->getSpecies() == type) {
                outFile << " - " << a->makeInfoString() << endl;
            }
        }
    }

    outFile.close();
    for (Animal* a : zooAnimals) delete a;
    cout << "Report generated successfully in newAnimals.txt" << endl;
    return 0;
}
