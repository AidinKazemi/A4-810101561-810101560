#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const string CSV_EMPLOYEES = "employees.csv";
const string CSV_SALARY_CONFIGS= "salary_configs.csv";
const string CSV_TEAMS = "teams.csv";
const string CSV_WORKING_HOURS = "working_hours.csv";

class Employee;
class Working_hour;
class Team;
class Salary_config;

class Data_base
{
    public:
    Data_base(fstream , );
private:
    vector<Employee> all_employees;
    vector<Team> all_teams;
    vector<Salary_config> all_salary_configs;
    vector<Working_hour> all_working_hours;
};

class Employee
{
public:
    int count_extra_working_hour();
    int count_salary();

private:
    long id;
    string name;
    int age;
    string level;
    vector<Working_hour *> employee_working_periods;
    Salary_config *employee_salary_config;
};

class Working_hour
{
public:
    int get_start_time() {return start;};
    int get_end_time () {return end;};
private:
    long employee_id;
    int day;
    int start;
    int end;
};

class Team
{
private:
    int team_id;
    int team_lead_id;
    string member_ids;
    int bonus_min_working_hours;
    int bonus_working_hours_max_variance;
    int bonus;
};

class Salary_config
{
public:
    int get_official_working_hours() { return official_working_hours; };
    int get_salary_per_hour() { return salary_per_hour; };
    int get_salary_per_extra_hour() { return salary_per_extra_hour; };

private:
    string level;
    int base_salray;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};



int main()
{
    fstream csv_employees(CSV_EMPLOYEES);
    Data_base all_information();
    return 0;
}