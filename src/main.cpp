#include "Game.h"


class BrainRot: Game{
public:
    void GiveEm(){
        Init();
    }
    void HawkTuah(){
        Run();
    }
    void Nourish(){
        Clean();
    }
};

int main(){
    BrainRot glizzy;
    glizzy.GiveEm();
    glizzy.HawkTuah();
    glizzy.Nourish();
}