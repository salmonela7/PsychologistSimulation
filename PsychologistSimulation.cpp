/*
10.Apsilankymas pas psichologą (ADT: eilė, ilgas sveikas skaičius). Psichologo konsultacijas teikia keli specialistai, dalis jų (n) formuoja
terapines grupes iš k žmonių (terapijos trukmė GrT valandų), kiti (m) priima pacientus individualiai (Terapijos trukmė InT valandų). Kiekvienas
naujai atėjęs pacientas (naujo paciento pasirodymo tikimybė p1, pakartotinai pacientai ateina po tam tikro laiko d) gali pasirinkti ar apsilankyti
pas psichologą, teikiantį individualią paslaugą, ar pas grupines konsultacijas. Kol pas psichologą teikiantį grupinę konsultaciją susirenka grupė į
ją pretenduojantys pacientai turi laukti. Pakartotinai atėję pacientai, pas savo psichologą gali rinktis ir mažesnėm grupėm, tačiau negali eiti kartu
su naujokais. Yra pastebėta, kad individualiai priimami pacientai sveiksta greičiau, nei dirbantys grupėje (jiems reikia mažiau konsultacijų),
tačiau pasitaiko išimčių, dėl socialinio bendravimo faktoriaus, kai kurie pacientai (tikimybė p2) pasveiksta h procentų greičiau, nei konsultuodami
individualiai. Individuali konsultacija kainuoja InK litų, grupinė GrK litų. Reikia įvetinti, kokį terapijos metodą turėtų pasirinkti pacientas optimizuodamas
savo išteklius, bei kiek ir kokių specialistų turėtų samdyti sveikatos priežiūros įstaiga.
*/

#include "Bigint.cpp"
#include "Queue.cpp"
#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <queue>
#include <list>
#include <algorithm>


using namespace std;

int therapyGroup = 10;
int smallTherapyGroup = 5;
int thNeedInd = 5;
int thNeedGrp = 6;
int indTherLength = 20;
int grpTherLength = 40;
int waitingT = 40;
int waitingForFirstTherapy = 0;
int waitingForTherapy = 0;

class Patient
{
    bool waiting;
public:
    int arrivalTime;
    int isbusy;
    int therapyNeeded;
    bool individual;
    int therapyCount;
    int waitingTime;
    int patientID;
    bool waitFirst;
    Patient(int at = 0, bool bs = false, bool indi = false, int tn = 0, int wt = 0, int id = 0, bool wf = false) : arrivalTime (at), isbusy (bs), individual (indi), therapyNeeded (tn), waitingTime(wt), patientID(id), waitFirst(wf), waiting(false), therapyCount(0) {}

    int getTherapyLength()
    {
        if (this->individual)
        {
            return indTherLength;
        }
        else if(!this->individual)
        {
            return grpTherLength;
        }
    }
    void waitForFirst(bool wait)
    {
        waitFirst = wait;
    }
    bool getWaitForFirst()
    {
        return waitFirst;
    }
    int getPatientID()
    {
        return patientID;
    }
    void setWaitingTime(int time)
    {
        waitingTime = time;
    }
    int getWaitingTime()
    {
        return waitingTime;
    }
    bool isWaiting()
    {
        return waiting;
    }
    void setWaiting(bool wait)
    {
        waiting = wait;
    }
    bool isBusy()
    {
        return isbusy;
    }
    void setBusy(bool busyy)
    {
        isbusy = busyy;
    }
    int getTherapyCount()
    {
        return therapyCount;
    }
    void setArrivalTime(int time)
    {
        arrivalTime = time;
    }
    int getArrivalTime()
    {
        return arrivalTime;
    }
    int wantsIndividual()
    {
        return individual;
    }
    int getTherapyNeeded()
    {
        return therapyNeeded;
    }
};

