//
// Created by hou guoli on 2018/2/11.
//

#include <iostream>
#include <string>
#include <time.h>
#include <map>

using namespace std;

class Memento{
public:
    Memento(int hp=0, int mp=0, int atk=0)
    {
        mHp = hp;
        mMp = mp;
        mAttack = atk;
    }

public:
    int mHp;
    int mMp;
    int mAttack;
};

class Caretaker
{
public:
    Memento* GetState(string key)
    {
        return mData[key];
    }
    void SetState(string key, Memento* pMemento)
    {
        mData[key] = pMemento;
    }
    ~Caretaker()
    {
        auto it = mData.begin();
        for(; it != mData.end(); it++)
        {
            if(mData.count("he") && it->second != nullptr)
            {
                delete it->second;
            }
        }
        mData.clear();
    }

private:
    map<string, Memento*> mData;
};

class Hero{
public:
    Hero(int hp=100, int mp=100, int at=100):mHp(hp), mMp(mp), mAttack(at), mCaretaker(new Caretaker){}

    void saveState(string key)
    {
        Memento* pMemento = new Memento(mHp, mMp, mAttack);
        mCaretaker->SetState(key, pMemento);
    }

    void resumeState(string key)
    {
        auto mmt = mCaretaker->GetState(key);
        mHp = mmt->mHp;
        mMp = mmt->mMp;
        mAttack = mmt->mAttack;
    }

    void battle()
    {
        mHp = rand()%100;
        mMp = rand()%100;
        mAttack = rand()%100;
    }

    void showState()
    {
        cout<<"血量："<<mHp<<endl
            <<"蓝量："<<mMp<<endl
            <<"攻击："<<mAttack<<endl;
    }

private:
    int mHp;
    int mMp;
    int mAttack;
    Caretaker* mCaretaker;
};

int test_Memento4()
{
    srand((unsigned int) time(NULL));

    Caretaker ctk;
    Hero hero;
    Memento mmt;

    cout<<"----战斗前-----"<<endl;
    hero.showState();
    cout<<endl;
    hero.saveState("战斗前");

    hero.battle();
    cout<<"-----战斗1后-----"<<endl;
    hero.showState();
    cout<<endl;
    hero.saveState("战斗1后");

    hero.battle();
    cout<<"-----战斗2后-----"<<endl;
    hero.showState();
    hero.saveState("战斗2后");
    cout<<endl;

    hero.battle();
    cout<<"-----战斗3后-----"<<endl;
    hero.showState();
    hero.saveState("战斗3后");
    cout<<endl;

    hero.resumeState("战斗1后");
    cout<<"-----恢复战斗1结果-----"<<endl;
    hero.showState();
    cout<<endl;

    hero.resumeState("战斗前");
    cout<<"-----恢复战斗前-----"<<endl;
    hero.showState();
    cout<<endl;

    return 0;
}
