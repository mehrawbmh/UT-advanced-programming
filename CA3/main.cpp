#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string PATIENTS_FILE = "patients.csv";
const string DOCTORS_FILE = "doctors.csv";
const string DISEASES_FILE = "diseases.csv";

const vector<string> weekDays = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};

struct Specialty {
    string name;
    vector<string> diseases;
};

struct WorkDay {
    int weekDayNumber; //starting from Saturday (0) to FriDay (6)
    int entranceHour;
    int exitHour;
    int visitCount = 0;
};

struct PatientArrivalTime {
    int weekDayNumber;
    int hour;
};

struct PatientVisitTime {
    int weekDayNumber;
    int hour;
    int minutes;
};

struct Doctor {
    string name;
    Specialty spec;
    int visitFee;
    int visitDuration;
    int avgWaitTime;
    vector<WorkDay> workDays;
};

struct Visit {
    Doctor assignedDoctor;
    PatientVisitTime visitTime;
    int visitCount;
};

struct Patient {
    string name;
    string medicalIssue;
    PatientArrivalTime arrivalTime;
    bool hasSetVisit = false;
    Visit visit;
};

bool comparePatientsByName(const Patient &p1, const Patient &p2) {
    return p1.name.compare(p2.name) < 0;
}

//this is the main sorting logic for patients
bool sortPatientsByVisitRules(const Patient &p1, const Patient &p2) {
    if (p1.arrivalTime.weekDayNumber == p2.arrivalTime.weekDayNumber) {
        if (p1.arrivalTime.hour == p2.arrivalTime.hour) {
            return p1.name.compare(p2.name) < 0;
        } else {
            return p1.arrivalTime.hour < p2.arrivalTime.hour;
        }
    }

    return p1.arrivalTime.weekDayNumber < p2.arrivalTime.weekDayNumber;
}

int findTotalVisitsDoctorCanHaveInDay(const Doctor &doctor, const WorkDay &workDay) {
    return (workDay.exitHour - workDay.entranceHour) * 60 / doctor.visitDuration;
}

int findFirstEmptyDayForDoctorToVisit(const Doctor &d) {
    for (const WorkDay &workDay: d.workDays) {
        int totalVisitInDay = findTotalVisitsDoctorCanHaveInDay(d, workDay);
        if (totalVisitInDay != workDay.visitCount) {
            return workDay.weekDayNumber;
        }
    }
    return INT32_MAX;
}

int findFirstEmptyTimeAfterEntranceForDoctor(const Doctor &d, int weekDayNumber) {
    for (const WorkDay &workDay: d.workDays) {
        if (workDay.weekDayNumber == weekDayNumber) {
            return workDay.entranceHour * 60 + workDay.visitCount * d.visitDuration;
        }
    }
    return INT32_MAX;
}

// this is the main sorting logic of doctors
bool compareDoctorsByFirstEmptyTimeAndVisitFeeAndAvgWaitTimeAndName(const Doctor &d1, const Doctor &d2) {
    int d1FirstEmptyDay = findFirstEmptyDayForDoctorToVisit(d1);
    int d2FirstEmptyDay = findFirstEmptyDayForDoctorToVisit(d2);

    if (d1FirstEmptyDay == d2FirstEmptyDay) {
        int d1FirstEmptyTimeInMinutes = findFirstEmptyTimeAfterEntranceForDoctor(d1, d1FirstEmptyDay);
        int d2FirstEmptyTimeInMinutes = findFirstEmptyTimeAfterEntranceForDoctor(d2, d2FirstEmptyDay);
        if (d1FirstEmptyTimeInMinutes != d2FirstEmptyTimeInMinutes) {
            return d1FirstEmptyTimeInMinutes < d2FirstEmptyTimeInMinutes;
        }
    } else {
        return d1FirstEmptyDay < d2FirstEmptyDay;
    }

    if (d1.visitFee == d2.visitFee) {
        if (d1.avgWaitTime == d2.avgWaitTime) {
            return d1.name.compare(d2.name) < 0;
        } else {
            return d1.avgWaitTime < d2.avgWaitTime;
        }
    }

    return d1.visitFee < d2.visitFee;
}

bool compareWeekDaysByNumberOfWeekDay(const WorkDay &w1, const WorkDay &w2) {
    return w1.weekDayNumber < w2.weekDayNumber;
}

int getNumberOfWeekDayFromItsName(const string &name) {
    for (int i = 0; i < weekDays.size(); ++i) {
        if (name == weekDays[i])
            return i;
    }
    return -1;
}

string getWeekDayStringFromItsNumber(const int &number) {
    if (number >= 0 && number < weekDays.size()) {
        return weekDays[number];
    }
    return "Invalid";
}

vector<string> splitString(const string &input, char delim = ',') {
    string element;
    stringstream ss(input);
    vector<string> out;

    while (getline(ss, element, delim)) {
        out.push_back(element);
    }

    return out;
}

