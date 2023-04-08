#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Data_base;

const string CSV_EMPLOYEES = "employees.csv";
const string CSV_SALARY_CONFIGS = "salary_configs.csv";
const string CSV_TEAMS = "teams.csv";
const string CSV_WORKING_HOURS = "working_hours.csv";
const int FIRST_WORD = 0;
const int SECOND_WORD = 1;
const int THIRD_WORD = 2;
const int FOURTH_WORD = 3;
const int FIFTH_WORD = 4;
const int SIXTH_WORD = 5;
const int JUNK = 4;
const int LEVELS_COUNT = 4;

class Salary_config
{
public:
    int get_official_working_hours() { return official_working_hours; };
    int get_salary_per_hour() { return salary_per_hour; };
    int get_salary_per_extra_hour() { return salary_per_extra_hour; };
    string get_level_name() { return level; };
    int get_base_salary() {return base_salray;};
    int get_tax_percentage() {return tax_percentage;};
    void set_level(string the_level) { level = the_level; };
    void set_base_salary(int the_base_salary) { base_salray = the_base_salary; };
    void set_salary_per_hour(int the_salary_per_hour) { salary_per_hour = the_salary_per_hour; };
    void set_salary_per_extra_hour(int the_salary_per_extra_hour) { salary_per_extra_hour = the_salary_per_extra_hour; };
    void set_official_working_hours(int the_official_working_hours) { official_working_hours = the_official_working_hours; };
    void set_tax_percentage(int the_tax_percentage) { tax_percentage = the_tax_percentage; };

private:
    string level;
    int base_salray;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};

class Working_hour
{
public:
    int get_start_time() { return start; };
    int get_end_time() { return end; };
    int get_interval_duration() { return end - start; };
    int get_day() { return day; };
    long get_emp_id() { return employee_id; };
    void set_employee_id(long emp_id) { employee_id = emp_id; };
    void set_day(int the_day) { day = the_day; };
    void set_start_time(int start_time) { start = start_time; };
    void set_end_time(int end_time) { end = end_time; };

private:
    long employee_id;
    int day;
    int start;
    int end;
};

class Team
{
public:
    void set_team_id(long id) { team_id = id; };
    void set_team_lead_id(long lead_id) { team_lead_id = lead_id; };
    void set_member_ids(string members)
    {
        string word;
        stringstream members_stream(members);
        while (getline(members_stream, word, '$'))
        {
            member_ids.push_back(stoi(word));
        }
    };
    void set_bonus_min_working_hours(int bonus_min) { bonus_min_working_hours = bonus_min; };
    void set_bonus_working_hours_max_variance(double bonus_var) { bonus_working_hours_max_variance = bonus_var; };
    int get_team_id() { return team_id; };
    vector<long> get_member_ids() { return member_ids; };
    double get_bonus_working_hours_max_variance() { return bonus_working_hours_max_variance; };
    long get_lead_id() { return team_lead_id; };
    int get_bonus_min_working_hours() { return bonus_min_working_hours; };

private:
    long team_id;
    long team_lead_id;
    vector<long> member_ids;
    int bonus_min_working_hours;
    double bonus_working_hours_max_variance;
};

class Employee
{
public:
    int count_extra_working_hour();
    int count_salary();
    long get_emp_id() { return id; };
    string get_emp_name() { return name; };
    string get_emp_level() { return level; };
    int get_emp_age() { return age; };
    Salary_config *get_salary_config() { return employee_salary_config; };
    void set_emp_id(long the_emp_id) { id = the_emp_id; };
    void set_emp_name(string the_name) { name = the_name; };
    void set_emp_age(int the_age) { age = the_age; };
    void set_emp_level(string the_level) { level = the_level; };
    void find_salary_config(Data_base *all_information);

private:
    long id;
    string name;
    int age;
    string level;
    Salary_config *employee_salary_config = new Salary_config;
};

int Employee::count_extra_working_hour()
{
    int total_working_hours = 0;
    // for (int i = 0; i < employee_working_periods.size(); i++)
    //     total_working_hours += employee_working_periods[i]->get_end_time() - employee_working_periods[i]->get_start_time();
    // int official_working_hours = employee_salary_config->get_official_working_hours();
    // return total_working_hours - official_working_hours;
}

int Employee::count_salary()
{
    int extra_working_hours = this->count_extra_working_hour();
    int official_working_hours = employee_salary_config->get_official_working_hours();
    int salary_per_hour = employee_salary_config->get_salary_per_hour();

    if (extra_working_hours > 0)
        return official_working_hours * salary_per_hour + extra_working_hours * salary_per_hour;
    else
        return (extra_working_hours + official_working_hours) * salary_per_hour;
};

class Data_base
{
public:
    Data_base(int a = JUNK);
    void read_csv_teams();
    void read_csv_employees();
    void read_csv_salary_configs();
    void read_csv_working_hours();
    vector<Team> get_the_teams() { return all_teams; };
    vector<Working_hour> get_the_working_hours() { return all_working_hours; };
    vector<Salary_config *> get_the_salary_configs_pointers();
    vector<Salary_config> get_the_salary_configs() { return all_salary_configs; };

