#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
#include <cstdint>

using namespace std;

//compaile command ----->>>   cl /EHsc /std:c++20 SieveOfEratostenes.cpp



unsigned int findNumber (const vector<unsigned int>& vec, unsigned int erase, unsigned int sttid, unsigned int count, unsigned int size)
{
    //vec is either eratos or markID.eratos's zero id is 2,So It is no problem if return number is 0;
    unsigned int schid = sttid;
    unsigned int countlast = count - 1;
    for (unsigned int i = 0; i < count; i++)
    {
        sttid >>= 1;
        if (vec[schid] == erase)
        {
            break;
        }
        else if (vec[schid] > erase)
        {
           if (schid < 0)break;
           schid -= sttid; 
        }
        else
        {
           unsigned int a = schid + sttid;
           if (a < size) schid = a;
        }
    }
    if (vec[schid] != erase) schid = 0;
    return schid;
}
unsigned int findNumSizeChange (const vector<unsigned int>& vec, unsigned int erase)
{
    unsigned int size = vec.size();
    unsigned int sttid = 1;
    unsigned int count = 0;
    while (sttid < size)
    {
        sttid <<= 1;
        count++;
    }

    count--;
    sttid >>= 1;
    unsigned int schid = findNumber(vec, erase, sttid, count, size);
    return schid;

}

void wrote_binary(const vector<unsigned int>& data)
{
    size_t count = data.size();
    const string filename ="prime_eratos_binary_223092871_" + to_string(count) + ".bin";
    ofstream ofs(filename, ios::out | ios::binary);
    if (!ofs) return;

    ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));
    ofs.write(reinterpret_cast<const char*>(data.data()), count * sizeof(unsigned int));
}