vector<string> readLinesFromCSV(const string &fileName, vector<string> &columns) {
    ifstream file(fileName);
    string line;
    vector<string> lines;

    if (getline(file, line)) {
        columns = splitString(line);
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

vector<vector<string>> getCSVList(const string &fileName, vector<string> &columns) {
    vector<vector<string>> output;
    vector<string> lines = readLinesFromCSV(fileName, columns);

    for (const string &line: lines) {
        output.push_back(splitString(line));
    }

    return output;
}

vector<Patient> getPatients(const string &fileName) {
    vector<string> columns;
    vector<vector<string>> patientsList = getCSVList(fileName, columns);
    vector<Patient> final;

    for (const vector<string> &patientVector: patientsList) {
        vector<string> timings = splitString(patientVector[2], '-');
        struct PatientArrivalTime pv = {getNumberOfWeekDayFromItsName(timings[0]), stoi(timings[1])};
        struct Patient p1 = {patientVector[0], patientVector[1], pv};
        final.push_back(p1);
    }

    return final;
}

Specialty findSpecialtyByName(const vector<Specialty> &specs, const string &name) {
    for (auto spec: specs) {
        if (spec.name == name) {
            return spec;
        }
    }
    // it is guaranteed that all specialties of doctors exist in diseases csv file. so it should not reach here at all
    return Specialty{};
}

vector<WorkDay> convertToWorkDayAndSortByDay(const vector<string> &input) {
    vector<WorkDay> final;
    for (const string &workDaySting: input) {
        vector<string> timeParts = splitString(workDaySting, '-');
        struct WorkDay wd = {
                getNumberOfWeekDayFromItsName(timeParts[0]),
                stoi(timeParts[1]),
                stoi(timeParts[2]),
                0
        };
        final.push_back(wd);
    }

    sort(final.begin(), final.end(), compareWeekDaysByNumberOfWeekDay);
    return final;
}

vector<Doctor> getDoctors(const string &fileName, const vector<Specialty> &specs) {
    vector<string> columns;
    vector<vector<string>> doctorsList = getCSVList(fileName, columns);
    vector<Doctor> final;

    for (const vector<string> &doctorVector: doctorsList) {
        struct Doctor d1 = {
                doctorVector[0],
                findSpecialtyByName(specs, doctorVector[1]),
                stoi(doctorVector[2]),
                stoi(doctorVector[3]),
                stoi(doctorVector[4]),
                convertToWorkDayAndSortByDay(splitString(doctorVector[5], '$'))
        };
        final.push_back(d1);
    }
    return final;
}

vector<Specialty> getSpecialties(const string &fileName) {
    vector<string> columns;
    vector<vector<string>> specsList = getCSVList(fileName, columns);
    vector<Specialty> final;

    for (const vector<string> &specVector: specsList) {
        struct Specialty spec = {specVector[0], splitString(specVector[1], '$')};
        final.push_back(spec);
    }
    return final;
}

bool setAppointment(Patient &patient, const Doctor &selectedDoctor, vector<Doctor> &doctors) {
    for (Doctor &doctor: doctors) {
        if (doctor.name == selectedDoctor.name) {
            for (WorkDay &workDay: doctor.workDays) {
                if (findTotalVisitsDoctorCanHaveInDay(doctor, workDay) != workDay.visitCount) {
                    int visitTimeInMinutes = workDay.entranceHour * 60 + workDay.visitCount * doctor.visitDuration;
                    int visitTimeHour = visitTimeInMinutes / 60;
                    workDay.visitCount += 1;
                    patient.visit = {
                            doctor,
                            {workDay.weekDayNumber, visitTimeHour, visitTimeInMinutes % 60},
                            workDay.visitCount
                    };
                    return true;
                }
            }
        }
    }
    return false;
}

vector<Doctor> getEligibleDoctorsForPatient(const Patient &patient, const vector<Doctor> &doctors) {
    vector<Doctor> final;
    string issue = patient.medicalIssue;
    for (const Doctor &doc: doctors) {
        for (const string &medIssue: doc.spec.diseases) {
            if (medIssue == issue) {
                final.push_back(doc);
                break;
            }
        }
    }

    sort(final.begin(), final.end(), compareDoctorsByFirstEmptyTimeAndVisitFeeAndAvgWaitTimeAndName);
    return final;
}

string convertToStandardTime(int hour, int minutes) {
    string hourString = hour < 10 ? "0" + to_string(hour) : to_string(hour);
    string minutesString = minutes < 10 ? "0" + to_string(minutes) : to_string(minutes);

    return hourString + ":" + minutesString;
}

int main() {
    vector<Patient> patients = getPatients(PATIENTS_FILE);
    vector<Specialty> specs = getSpecialties(DISEASES_FILE);
    vector<Doctor> doctors = getDoctors(DOCTORS_FILE, specs);

    bool printDash = false;

    sort(patients.begin(), patients.end(), sortPatientsByVisitRules);

    for (Patient &patient: patients) {
        Doctor candidateDoctor = getEligibleDoctorsForPatient(patient, doctors)[0];
        // it is guaranteed that at least one eligible doctor exists per patient. so we won't check empty vector case.

        patient.hasSetVisit = setAppointment(patient, candidateDoctor, doctors);
    }

    sort(patients.begin(), patients.end(), comparePatientsByName);
    for (const Patient &patient: patients) {
        if (printDash) {
            cout << "----------\n";
        }
        printDash = true;

        if (patient.hasSetVisit) {
            cout << "Name: " << patient.name << endl;
            cout << "Doctor: " << patient.visit.assignedDoctor.name << endl;
            cout << "Visit: " << getWeekDayStringFromItsNumber(patient.visit.visitTime.weekDayNumber) << " "
                 << patient.visit.visitCount << " "
                 << convertToStandardTime(patient.visit.visitTime.hour, patient.visit.visitTime.minutes) << endl;
            cout << "Charge: " << patient.visit.assignedDoctor.visitFee << endl;
        } else {
            cout << "Name: " << patient.name << endl;
            cout << "No free time" << endl;
        }
    }
}
