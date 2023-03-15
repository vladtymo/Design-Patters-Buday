#include <iostream>
#include <vector>
using namespace std;

// application objects
class Team
{
private:
    string name;
public:
    Team(string name) : name(name) { }
    void CompleteProject(vector<string>& requirements)
    {
        cout << "Complete the project with the " << requirements.size() << " requirements:\n";
        for (size_t i = 0; i < requirements.size(); i++)
        {
            cout << i+1 << ". " << requirements[i] << " has been completed!" << endl;
        }
    }
};
class Developer
{
public:
    void DoAllHardWork(string projectName)
    {
        cout << "Hero developer completed project " << projectName << " without requirements in manner of couple hours!\n";
    }
};

class Command
{
public:
    // Кожна Команда має метод для її запуску
    virtual void Execute() = 0;
};

// Приклад однієї із Команд до виконання
class YouAsProjectManagerCommand : public Command
{
private:
    Team* team;
    vector<string> requirements;

public:
    YouAsProjectManagerCommand() { }
    YouAsProjectManagerCommand(Team& team, vector<string>& requirements)
    {
        this->team = &team;
        this->requirements = requirements;
    }
    void Execute() override
    {
        // Реалізація делегує роботу до потрібного отримувача
        team->CompleteProject(requirements);
    }
};

// І ще один приклад
class HeroDeveloperCommand : public Command
{
private:
    Developer developer;
    string projectName;

public:
    HeroDeveloperCommand(Developer developer, string projectName)
    {
        this->developer = developer;
        this->projectName = projectName;
    }
    void Execute() override
    {
        // Реалізація делегує роботу до потрібного отримувача
        developer.DoAllHardWork(projectName);
    }
};

class Customer
{
private:
    vector<Command*> commands;

public:
    void AddCommand(Command* command)
    {
        commands.push_back(command);
    }
    void SignContractWithBoss()
    {
        for (auto command : commands)
        {
            command->Execute();
        }
    }
};

int main()
{
    // Замовник
    Customer customer;

    // Із певних міркуваня, бос завжди знає, що грошей стає тільки на бригаду UA
    Team team("UA");

    // Також бос отримав список вимог, що треба буде передати бригаді
    vector<string> requirements = {
        "Cool web site",
        "Ability to book beer on site"
    };

    // Ви повинні бути готові бути викликаними замовником
    Command* commandX = new YouAsProjectManagerCommand(team, requirements);

    // Передача вас у «найми» замовнику 
    customer.AddCommand(commandX);

    // В компанії також є програміст-герой, що кодує на швидкості світла
    Developer heroDeveloper;

    // Бос вирішив віддати йому проект A
    Command* commandA = new HeroDeveloperCommand(heroDeveloper, "Global Security");
    customer.AddCommand(commandA);

    // Як тільки замовник підписує контракт із вашим босом,
    // ваша бригада і програміст-герой готові виконати все, що треба
    // згідно вихідного коду контракту
    customer.SignContractWithBoss();
}
