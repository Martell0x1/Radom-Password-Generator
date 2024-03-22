//
// Created by martell on 3/22/24.
//

#include <iostream>
#include <cstdlib>

using namespace std;

class PassWordGenerator{
private:

    const char* LETTERS;
    const char* DIGITS;
    const char* SYMPOLS;

    int length;
    int Count;


private:

    void Shuffule(string& password){
        for(int x = 0 ; x < password.size() ; x++){
            int RandomIndex = rand() % password.size();
            char current = password[x];
            char temp = password[RandomIndex];
            password[x] = temp;
            password[RandomIndex] = current;
        }
    }


public:
    PassWordGenerator(){
        this-> length = 0;
//        srand(time(NULL)); // initialize this Globally , think if this function takes a long time , every time you create a new obj...
//        such a solution is to provide a static function to do so
    }
    PassWordGenerator(const char* chars , const char* digits , const char* sympols, int length): PassWordGenerator(){ // delegating the default constructor
        LETTERS = chars;
        DIGITS = digits;
        SYMPOLS = sympols;
        this->length = length;
    }

    void SetLength(int value){
        this->length = value;
    }

    int getLength() const{
        return this->length;
    }

    int getCount() const {
        return Count;
    }

    void setCount(int count) {
        Count = count;
    }

    static void Initialize(){
        srand(time(NULL));
    }
    [[nodiscard]] string GenerateCharacters() {
        string result;

        for(int x = 0 ; x < length ; x++){
            int num = rand() % (sizeof(LETTERS) / sizeof(*LETTERS));
            result += LETTERS[num];
        }
        int count = getCount();
        setCount(++count);

        return result;
    }

    [[nodiscard]] string GenerateDigits() {
        string result;

        for(int x = 0 ; x < length ; x++){
            int num = rand() % (sizeof(DIGITS) / sizeof(*DIGITS));
            result += to_string(DIGITS[num]);
        }
        int count = getCount();
        setCount(++count);

        return result;
    }

    [[nodiscard]] string Generate(bool Complix = false) {
        string result;

        for(int x = 0 ; x < length/2 ; x++){
            int num = rand() % (sizeof(LETTERS) / sizeof(*LETTERS));
            result += LETTERS[num];
        }

        for(int x = 0 ; x < length/2 ; x++){
            int num = rand() % (sizeof(DIGITS) / sizeof(*DIGITS));
            result += DIGITS[num];
        }

        Shuffule(result);

        if(Complix){
            int num = rand() % length;
            result[num] = SYMPOLS[num];
        }
        int count = getCount();
        setCount(++count);

        return result;

    }

    friend class BlackBoxTest; // blackboxtesting utility


};


int main(){
    const char* letters = "abcdefghijklmnopqrstuvwxyz";
    const char* digits = "0123456789";
    const char* symbols = "!@#$%^&*()-_+=~`[]{}|;:,.<>?";

    PassWordGenerator::Initialize();
    PassWordGenerator generator(letters,digits,symbols,8);
    string password = generator.Generate();

    cout << password  << " "<< generator.getCount();
}