    vector<Employee> get_the_employees() { return all_employees; };

private:
    vector<Employee> all_employees;
    vector<Team> all_teams;
    vector<Salary_config> all_salary_configs;
    vector<Working_hour> all_working_hours;
};
vector<Salary_config *> Data_base::get_the_salary_configs_pointers()
{
    vector<Salary_config *> pointers;
    for (int i = 0; i < LEVELS_COUNT; i++)
        pointers.push_back(&(all_salary_configs[i]));
    return pointers;
};

void Employee::find_salary_config(Data_base *all_information)
{
    string level_name = this->level;
    vector<Salary_config *> all_salary_configs = all_information->get_the_salary_configs_pointers();
    for (int i = 0; i < LEVELS_COUNT; i++)
    {
        string config_level_name = all_salary_configs[i]->get_level_name();

        if (config_level_name == level_name)
        {
            employee_salary_config = all_salary_configs[i];
        }
    }
}

Data_base::Data_base(int a)
{
    this->read_csv_teams();
    this->read_csv_working_hours();
    this->read_csv_salary_configs();
    this->read_csv_employees();
}

vector<string> init_all_words(string line)
{
    stringstream working_hour_stream(line);
    string word;
    vector<string> all_words;
    while (getline(working_hour_stream, word, ','))
        all_words.push_back(word);
    return all_words;
}

Team set_team_id(Team new_team, vector<string> all_words)
{
    long id = stoi(all_words[FIRST_WORD]);
    new_team.set_team_id(id);
    return new_team;
}

Team set_lead_id(Team new_team, vector<string> all_words)
{

    long lead_id = stoi(all_words[SECOND_WORD]);
    new_team.set_team_lead_id(lead_id);
    return new_team;
}

Team set_member_ids(Team new_team, vector<string> all_words)
{

    string memebr_ids = all_words[THIRD_WORD];
    new_team.set_member_ids(memebr_ids);
    return new_team;
}

Team set_bonus_min(Team new_team, vector<string> all_words)
{

    int bonus_min = stoi(all_words[FOURTH_WORD]);
    new_team.set_bonus_min_working_hours(bonus_min);
    return new_team;
}

Team set_bonus_var(Team new_team, vector<string> all_words)
{

    double bonus_var;
    istringstream fifth_word_stream(all_words[FIFTH_WORD]);
    fifth_word_stream >> bonus_var;
    new_team.set_bonus_working_hours_max_variance(bonus_var);
    return new_team;
}

void Data_base::read_csv_teams()
{
    ifstream csv_teams(CSV_TEAMS);
    string line;
    getline(csv_teams, line);
    while (getline(csv_teams, line))
    {
        Team new_team;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_team = set_team_id(new_team, all_words);
        new_team = set_lead_id(new_team, all_words);
        new_team = set_member_ids(new_team, all_words);
        new_team = set_bonus_min(new_team, all_words);
        new_team = set_bonus_var(new_team, all_words);

        all_teams.push_back(new_team);
    }
}

Working_hour set_emp_id(Working_hour new_working_hour, vector<string> all_words)
{
    long emp_id = stoi(all_words[FIRST_WORD]);
    new_working_hour.set_employee_id(emp_id);
    return new_working_hour;
}

Working_hour set_day(Working_hour new_working_hour, vector<string> all_words)
{
    int the_day = stoi(all_words[SECOND_WORD]);
    new_working_hour.set_day(the_day);
    return new_working_hour;
}

Working_hour set_interval_start_time(Working_hour new_working_hour, vector<string> all_words)
{
    int start_time = stoi(all_words[THIRD_WORD].substr(0, all_words[THIRD_WORD].find('-')));
    new_working_hour.set_start_time(start_time);
    return new_working_hour;
}

Working_hour set_interval_end_time(Working_hour new_working_hour, vector<string> all_words)
{
    int end_time = stoi(all_words[THIRD_WORD].substr(all_words[THIRD_WORD].find('-') + 1));
    new_working_hour.set_end_time(end_time);
    return new_working_hour;
}

void Data_base::read_csv_working_hours()
{
    ifstream csv_working_hours(CSV_WORKING_HOURS);
    string line;
    getline(csv_working_hours, line);
    while (getline(csv_working_hours, line))
    {
        Working_hour new_working_hour;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_working_hour = set_emp_id(new_working_hour, all_words);
        new_working_hour = set_day(new_working_hour, all_words);
        new_working_hour = set_interval_start_time(new_working_hour, all_words);
        new_working_hour = set_interval_end_time(new_working_hour, all_words);

        all_working_hours.push_back(new_working_hour);
    }
}

Salary_config set_level(Salary_config new_salary_config, vector<string> all_words)
{
    string level = all_words[FIRST_WORD];
    new_salary_config.set_level(level);
    return new_salary_config;
}

