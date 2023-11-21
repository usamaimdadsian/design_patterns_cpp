/*
    1. High-level modules should not depend on low-level modules. Both should depend on abastractions.
    2. Abstractions should not depend on details. Details should depend on abastractions.

*/
#include <iostream>
#include <string>
// #include <memory>
#include <boost/di.hpp>


using namespace std;

struct ILogger
{
    virtual ~ILogger() {} // destructor
    virtual void Log(const string &s) = 0;
};

struct ConsoleLogger : ILogger
{
    ConsoleLogger() {}
    void Log(const string &s) override
    {
        cout << "LOG: " << s.c_str() << endl;
    }
};

class Reporting
{
    ILogger &logger;

public:
    Reporting(ILogger &logger) : logger{logger} {}
    void prepare_report()
    {
        // logger.log_info("Preparing the info");
    }
};

struct Engine
{
    float volume = 5;
    int horse_power = 400;

    friend ostream &operator<<(ostream &os, const Engine &obj)
    {
        return os << "Volume: " << obj.volume << " horse_power: " << obj.horse_power;
    }
};


struct Car
{
    unique_ptr<Engine> engine;
    shared_ptr<ILogger> logger;

    Car(unique_ptr<Engine> engine, const shared_ptr<ILogger> &logger): engine{move(engine)},logger{logger}{
        logger->log("Making a Car.");
    }

    friend ostream& operator<< (ostream &os, const Car &obj){
        return os << "car with engine: " << *obj.engine;
    }
};


int main(){
    auto injector = di::make_injector(
        di::bind<ILogger>().to<ConsoleLogger>()
    );

    auto car = injector.create<shared_ptr<Car>>();
    
}