class Psychologist
{
    bool busy;
    int patientGroup;
public:
    int therapyStart;
    int therapyLength;
    Psychologist(int ts, int pg, bool bs, int tl): therapyStart(ts), patientGroup(pg), busy(bs), therapyLength(tl), patientCount(0) {}
    int patientCount;
    int getTherapyLength()
    {
        return therapyLength;
    }
    bool isBusy()
    {
        return busy;
    }
    void setBusy(bool busyy)
    {
        busy = busyy;
    }
    int getPatientCount()
    {
        return patientGroup;
    }
    int getTherapyStart()
    {
        return therapyStart;
    }
    void setTherapyStart(int time)
    {
        therapyStart = time;
    }
};

int main()
{
    Queue *patqueue = 0;
    patqueue = new Queue;

    Queue *psychqueue = 0;
    psychqueue = new Queue;

    list<Patient> patients;
    queue<Patient> pat;
    list<Psychologist> psych;

    clock_t clk = 0;

    bool newPatient;
    int duration = 0;

    Bigint k;
    cout << "How long is the simulation going to run?: ";
    cin >> k;

    int groupCount = 0;
    int grp1PsychCount = 0;
    int grp2PsychCount = 0;
    int indPsychCount = 0;
    int patID = 0;
    int p = 0;
    clock_t time = clock();
    for(int i = 0;; i++)
    {
        if((rand() % 100) < 100)
        {
            bool ind = false;
            int therNeeded;
            if ((rand() % 100) < 10)
            {
                ind = true;
                therNeeded = thNeedInd;
            }
            else
            {
                ind = false;
                therNeeded = thNeedGrp;
            }

            if ((rand() % 100) < 20)
            {
                if (!ind)
                {
                    therNeeded = thNeedInd;
                    therNeeded = therNeeded - therNeeded/5;
                }
            }

            patID++;
            patients.push_front(Patient(i, false, ind, therNeeded, 0, patID));
            patqueue->addElement(patID);


        }





        for(list<Psychologist>::iterator itr = psych.begin(); itr != psych.end(); itr++)
        {
            if(i - itr->getTherapyStart() >= itr->getTherapyLength())
            {
                itr->setBusy(false);
            }
        }


        for (int m = 0; m < patqueue->length(); m++)
        {
            int therapyLen;
            list<Patient>::iterator itr = patients.begin();
            for(; itr != patients.end(); itr++)
            {

                if (itr->getPatientID() == patqueue->first())
                {
                    break;
                }
            }

            if (itr->getTherapyCount() >= itr->getTherapyNeeded())
            {
                patients.erase(itr);
                patqueue->remove();
                break;
            }
            if (itr->wantsIndividual())
            {
                therapyLen = indTherLength;
            }
            else
            {
                therapyLen = grpTherLength;
            }
            if (i - itr->getArrivalTime() >= itr->getTherapyLength() && itr->isBusy() && !itr->isWaiting())
            {
                itr->setBusy(false);
                itr->setWaitingTime(i);
                itr->setWaiting(true);
            }
            if(itr->isWaiting() && i - itr->getWaitingTime() >= waitingT)
            {
                itr->setWaiting(false);
            }




            for (list<Patient>::iterator pat = patients.begin(); pat != patients.end(); pat++)
            {
                if (patqueue->first() == pat->getPatientID())
                {

                    //individualus
                    if (pat->wantsIndividual() && !pat->isWaiting() && !pat->isBusy())
                    {
                        bool found1 = false;
                        list<Psychologist>::iterator psychol = psych.begin();
                        for(;psychol != psych.end(); psychol++)
                        {

                            if (!psychol->isBusy() && psychol->getPatientCount() == 1)
                            {
                                found1 = true;
                                break;
                            }
                        }
                        cout << found1 << endl;
                        if (found1)
                        {
                            p++;
                            psychol->setBusy(true);
                            psychol->setTherapyStart(i);
                            pat->setArrivalTime(i);
                            pat->setBusy(true);
                            pat->therapyCount++;

                        }
                        else if (!found1)
                        {
                            psych.push_front(Psychologist(i, 1, true, indTherLength));
                        }
                    }




                    //naujoku grupe
                    else if (!pat->wantsIndividual() && pat->getTherapyCount() == 0 && !pat->isBusy())
                    {

                        bool found2 = false;
                        if (!pat->getWaitForFirst() && !pat->isBusy() && pat-> getTherapyCount() == 0)
                        {
                            waitingForFirstTherapy++;
                            pat->waitForFirst(true);
                        }
                        if (waitingForFirstTherapy >= therapyGroup)
                        {
                            waitingForFirstTherapy = 0;
                            list<Psychologist>::iterator psychol1 = psych.begin();
                            for(; psychol1 != psych.end(); psychol1++)
                            {
                                if (!psychol1->isBusy() && psychol1->getPatientCount() == therapyGroup)
                                {
                                    found2 = true;
                                    break;
                                }
                            }
                                if (found2)
                                {
                                    psychol1->setBusy(true);
                                    psychol1->setTherapyStart(i);
                                }
                                else
                                {
                                    psych.push_front(Psychologist(i, therapyGroup, true, grpTherLength));
                                }
                            for (list<Patient>::iterator pat1 = patients.begin(); pat1 != patients.end(); pat1++)
                            {
                                if (pat1->getWaitForFirst() && pat1->getTherapyCount() == 0 && !pat1->isBusy())
                                {
                                    pat1->setArrivalTime(i);
                                    pat1->setBusy(true);
                                    pat1->therapyCount++;
                                    pat1->waitForFirst(false);
                                }

                            }
                        }
                    }



                    //patyrusiu grupe
                    else if (!pat->wantsIndividual() && pat->getTherapyCount() > 0 && !pat->isWaiting() && !pat->isBusy())
                    {
                        bool found3 = false;
                        if (!pat->getWaitForFirst() && !pat->isBusy() && pat->getTherapyCount() > 0)
                        {
                            waitingForTherapy++;
                            pat->waitForFirst(true);
                        }
                        if (waitingForTherapy >= smallTherapyGroup)
                        {
                            waitingForTherapy = 0;
                            list<Psychologist>::iterator psychol2 = psych.begin();
                            for(; psychol2 != psych.end(); psychol2++)
                            {
                                if (!psychol2->isBusy() && psychol2->getPatientCount() == smallTherapyGroup)
                                {
                                    found3 = true;
                                    break;
                                }
                            }
                            if (found3)
                                {
                                    psychol2->setBusy(true);
                                    psychol2->setTherapyStart(i);
                                }
                                else
                                {
                                    psych.push_front(Psychologist(i, smallTherapyGroup, true, grpTherLength));
                                }
                            for (list<Patient>::iterator pat2 = patients.begin(); pat2 != patients.end(); pat2++)
                            {
                                if (pat2->getWaitForFirst() && pat2->getTherapyCount() == 0 && !pat2->isBusy())
                                {
                                    pat2->setArrivalTime(i);
                                    pat2->setBusy(true);
                                    pat2->therapyCount++;
                                    pat2->waitForFirst(false);
                                }

                            }
                        }
                    }
                }
            }
            patqueue->addElement(patqueue->first());
            patqueue->remove();

        }


            for(list<Psychologist>::iterator itr = psych.begin(); itr != psych.end(); itr++)
            {
                if(itr->isBusy())
                {
                    cout << "[" << itr->getPatientCount() << "]";
                }
            }
            cout << endl;


    }
    for (list<Psychologist>::iterator iter = psych.begin(); iter != psych.end(); iter++)
            {
                if (iter->getPatientCount() == 1)
                {
                    indPsychCount++;
                }
                else if(iter->getPatientCount() == therapyGroup)
                {
                    grp1PsychCount++;

                }
                else if(iter->getPatientCount() == smallTherapyGroup)
                {
                    grp2PsychCount++;
                }
            }
    cout << "Didesniu grupiu psichologu reikia samdyti: " << grp1PsychCount << endl << "Mazesniu grupiu psichologu reikia samdyti: " << grp2PsychCount << endl << "Individualiu psichologu reikia samdyti: " << indPsychCount << endl;
    cout << "Programa veike: " << (clock() - time)*1.0/CLOCKS_PER_SEC << " sekundes." << endl;


    return 0;
}