Salary_config set_base_salary(Salary_config new_salary_config, vector<string> all_words)
{
    int base_salary = stoi(all_words[SECOND_WORD]);
    new_salary_config.set_base_salary(base_salary);
    return new_salary_config;
}

Salary_config set_salary_per_hour(Salary_config new_salary_config, vector<string> all_words)
{
    int salary_per_hour = stoi(all_words[THIRD_WORD]);
    new_salary_config.set_salary_per_hour(salary_per_hour);
    return new_salary_config;
}

Salary_config set_salary_per_extra_hour(Salary_config new_salary_config, vector<string> all_words)
{
    int salary_per_extra_hour = stoi(all_words[FOURTH_WORD]);
    new_salary_config.set_salary_per_extra_hour(salary_per_extra_hour);
    return new_salary_config;
}

Salary_config set_official_working_hours(Salary_config new_salary_config, vector<string> all_words)
{
    int official_working_hours = stoi(all_words[FIFTH_WORD]);
    new_salary_config.set_official_working_hours(official_working_hours);
    return new_salary_config;
}

Salary_config set_tax_percentage(Salary_config new_salary_config, vector<string> all_words)
{
    int tax_percentage = stoi(all_words[SIXTH_WORD]);
    new_salary_config.set_tax_percentage(tax_percentage);
    return new_salary_config;
}

void Data_base::read_csv_salary_configs()
{
    ifstream csv_salary_configs(CSV_SALARY_CONFIGS);
    string line;
    getline(csv_salary_configs, line);
    while (getline(csv_salary_configs, line))
    {
        Salary_config new_salary_config;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_salary_config = set_level(new_salary_config, all_words);
        new_salary_config = set_base_salary(new_salary_config, all_words);
        new_salary_config = set_salary_per_hour(new_salary_config, all_words);
        new_salary_config = set_salary_per_extra_hour(new_salary_config, all_words);
        new_salary_config = set_official_working_hours(new_salary_config, all_words);
        new_salary_config = set_tax_percentage(new_salary_config, all_words);

        all_salary_configs.push_back(new_salary_config);
    }
}

Employee set_emp_id(Employee new_employee, vector<string> all_words)
{
    long id = stoi(all_words[FIRST_WORD]);
    new_employee.set_emp_id(id);
    return new_employee;
}

Employee set_emp_name(Employee new_employee, vector<string> all_words)
{
    string name = all_words[SECOND_WORD];
    new_employee.set_emp_name(name);
    return new_employee;
}

Employee set_emp_age(Employee new_employee, vector<string> all_words)
{
    int age = stoi(all_words[THIRD_WORD]);
    new_employee.set_emp_age(age);
    return new_employee;
}

Employee set_emp_level(Employee new_employee, vector<string> all_words)
{
    string level = all_words[FOURTH_WORD];
    new_employee.set_emp_level(level);
    return new_employee;
}

void Data_base::read_csv_employees()
{
    ifstream csv_employees(CSV_EMPLOYEES);
    string line;
    getline(csv_employees, line);
    while (getline(csv_employees, line))
    {
        Employee new_employee;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_employee = set_emp_id(new_employee, all_words);
        new_employee = set_emp_name(new_employee, all_words);
        new_employee = set_emp_age(new_employee, all_words);
        new_employee = set_emp_level(new_employee, all_words);
        new_employee.find_salary_config(this);
        new_employee.get_salary_config()->get_level_name();

        all_employees.push_back(new_employee);
    }
}

void get_input()

int main()
{
    Data_base all_information(JUNK);
    vector<Team> ali = all_information.get_the_teams();
    return 0;
}

    // cout << ali[0].get_team_id() << " "
    //      << ali[0].get_lead_id() << " "
    //      << ali[0].get_bonus_working_hours_max_variance() << " "
    //      << ali[0].get_member_ids()[0] << " "
    //      << ali[0].get_bonus_min_working_hours() << endl;
    // vector<Working_hour> bli = all_information.get_the_working_hours();
    // cout << bli[7].get_start_time() << " "
    //      << bli[7].get_end_time() << " "
    //      << bli[7].get_emp_id() << " "
    //      << bli[7].get_day() << endl;
    // vector<Salary_config> gli = all_information.get_the_salary_configs();
    // cout << gli[2].get_level_name() << " "
    // << gli[2].get_official_working_hours() << " "
    // << gli[2].get_salary_per_extra_hour() << " "
    // << gli[2].get_salary_per_hour() << " "
    // << gli[2].get_tax_percentage() << " "
    // << gli[2].get_base_salary() << endl;
    // vector<Salary_config *> nli = all_information.get_the_salary_configs_pointers();
    // cout << nli[2]->get_level_name() << " "
    // << nli[2]->get_base_salary() << endl;
    // vector<Employee> cli = all_information.get_the_employees();
    // cout << cli[2].get_salary_config()->get_level_name() << " "
    // << cli[2].get_emp_age() << " "
    // << cli[2].get_emp_id() << " "
    // << cli[2].get_emp_level() << " "
    // << cli[2].get_emp_name() << endl;