int main() {
    //variable---------------------------------
    const uint64_t RIMIT = 4294967295ULL;
    const unsigned int SIGHT = 223092871;

    vector<unsigned int> eratos = {2, 3, 5, 7};
    vector<unsigned int> referenceNum;
    vector<unsigned int> markID;
    vector<unsigned int> temporary;

    unsigned int inflate = 2;
    unsigned int difference = 2;
    unsigned int endnum = 11;
    unsigned int remainder = 2;


    unsigned int startid = 2;
    unsigned int beforeid = 1;
    int listUp = 0;
    int reachExpo = 0;

    unsigned int listUpsttid = 0;
    unsigned int listUpcount = 0;
    unsigned int listUpSize = 0;
    //var end-----------------------------------------

    //function-----------------------------------------
    auto overCheck = [&](unsigned int var, unsigned int start, int plus) -> unsigned int {
        uint64_t check = 0ULL;
        unsigned int below = 0;
        if (plus > 0)
        {
            check = static_cast<uint64_t>(var) + start;
        }
        else {
            check = static_cast<uint64_t>(var) * start;
        }
        if (check <= RIMIT){
            below = static_cast<unsigned int>(check);
        } 
        else 
        {
            below = 0;
        }
        return below;
    };
    //function end-----------------------------------------

    //main Loop -----------------------------------------
    while(reachExpo < 1) {
        if (listUp > 0) {
            cout << "reach listUp count: "<< startid << "\n";
            //peck multiple--------------------------------
            unsigned int hit1 = 0;
            //It investigate the startid whether prime or not.
            if (markID.size() > 1)
            {
                unsigned int duplicate = findNumSizeChange(markID, startid);
                if (duplicate > 0) hit1 = 1;
            }

            if(hit1 < 1) {
                unsigned int primeInEratos = eratos[startid];
                unsigned int ei = startid;
                unsigned int serialEra = 0;
                while (true) {
                    //This is whether there is ei in markID. 
                    unsigned int fid = 0;
                    if (markID.size() > 1) fid = findNumSizeChange(markID, ei);
                    if (fid < 1)//if it is not found.
                    {
                        serialEra = eratos[ei];
                        unsigned int multiple = primeInEratos * serialEra;
                        if (multiple >= SIGHT) {
                            if (ei == startid) {
                                reachExpo++;
                            }
                            break;
                        } 
                        unsigned int mid = findNumber(eratos, multiple, listUpsttid, listUpcount, listUpSize);
                        if (mid > 0) temporary.push_back(mid);
                    }
                    ei++;
                }
                size_t msize = markID.size();
                size_t tsize = temporary.size();
                size_t total = msize + tsize;
            
                markID.resize(total);
                msize--;
                tsize--;
                total--;
                unsigned int lastOne = 0;
                if (temporary.size() > 0) {
                    if (temporary.size() == 1) lastOne = 1;
                    while (lastOne < 2)
                    {
                        if(markID[msize] > temporary[tsize])
                        {
                            markID[total] = markID[msize];
                            if(msize > 0)msize--;
                        }
                        else
                        {
                            markID[total] = temporary[tsize];
                            if(tsize > 0)tsize--;
                            if (tsize < 1) lastOne++;;
                        }
                        total--;
                    }
                    temporary.clear();
                }

            }

        }
        else {
            cout << "debug count: "<< startid << "\n";
            //make list--------------------------------
            unsigned int eraRefid = startid;
            unsigned int removeNum = eratos[eraRefid] * eratos[startid];
            int refid = 0;
            int zeroFlag = 0;
            int inendId = 0;
            int refflag = 0;
            unsigned int lastNum = 0;
            int updateRemoveNum = 0;

            //initial--------------------------------
            referenceNum.clear();
            remainder = inflate;
            inflate = remainder * (eratos[startid] - 1);
            difference *= eratos[beforeid];
            lastNum = endnum;
            //If it is not over rimit that it return the result of culculate.
            unsigned int ov1 = overCheck(difference, eratos[startid], 0);
            if (ov1 > 0)
            {
                endnum = ov1;
                if (endnum >= SIGHT) { endnum = SIGHT; }
                else { endnum += 1; }
            }
            else
            {
                endnum = SIGHT;
            }
            //initial end--------------------------------
            
            //sifting multiple--------------------------------
            if (removeNum < endnum)
            {
                int onetime = 0;
                unsigned int startRmove = 0;
                unsigned int startRmoveId = 0;
                while(removeNum < endnum)//make referenceNum array is main work.
                {
                    if (removeNum > lastNum)
                    {
                        if (onetime == 0) {
                            startRmove = removeNum;
                            startRmoveId = referenceNum.size();
                            onetime++;
                        }
                    }
                    referenceNum.push_back(removeNum);
                    eraRefid++;
                    int ovSifting = overCheck(eratos[eraRefid], eratos[startid], 0);
                    //If it over rimit that removeNum is not chage.
                    if (ovSifting > 0){ removeNum = ovSifting; } 
                    else { break; }
                }
                referenceNum.push_back(removeNum);
                removeNum = startRmove;
                refid = startRmoveId;
                refflag = 1;
                zeroFlag = 1;
            }

            //erase multiple--------------------------------
            if (zeroFlag > 0)
            {
                //Erase the number multiple of eratos at startid.
                markID.clear();
                for (unsigned int i = 0; i < referenceNum.size(); i++) {
                    unsigned int inErase = referenceNum[i];
                    unsigned int eraseID = findNumSizeChange(eratos, inErase);
                    if (eraseID > startid) {
                        markID.push_back(eraseID);
                    }
                    if (i > 0)
                    {
                        if (eraseID == 0) break;
                    }
                }
                for (unsigned int i = 0; i < markID.size(); i++) {
                    unsigned int mid = markID[i];
                    if (mid >= eratos.size()) { break; }
                    else { eratos[mid] = 0; }
                 }
                erase(eratos, 0);

            }

            //add number to eratos--------------------------------
            unsigned int ei = startid;
            for (unsigned int i = 0; i < inflate; i++)
            {
                unsigned int add = 0;
                unsigned int base = eratos[ei];
                if (refflag > 0)
                {
                    if (eratos[ei] > referenceNum[inendId]) 
                    {
                        base = referenceNum[inendId];
                        inendId++;
                        ei--;//for execute again.
                    }
                }

                //uint64_t overcheck = static_cast<uint64_t>(difference) + eratos[ei];
                unsigned int ovAdd = overCheck(difference, base, 1);
                if (ovAdd > 0)
                {
                    add = ovAdd;
                }
                

                if (add <= endnum) {
                    if (add < removeNum)
                    { 
                        eratos.push_back(add); 
                    }
                    else {
                        if (updateRemoveNum > 0)
                        {
                            if (refid < referenceNum.size()) refid++;
                            removeNum = referenceNum[refid];
                            if (add < removeNum) { eratos.push_back(add); }
                            updateRemoveNum = 0;
                        }
                        else { updateRemoveNum = 1; }
                    }
                }
                else {

                    if (add < SIGHT) 
                    { break; }
                    else 
                    {
                        listUp = 1;
                        listUpSize = eratos.size();
                        listUpsttid = 1;
                        listUpcount = 0;
                        while (listUpsttid < listUpSize)
                        {
                            listUpsttid <<= 1;
                            listUpcount++;
                        }

                        listUpcount--;
                        listUpsttid >>= 1;
                        referenceNum.clear();
                        markID.clear();
                        markID.push_back(0);//This zero is it for false.
                        break;
                    }
                }

                
                ei++;
            }
        }


        startid++;
        if (listUp < 1) beforeid++;
    }
    //main Loop end-----------------------------------------

    for (unsigned int i = 1; i < markID.size(); i++)
    {
        unsigned int alleraseid = markID[i];
        eratos[alleraseid] = 0;
    }
    erase(eratos, 0);


    //write down -----------------------------------------
/*
    for (int i = 0; i < markID.size(); i++)
    {
        cout << markID[i] << ": ";
        if ((i % 10) == 0) cout << "\n";
    }
    cout << "markID end" << endl;
    cout << "\n\n";

    int debugSize = eratos.size();
    cout << "\n";
    cout << "debug express inner array" << endl;
    cout << "eratos after size: " << debugSize << endl;
    cout << "\n";
    for (int i = 0; i < debugSize; i++)
    {
        cout << eratos[i] << ": ";
        if ((i % 10) == 0) cout << "\n";
    }
    cout << "end" << endl;
    cout << "\n";
*/
    size_t final_size = eratos.size();
    cout << "\n\n";
    cout << "reach listUp end  \n\n";
    cout << "eratos size:  " << final_size;
    cout << "\n\n";
    cout << "\n\n";
    wrote_binary(eratos);
    cout << "write success  \n\n";
    //write down end-----------------------------------------

    return 0;
}